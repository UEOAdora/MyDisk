#ifndef CLOGIC_H
#define CLOGIC_H

#include"TCPKernel.h"

class CLogic
{
public:
    CLogic( TcpKernel* pkernel )
    {
        m_pKernel = pkernel;
        m_sql = pkernel->m_sql;
        m_tcp = pkernel->m_tcp;
    }
public:
    //设置协议映射
    void setNetPackMap();
    /************** 发送数据*********************/
    void SendData( sock_fd clientfd, char*szbuf, int nlen )
    {
        m_pKernel->SendData( clientfd ,szbuf , nlen );
    }
    /************** 网络处理 *********************/
    //注册
    void RegisterRq(sock_fd clientfd, char*szbuf, int nlen);
    //登录
    void LoginRq(sock_fd clientfd, char*szbuf, int nlen);
    //用户文件列表请求
    void UserFileListRq(sock_fd clientfd, char*szbuf, int nlen);
    //下载文件请求
    void DownloadFileRq(sock_fd clientfd, char*szbuf, int nlen);
    //文件头回复
    void FileHeadRs(sock_fd clientfd, char*szbuf, int nlen);
    //文件内容回复
    void FileContentRs(sock_fd clientfd, char*szbuf, int nlen);
    //上传文件请求
    void UploadFileRq(sock_fd clientfd, char*szbuf, int nlen); 

    void FileContentRq(sock_fd clientfd, char*szbuf, int nlen);

    void AddFolderRq(sock_fd clientfd, char*szbuf, int nlen);
    /*******************************************/

private:
    TcpKernel* m_pKernel;
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;

    MyMap<int ,UserInfo*> m_mapIDToUserInfo;
    MyMap<std::string ,FileInfo*> m_mapFileidToFileInfo;
    //string -> userid+fileid 一个文件可能多人下载 一个人可能下载多个文件 防止混淆
};

#endif // CLOGIC_H
