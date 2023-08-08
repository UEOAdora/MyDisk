#include "ckernel.h"
#include <iostream>
#include <QCoreApplication>
#include <QSettings>
#include <QFileInfo>
#include <QMessageBox>
#include "TcpClientMediator.h"
#include "TcpServerMediator.h"

#include <QDir>
using namespace std;

#define MD5_KEY "1234"

string getMD5(QString val) {
    QString str = QString("%1_%2").arg(val).arg(MD5_KEY);
    MD5 md5(str.toStdString());
    qDebug() << str << "md5:" << md5.toString().c_str();
    return md5.toString();
}

//构造函数
Ckernel::Ckernel(QObject* parent)
    : QObject(parent), m_id(0),m_curDir("/")
{
    //设置配置文件
    setConfig();
    setNetMap();
    m_tcpClient = new TcpClientMediator;
    m_tcpClient->OpenNet(m_ip.toStdString().c_str(), m_port);
    connect(m_tcpClient, SIGNAL(SIG_ReadyData(unsigned int,char*,int)), this, SLOT(slot_clientReadyData(unsigned int,char*,int)));
    //创建UI
    m_pUI = new MainWindow;
    //m_pUI->show();
    m_loginDialog = new LoginDialog;
    m_loginDialog->show();
    connect(m_pUI, SIGNAL(sig_close()), this, SLOT(slot_deleteLater()));
    connect(m_pUI, SIGNAL(SIG_downloadFile(int)), this, SLOT(slot_downloadFile(int)));
    connect(m_loginDialog, SIGNAL(SIG_registerCommit(QString,QString,QString)), this, SLOT(slot_registerCommit(QString,QString,QString)));
    connect(m_loginDialog, SIGNAL(SIG_loginCommit(QString,QString)), this, SLOT(slot_loginCommit(QString,QString)));
    connect(m_loginDialog, SIGNAL(SIG_close()), this, SLOT(slot_deleteLater()));
}

void Ckernel::setConfig()
{
    //读取配置文件 windows .ini文件 linux xml文件
    //[]组名
    //key=value 键值对
    //保存在exe同级目录下
    //获取exe路径
    QString path = QCoreApplication::applicationDirPath() + "/config.ini";
    //有 读取 没有 创建默认的
    //默认ip 和端口
    m_ip = "192.168.123.30";
    m_port = 8088;
    QFileInfo info(path);
    if (info.exists())
    {
        //读取
        QSettings config(path, QSettings::IniFormat, nullptr);
        config.beginGroup("net");
        //读取 ip port
        QVariant strip = config.value("config/ip", "");
        if (!strip.toString().isEmpty()) {
            m_ip = strip.toString();
        }
        QVariant nport = config.value("config/port", 0);
        if (nport.toInt() != 0) {
            m_port = nport.toInt();
        }
        config.endGroup();
    }
    else
    {
        //创建
        QSettings config(path, QSettings::IniFormat, nullptr);
        //写入组名 net
        config.beginGroup("net");
        //写入 默认 ip port
        config.setValue("config/ip", m_ip);
        config.setValue("config/port", m_port);
        config.endGroup();
    }
    //输出ip地址和端口
    cout << m_ip.toStdString() << endl;
    cout << m_port << endl;
    //查看是否有默认路径 exe同级路径
    QString sysPath = QCoreApplication::applicationDirPath() + "/NetDisk/";
    QDir dir;
    if (!dir.exists(sysPath)) {
        dir.mkdir(sysPath);
    }
    //fileinfo dir 带/的 要拼接
    m_sysPath = QCoreApplication::applicationDirPath() + "/NetDisk";
}
#define NetMap( a ) m_netPackMap[ a - _DEF_PROTOCOL_BASE]
void Ckernel::setNetMap()
{
    memset(m_netPackMap, 0, sizeof(PFUN)*_DEF_PROTOCOL_COUNT);
    NetMap( _DEF_PACK_LOGIN_RS ) = &Ckernel::slot_dealLoginRs;
    NetMap( _DEF_PACK_REGISTER_RS ) = &Ckernel::slot_dealRegisterRs;
    NetMap( _DEF_PACK_FILE_INFO ) = &Ckernel::slot_dealFileInfo;
    NetMap( _DEF_PACK_FILE_HEAD_RQ) =  &Ckernel::slot_dealFileHeadRq;
    NetMap( _DEF_PACK_FILE_CONTENT_RQ) = &Ckernel::slot_dealFileContentRq;
}

void Ckernel::SendData(char* buf, int nlen)
{
    m_tcpClient->SendData(0, buf, nlen);
}



void Ckernel::slot_clientReadyData(unsigned int lSendIP, char* buf, int nlen)
{
    //std::string text = buf;
    //QMessageBox::about(nullptr, "客户端接收", QString("来自服务器:%1").arg(QString::fromStdString(text)));
    //处理协议头
    char * tmp = buf;
    int type = *(int*)tmp;
    //判断是否合法
    if (type < _DEF_PROTOCOL_COUNT+_DEF_PROTOCOL_BASE && type >= _DEF_PROTOCOL_BASE)
    {
        PFUN pf = NetMap(type);
        if (pf) {
            (this->*pf)(lSendIP, buf, nlen);
        }
    }
    delete[] buf;
}


void Ckernel::slot_dealLoginRs(unsigned int lSendIP, char* buf, int nlen)
{
    qDebug() << __func__;
    //拆包
    STRU_LOGIN_RS* rs = (STRU_LOGIN_RS*)buf;
    //判断结果
    switch (rs->result)
    {
    case user_not_exist:
        QMessageBox::about(nullptr, "登录结果", "账号不存在");
        break;
    case password_error:
        QMessageBox::about(nullptr, "登录结果", "密码错误");
        break;
    case login_success:
        QMessageBox::about(nullptr, "登录结果", "登录成功");
        m_loginDialog->hide();
        m_pUI->show();
        //后台
        m_id = rs->userid;
        m_name = rs->name;

        m_pUI->slot_setInfo(m_name);

        //追加请求 获取用户根目录'/'下面的所有文件
        STRU_FILE_LIST_RQ rq;
        rq.userid = m_id;
        strcpy(rq.dir, "/");

        SendData((char*)&rq, sizeof(rq));

        break;
    }
}

void Ckernel::slot_dealRegisterRs(unsigned int lSendIP, char* buf, int nlen)
{
    qDebug() << __func__;
    //拆包
    STRU_REGISTER_RS* rs = (STRU_REGISTER_RS*)buf;
    //判断结果
    switch (rs->result)
    {
    case zh_is_exist:
        QMessageBox::about(nullptr, "注册结果", "账号已存在");
        break;
    case name_is_exist:
        QMessageBox::about(nullptr, "注册结果", "昵称已存在");
        break;
    case register_success:
        QMessageBox::about(nullptr, "注册结果", "注册成功");
        break;

    }
}

void Ckernel::slot_dealFileInfo(unsigned int lSendIP, char* buf, int nlen)
{
    //拆包
    STRU_FILE_INFO * info = (STRU_FILE_INFO*)buf;
    //读取信息 用qdebug输出
    qDebug() << "fileName:" << info->filename;
    qDebug() << "uploadTime:" << info->uploadTime;
    qDebug() << "size:" << info->size;
    qDebug() << "type:" << info->fileType;
    qDebug() << "md5:" << info->md5;
    qDebug() << "dir:" << info->dir;
    qDebug() << "fileid:" << info->fileid;
    //判断是否是当前路径
    if (m_curDir == info->dir) {
        FileInfo file;
        file.fileid = info->fileid;
        file.name = info->filename;
        file.time = info->uploadTime;
        file.size = info->size;
        file.type = info->fileType;
        file.md5 = info->md5;
        file.dir = info->dir;
        m_pUI->slot_insertFileInfo(file);
    }
}

void Ckernel::slot_downloadFile(int fileid)
{
    //发送下载请求
    STRU_DOWNLOAD_RQ rq;
    rq.userid = m_id;
    rq.fileid = fileid;
    SendData((char*)&rq, sizeof(rq));
}

void Ckernel::slot_dealFileHeadRq(unsigned int lSendIP, char* buf, int nlen)
{
    //拆包
    STRU_FILE_HEAD_RQ * rq = (STRU_FILE_HEAD_RQ*)buf;
    //创建info
    FileInfo fileInfo;
    fileInfo.dir = QString::fromStdString(rq->dir);
    fileInfo.fileid = rq->fileid;
    fileInfo.name = QString::fromStdString(rq->fileName);
    fileInfo.type = QString::fromStdString(rq->fileType);
    fileInfo.md5 = QString::fromStdString(rq->md5);
    fileInfo.size = rq->size;
    //绝对路径 默认路径 exe同级
    fileInfo.absolutePath = m_sysPath + fileInfo.dir +  fileInfo.name;
    //打开文件
    fileInfo.pfile = fopen(fileInfo.absolutePath.toStdString().c_str(), "wb");
    if(!fileInfo.pfile)
    {
        qDebug() << "打开文件失败:"<<fileInfo.absolutePath;
        return;
    }
    //加入到map
    m_mapFileidToFileInfo[fileInfo.fileid] = fileInfo;
    //写文件头回复
    STRU_FILE_HEAD_RS rs;
    rs.fileid = rq->fileid;
    rs.userid = m_id;
    rs.result = 1; //0失败 1成功

    SendData((char*)&rs, sizeof(rs));
}

void Ckernel::slot_dealFileContentRq(unsigned int lSendIP, char* buf, int nlen)
{
    //拆包
    STRU_FILE_CONTENT_RQ * rq = (STRU_FILE_CONTENT_RQ*)buf;
    if (m_mapFileidToFileInfo.count(rq->fileid) == 0) {
        return;
    }
    //写文件
    FileInfo& info = m_mapFileidToFileInfo[rq->fileid];
    int len = fwrite(rq->content, 1, rq->len, info.pfile);
    //有可能失败
    //写文件内容回复
    STRU_FILE_CONTENT_RS rs;
    if (len != rq->len) {
        rs.result = 0;
    }
    else {
        info.pos += len;
        rs.result = 1;
    }
    rs.len = rq->len;
    rs.fileid = rq->fileid;
    rs.userid = rq->userid;
    if (info.pos >= info.size) {
        fclose(info.pfile);
    m_mapFileidToFileInfo.erase(info.fileid);
    }
    SendData((char*)&rs, sizeof(rs));
}

//void Ckernel::slot_serverReadyData(unsigned int lSendIP, char* buf, int nlen)
//{
//    //std::string text = buf;
//    //QMessageBox::about(nullptr,"服务器接收",QString("来自客户端:%1").arg(QString::fromStdString(text)));
//    //m_tcpServer->SendData(lSendIP, buf, nlen);
//    //delete[] buf;
//}

void Ckernel::slot_registerCommit(QString zh, QString passwd, QString name)
{
    STRU_REGISTER_RQ rq;
    //QString 转 char* 包括兼容中文
    std::string zhStr = zh.toStdString();
    strcpy(rq.tel, zhStr.c_str());
    std::string passwdStr = getMD5(passwd);/*passwd.toStdString();*/
    strcpy(rq.password, passwdStr.c_str());
    std::string nameStr = name.toStdString();
    strcpy(rq.name, nameStr.c_str());
    SendData((char*)&rq, sizeof(rq));
}
void Ckernel::slot_loginCommit(QString zh, QString passwd)
{
    STRU_LOGIN_RQ rq;
    //QString 转 char* 包括兼容中文
    std::string zhStr = zh.toStdString();
    strcpy(rq.tel, zhStr.c_str());
    std::string passwdStr = getMD5(passwd);/*passwd.toStdString();*/
    strcpy(rq.password, passwdStr.c_str());
    SendData((char*)&rq, sizeof(rq));
}
void Ckernel::slot_deleteLater()
{
    cout << "delete" << endl;
    //回收网络
    m_tcpClient->CloseNet();

    delete m_tcpClient;

    delete m_pUI;
    delete m_loginDialog;
}
