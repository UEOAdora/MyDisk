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
    connect(this,SIGNAL(SIG_updateFileProgress(int,int)), m_pUI, SLOT(slot_updateFileProgress(int,int)));
    connect(m_pUI, SIGNAL(SIG_uploadFile(QString)), this, SLOT(slot_uploadFile(QString)));
    connect(m_pUI, SIGNAL(SIG_uploadFolder(QString)), this, SLOT(slot_uploadFolder(QString)));
    //更新文件上传进度
    connect(this, SIGNAL(SIG_updateUploadFileProgress(int, int)), m_pUI, SLOT(slot_updateUploadFileProgress(int, int)));
    connect(m_pUI, SIGNAL(SIG_addFolder(QString)),this,SLOT(slot_addFolder(QString)));
}
#include<QTextCodec>

// QString -> char* gb2312
void Utf8ToGB2312(char* gbbuf, int nlen, QString& utf8)
{
    //转码的对象
    QTextCodec* gb2312code = QTextCodec::codecForName("gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    QByteArray ba = gb2312code->fromUnicode(utf8);// Unicode -> 转码对象的字符集

    strcpy_s(gbbuf, nlen, ba.data());
}

// char* gb2312 --> QString utf8
QString GB2312ToUtf8(char* gbbuf)
{
    //转码的对象
    QTextCodec* gb2312code = QTextCodec::codecForName("gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    return gb2312code->toUnicode(gbbuf);// 转码对象的字符集 -> Unicode
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
    NetMap( _DEF_PACK_FILE_CONTENT_RS) = &Ckernel::slot_dealFileContentRs;
    //上传回复
    NetMap( _DEF_PACK_UPLOAD_FILE_RS) = &Ckernel::slot_dealUploadFileRs;
    NetMap( _DEF_PACK_ADD_FOLDER_RS) = &Ckernel::slot_dealAddFolderRs;
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
        m_curDir = "/";

        //追加请求 获取用户根目录'/'下面的所有文件
        //STRU_FILE_LIST_RQ rq;
        //rq.userid = m_id;
        //strcpy(rq.dir, "/");
        //
        //SendData((char*)&rq, sizeof(rq));
        slot_uploadFileList();
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
    //输出绝对路径
    qDebug() << "绝对路径:" << fileInfo.absolutePath;
    //转化为ANSI
    char pathbuf[1024] = "";
    Utf8ToGB2312(pathbuf, 1000, fileInfo.absolutePath);
    //打开文件
    fileInfo.pfile = fopen(pathbuf, "wb");
    if(!fileInfo.pfile)
    {
        qDebug() << "打开文件失败:"<<fileInfo.absolutePath;
        return;
    }
    m_pUI->slot_insertDownloadFile(fileInfo);
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

 //   //验证文件是否存在
 //   if (QFile::exists(info.absolutePath)) {
	//	qDebug() << "文件已存在";
 //       //输出文件大小和内容
 //       qDebug() << "文件大小:" << info.size;
 //       qDebug() << "文件内容:" << info.pfile;

	//}
 //   else {
	//	qDebug() << "文件不存在";
	//}
    //写文件内容回复
    STRU_FILE_CONTENT_RS rs;
    if (len != rq->len) {
        //失败->回退
        fseek(info.pfile, -1*len, SEEK_CUR);
        rs.result = 0;
    }
    else {
        info.pos += len;
        rs.result = 1;
        //更新进度条 文件id pos
        Q_EMIT SIG_updateUploadFileProgress(info.fileid, info.pos);
    }
    rs.len = rq->len;
    rs.fileid = rq->fileid;
    rs.userid = rq->userid;
    
    

    if (info.pos >= info.size) { //文件接收完毕
        //对文件进行md5校验

        fclose(info.pfile);
        m_pUI->slot_insertComplete(info);
        m_mapFileidToFileInfo.erase(info.fileid);
    }
    SendData((char*)&rs, sizeof(rs));
}

//获取文件md5
string getFileMD5(QString path) {
    //打开文件 将文件读取到md5对象中
    FILE* pfile = nullptr;
    //utf-8->ascii
    char buf[1024] = "";
    Utf8ToGB2312(buf, 1000, path);
    pfile = fopen(buf, "rb");
    if (!pfile) {
		qDebug() << "打开文件失败";
		return "";
	}
    int len = 0;
    MD5 md;
    do {
        len = fread(buf, 1, 1024, pfile);
        md.update(buf, len);
    } while (len > 0);
    //输出md5
    qDebug() << "文件md5:" << md.toString().c_str();
    return md.toString();
}
#include <QFileInfo>
#include <QDateTime>
void Ckernel::slot_uploadFile(QString path)
{
    //创建文件信息结构体
    QFileInfo fileInfo(path);
    FileInfo info;
    info.absolutePath = path;
    info.dir = m_curDir;

    info.md5 = QString::fromStdString(getFileMD5(path));
    info.name = fileInfo.fileName();
    info.pfile;
    info.size = fileInfo.size();
    info.time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    info.type = "file";
    //打开文件
    char pathbuf[1024] = "";
    Utf8ToGB2312(pathbuf, 1000, path);
    info.pfile = fopen(pathbuf, "rb");
    //求解文件MD5

    //添加map 里面map[md5] = fileInfo
    m_mapFileMd5ToFileInfo[info.md5.toStdString()] = info;
    //上传文件 打包
    STRU_UPLOAD_FILE_RQ rq;
    std::string strPath = info.dir.toStdString();
    strcpy(rq.dir, strPath.c_str());
    std::string strName = info.name.toStdString();
    strcpy(rq.fileName, strName.c_str());
    strcpy(rq.fileType, "file");
    strcpy(rq.md5, info.md5.toStdString().c_str());
    rq.size = info.size;
    strcpy(rq.time, info.time.toStdString().c_str());
    rq.userid = m_id;

    //发送
    SendData((char*)&rq, sizeof(rq));

}

void Ckernel::slot_uploadFolder(QString path)
{
}

void Ckernel::slot_dealFileContentRs(unsigned int lSendIP, char* buf, int nlen)
{
    //拆包 获取信息
    STRU_FILE_CONTENT_RS* rs = (STRU_FILE_CONTENT_RS*)buf;
    if (m_mapFileidToFileInfo.count(rs->fileid) == 0) {
        return;
    }
    FileInfo& info = m_mapFileidToFileInfo[rs->fileid];
    //更新进度
    
    if (rs->result == 0) {
        //失败
		fseek(info.pfile, -1 * rs->len, SEEK_CUR);
    }
    else {
        info.pos += rs->len;
        Q_EMIT SIG_updateUploadFileProgress(info.fileid, info.pos);
        if (info.pos >= info.size) {
            if (info.dir == m_curDir) {
                slot_uploadFileList();
            }
            fclose(info.pfile);

            m_pUI->slot_insertUploadComplete(info);
			m_mapFileidToFileInfo.erase(rs->fileid);
            return ;
        }
	}

    STRU_FILE_CONTENT_RQ rq;
    //读文件
    int len = fread(rq.content, 1, _DEF_BUFFER, info.pfile);
    rq.len = len;
    rq.fileid = rs->fileid;
    rq.userid = rs->userid;
    //发送文件内容
    SendData((char*)&rq, sizeof(rq));



}

void Ckernel::slot_dealUploadFileRs(unsigned int lSendIP, char* buf, int nlen)
{
    //拆包 获取信息
    STRU_UPLOAD_FILE_RS* rs = (STRU_UPLOAD_FILE_RS*)buf;
    //map md5 -》 id map
    if (m_mapFileMd5ToFileInfo.count(rs->md5) == 0) {
		return;
	}
    FileInfo& info = m_mapFileMd5ToFileInfo[rs->md5];
    m_mapFileidToFileInfo[rs->fileid] = info;//拿文件信息

    m_pUI->slot_insertUploadFile(info);
    
    STRU_FILE_CONTENT_RQ rq;
    //读文件
    int len = fread(rq.content, 1, _DEF_BUFFER, info.pfile);
    rq.len = len;
    rq.fileid = rs->fileid;
    rq.userid = rs->userid;
    //发送文件内容
    SendData((char*)&rq, sizeof(rq));
    //从md5 map 删除 该点
	m_mapFileMd5ToFileInfo.erase(rs->md5);
}

void Ckernel::slot_uploadFileList()
{
    m_pUI->slot_deleteAllFileInfo();
    STRU_FILE_LIST_RQ rq;
    rq.userid = m_id;
    
    std::string curDir = m_curDir.toStdString();
    strcpy(rq.dir, curDir.c_str());
    SendData((char*)&rq, sizeof(rq));
}

void Ckernel::slot_addFolder(QString name)
{
    STRU_ADD_FOLDER_RQ rq;
    std::string strPath = m_curDir.toStdString();
    strcpy(rq.dir, strPath.c_str());
    std::string strName = name.toStdString();
    strcpy(rq.fileName, strName.c_str());
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    rq.size = 0;
    strcpy(rq.time, time.toStdString().c_str());
    rq.userid = m_id;
    strcpy(rq.fileType, "dir");
    //发送
    SendData((char*)&rq, sizeof(rq));
}

void Ckernel::slot_dealAddFolderRs(unsigned int lSendIP, char* buf, int nlen)
{
    STRU_ADD_FOLDER_RS* rs = (STRU_ADD_FOLDER_RS*)buf;
    if (rs->result == 1) {
		slot_uploadFileList();
	}
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
