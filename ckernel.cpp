#include "ckernel.h"
#include <iostream>
#include <QCoreApplication>
#include <QSettings>
#include <QFileInfo>
#include <QMessageBox>
#include "TcpClientMediator.h"
#include "TcpServerMediator.h"
using namespace std;
//构造函数
Ckernel::Ckernel(QObject* parent)
    : QObject(parent)
{
    //设置配置文件
    setConfig();
    setNetMap();
    m_tcpClient = new TcpClientMediator;

    m_tcpClient->OpenNet(m_ip.toStdString().c_str(), m_port);

//    connect(m_tcpServer, SIGNAL(SIG_ReadyData(unsigned int,char*,int)), this, SLOT(slot_serverReadyData(unsigned int,char*,int)));
    connect(m_tcpClient, SIGNAL(SIG_ReadyData(unsigned int,char*,int)), this, SLOT(slot_clientReadyData(unsigned int,char*,int)));
    //创建UI)

    m_pUI = new MainWindow;
    m_pUI->show();
    connect(m_pUI, SIGNAL(sig_close()), this, SLOT(slot_deleteLater()));
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
}
#define NetMap( a ) m_netPackMap[ a - _DEF_PROTOCOL_BASE]
void Ckernel::setNetMap()
{
    memset(m_netPackMap, 0, sizeof(PFUN)*_DEF_PROTOCOL_COUNT);
    NetMap( _DEF_PACK_LOGIN_RS ) = &Ckernel::slot_dealLoginRs;
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
}

//void Ckernel::slot_serverReadyData(unsigned int lSendIP, char* buf, int nlen)
//{
//    //std::string text = buf;
//    //QMessageBox::about(nullptr,"服务器接收",QString("来自客户端:%1").arg(QString::fromStdString(text)));
//    //m_tcpServer->SendData(lSendIP, buf, nlen);
//    //delete[] buf;
//}

void Ckernel::slot_deleteLater()
{
    cout << "delete" << endl;
    //回收网络
    m_tcpClient->CloseNet();

    delete m_tcpClient;

    delete m_pUI;
}
