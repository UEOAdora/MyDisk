#ifndef CKERNEL_H
#define CKERNEL_H

#pragma execution_character_set("utf-8")
#include <QObject>
#include "mainwindow.h"
#include "packdef.h"
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
    QString m_ip;
    int m_port;
    INetMediator * m_tcpClient;
    //INetMediator * m_tcpServer;
    //函数指针数组
    PFUN m_netPackMap[_DEF_PROTOCOL_COUNT];

public:
    static Ckernel* getInstance() {//静态函数获取单例
        static Ckernel kernel;
        return &kernel;
    }
signals:

private slots:
    //回收用槽函数
    void slot_deleteLater();
    //网络处理
    void slot_clientReadyData(unsigned int lSendIP, char* buf, int nlen);
    //void slot_serverReadyData(unsigned int lSendIP, char* buf, int nlen);
    //处理登录回复
    void slot_dealLoginRs(unsigned int lSendIP, char* buf, int nlen);
};

#endif // CKERNEL_H
