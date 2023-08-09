#ifndef CKERNEL_H
#define CKERNEL_H

#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "packdef.h"
#include "logindialog.h"
#include "md5.h"
#include <QDebug>
#include <stdio.h>
using namespace std;
//单例模式 拷贝构造和析构函数私有化 提供静态函数获取单例

class INetMediator;//类声明即可
class Ckernel;
//类函数指针类型
typedef void (Ckernel::*PFUN)(unsigned int lSendIP, char* buf, int nlen);

class Ckernel : public QObject
{
    Q_OBJECT
private:
    explicit Ckernel(QObject* parent = nullptr);//explicit防止隐式转换
    ~Ckernel() {}
    Ckernel(const Ckernel& kernel) {}//拷贝构造函数私有化
    void setConfig();//设置配置文件

    //初始化协议映射表
    void setNetMap();
    MainWindow* m_pUI;
    LoginDialog* m_loginDialog;
    QString m_ip;
    int m_port;
    INetMediator * m_tcpClient;
    //INetMediator * m_tcpServer;
    //函数指针数组
    PFUN m_netPackMap[_DEF_PROTOCOL_COUNT];
public:
    map<int, FileInfo> m_mapFileidToFileInfo;//文件id和文件信息的映射表

    QString m_sysPath;

    //发送函数
    void SendData(char* buf, int nlen);

    //名字 id
    QString m_name;
    int m_id;

    QString m_curDir;//当前目录

public:
    static Ckernel* getInstance() {//静态函数获取单例
        static Ckernel kernel;
        return &kernel;
    }
signals:
    void SIG_updateFileProgress(int fileid, int pos);
private slots:

    //处理控件的信号
    void slot_loginCommit(QString, QString);
    void slot_registerCommit(QString, QString, QString);

    //回收用槽函数
    void slot_deleteLater();
    //网络处理
    void slot_clientReadyData(unsigned int lSendIP, char* buf, int nlen);
    //void slot_serverReadyData(unsigned int lSendIP, char* buf, int nlen);
    //处理登录回复
    void slot_dealLoginRs(unsigned int lSendIP, char* buf, int nlen);
    //处理注册回复
    void slot_dealRegisterRs(unsigned int lSendIP, char* buf, int nlen);
    //处理文件信息
    void slot_dealFileInfo(unsigned int lSendIP, char* buf, int nlen);
    void slot_downloadFile(int fileid);
    //处理文件头请求
    void slot_dealFileHeadRq(unsigned int lSendIP, char* buf, int nlen);
    //处理文件内容请求
    void slot_dealFileContentRq(unsigned int lSendIP, char* buf, int nlen);
};

#endif // CKERNEL_H
