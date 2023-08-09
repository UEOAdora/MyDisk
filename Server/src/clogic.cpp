#include "clogic.h"

void CLogic::setNetPackMap()
{
    NetPackMap(_DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(_DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
    NetPackMap(_DEF_PACK_FILE_LIST_RQ)   = &CLogic::UserFileListRq;
    NetPackMap(_DEF_PACK_FILE_DOWNLOAD_RQ) = &CLogic::DownloadFileRq;
    NetPackMap(_DEF_PACK_FILE_HEAD_RS) = &CLogic::FileHeadRs;
    NetPackMap(_DEF_PACK_FILE_CONTENT_RS) = &CLogic::FileContentRs;
    NetPackMap(_DEF_PACK_UPLOAD_FILE_RQ) = &CLogic::UploadFileRq;
    //文件块请求
    NetPackMap(_DEF_PACK_FILE_CONTENT_RQ) = &CLogic::FileContentRq;
    //add
    NetPackMap(_DEF_PACK_ADD_FOLDER_RQ) = &CLogic::AddFolderRq;
}

#define DEF_PATH "/home/lighthouse/MyDisk/MyDisk/Server/Space/"

//注册
void CLogic::RegisterRq(sock_fd clientfd,char* szbuf,int nlen)
{
    printf("clientfd:%d RegisterRq\n", clientfd);
   //注册流程
   //1.解析数据包
    STRU_REGISTER_RQ *rq = (STRU_REGISTER_RQ*)szbuf;
    STRU_REGISTER_RS rs;
    rq->tel;
    //2.判断用户名是否存在
    //查询数据库 条件是tel
    char sqlbuf[1024] = "";
    sprintf(sqlbuf,"select u_tel from t_user where u_tel = '%s'",rq->tel);
    list<string> lstRes;
    bool res = m_sql->SelectMysql(sqlbuf,1,lstRes);
    if(!res){
        printf("sql select error:%s\n",sqlbuf);
        return ;
    }
    //有 ->手机号存在
    //无 -> 查数据库 条件是name 看昵称是否存在
    //有 -> 昵称存在 返回 name_is_exist
    //无 -> 注册成功 数据库插入信息 在网盘上创建存储路径 /home/lighthouse/MyDisk/MyDisk/Server/Space/user_id
    if(lstRes.size() > 0){
        //手机号存在
        rs.result = zh_is_exist;
        m_tcp->SendData(clientfd,(char*)&rs,sizeof(rs));
        return ;
    } else {
        sprintf(sqlbuf,"select u_name from t_user where u_name = '%s'",rq->name);
        lstRes.clear();
        res = m_sql->SelectMysql(sqlbuf,1,lstRes);
        if(!res){
            printf("sql select error:%s\n",sqlbuf);
            return ;
        }
        if(lstRes.size() > 0){
            rs.result = name_is_exist;
        } else {
            
            sprintf(sqlbuf,"insert into t_user (u_tel,u_password,u_name) values('%s','%s','%s')",rq->tel,rq->password,rq->name);
            res = m_sql->UpdataMysql(sqlbuf);
            if(!res){
                printf("sql insert error:%s\n",sqlbuf);
                return ;
            }
            sprintf(sqlbuf,"select u_id from t_user where u_tel = '%s'",rq->tel);
            lstRes.clear();
            res = m_sql->SelectMysql(sqlbuf,1,lstRes);
            if(!res){
                printf("sql select error:%s\n",sqlbuf);
                return ;
            }
            int id = 0;
            if(lstRes.size() > 0){
                id = atoi(lstRes.front().c_str());
            }
            char strPath[1024] = "";
            sprintf(strPath,"%s%d",DEF_PATH,id);
            umask(0);//设置权限掩码
            mkdir(strPath,S_IRWXU | S_IRWXG | S_IRWXO);//创建目录
            //S_IRWXU:表示文件所有者具有读、写和执行操作的权限
            //S_IRWXG:表示用户组具有读、写和执行操作的权限
            //S_IRWXO:表示其他用户具有读、写和执行操作的权限
            rs.result = register_success;
        }
    }
    //发送回复包
    SendData(clientfd,(char*)&rs,sizeof(rs));
}

//登录
void CLogic::LoginRq(sock_fd clientfd ,char* szbuf,int nlen)
{
    printf("clientfd:%d LoginRq\n", clientfd);
    //登录流程
    //1.解析数据包 tel passwd
    STRU_LOGIN_RQ *rq = (STRU_LOGIN_RQ*)szbuf;
    STRU_LOGIN_RS rs;
    //2.查询数据库 条件是tel 查询passwd id name
    char sqlbuf[1024] = "";
    list<string> lstRes;
    sprintf(sqlbuf,"select u_password,u_id,u_name from t_user where u_tel = '%s';",rq->tel);
    m_sql->SelectMysql(sqlbuf,3,lstRes);
    //无 -> 用户不存在 返回 user_not_exist
    if(lstRes.size() == 0){
        rs.result = user_not_exist;
    } else {
        //有 
        //  密码错误 -> 返回 passwd_error
        if(strcmp(lstRes.front().c_str(),rq->password) != 0){
            rs.result = password_error;
        } else {
            //  密码正确 -> 回复包里面写 name id
            lstRes.pop_front();
            int id = atoi(lstRes.front().c_str());
            lstRes.pop_front();
            string name = lstRes.front();
            lstRes.pop_front();
            rs.userid = id;
            strcpy(rs.name,name.c_str());
            rs.result = login_success;
            //map[id] = UserInfo id对用户信息的映射关系 
            UserInfo *user;
            if(!m_mapIDToUserInfo.find(id,user)){
                user = new UserInfo;
            }
            //覆盖
            user->clientfd = clientfd;
            user->userid = id;
            user->name = name;
            //更新映射关系
            m_mapIDToUserInfo.insert(id,user);
        }               
    }

    //发送回复包
    SendData(clientfd,(char*)&rs,sizeof(rs));
}

//用户文件列表请求
void CLogic::UserFileListRq(sock_fd clientfd ,char* szbuf,int nlen)
{
    printf("clientfd:%d UserFileListRq\n", clientfd);
    //拆包
    STRU_FILE_LIST_RQ *rq = (STRU_FILE_LIST_RQ*)szbuf;
    //获取 路径和userid 查询数据库 找到文件信息
    char sqlbuf[1024] = "";
    sprintf(sqlbuf,"select f_id,f_name,f_uploadtime,f_size,f_MD5,f_type from t_file where f_id in (select f_id from t_user_file where f_dir = '%s' and u_id = '%d');",rq->dir,rq->userid);
    list<string> lstRes;
    bool res = m_sql->SelectMysql(sqlbuf,6,lstRes);
    if(!res){
        printf("sql select error:%s\n",sqlbuf);
        return ;
    }
    if(lstRes.size() == 0){
        return ;
    }
    //封包 循环发送文件信息
    while(lstRes.size()!=0){
        string strid = lstRes.front();
        lstRes.pop_front();
        string strname = lstRes.front();
        lstRes.pop_front();
        string struploadTime = lstRes.front();
        lstRes.pop_front();
        string strsize = lstRes.front();
        lstRes.pop_front();
        string strMD5 = lstRes.front();
        lstRes.pop_front();
        string strtype = lstRes.front();
        lstRes.pop_front();
        STRU_FILE_INFO info;
        info.userid = rq->userid;
        info.fileid = atoi(strid.c_str());
        strcpy(info.dir,rq->dir);
        strcpy(info.md5,strMD5.c_str());
        info.size = atoi(strsize.c_str());
        strcpy(info.filename,strname.c_str());
        strcpy(info.fileType,strtype.c_str());
        strcpy(info.uploadTime,struploadTime.c_str());

        SendData(clientfd,(char*)&info,sizeof(info));
    }
}
void CLogic::DownloadFileRq(sock_fd clientfd, char*szbuf, int nlen){
    printf("clientfd:%d DownloadFileRq\n", clientfd);
    //拆包
    STRU_DOWNLOAD_RQ *rq = (STRU_DOWNLOAD_RQ*)szbuf;
    //数据库查询
    char sqlbuf[1024] = "";
    sprintf(sqlbuf,"select t_file.f_id, f_name, f_type, f_md5, f_size, t_user_file.f_dir, f_path from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id where t_user_file.u_id = %d and t_file.f_id = %d ;",rq->userid,rq->fileid);
    list<string> lstRes;
    m_sql->SelectMysql(sqlbuf,7,lstRes);
    if(lstRes.size() == 0){
        return ;
    }
    //做映射 fileid to FileInfo
    FileInfo *info = new FileInfo;
    info->fileid = atoi(lstRes.front().c_str());
    lstRes.pop_front();
    info->name = lstRes.front();
    lstRes.pop_front();
    info->type = lstRes.front();
    lstRes.pop_front();
    info->md5 = lstRes.front();
    lstRes.pop_front();
    info->size = atoi(lstRes.front().c_str());
    lstRes.pop_front();
    info->dir = lstRes.front();
    lstRes.pop_front();
    info->absolutePath = lstRes.front();
    lstRes.pop_front();

    if(info->type == "file"){
        info->filefd = open(info->absolutePath.c_str(),O_RDONLY);
        if(info->filefd <= 0){
            printf("open file error:%d\n",errno);
            return ;
        }
        char idbuf[100] = "";
        sprintf(idbuf, "%10d%10d",rq->userid,rq->fileid);
        string strid = idbuf;
        m_mapFileidToFileInfo.insert(strid,info);
        //返回文件头请求
        STRU_FILE_HEAD_RQ headrq;
        strcpy(headrq.dir,info->dir.c_str());
        headrq.fileid = info->fileid;
        strcpy(headrq.fileName,info->name.c_str());
        strcpy(headrq.fileType,info->type.c_str());
        strcpy(headrq.md5,info->md5.c_str());
        headrq.size = info->size;

        SendData(clientfd,(char*)&headrq,sizeof(headrq));
    } else{  //文件夹

    }


}

void CLogic::FileHeadRs(sock_fd clientfd, char*szbuf, int nlen){
    printf("clientfd:%d FileHeadRs\n", clientfd);
    //拆包
    STRU_FILE_HEAD_RS *rs = (STRU_FILE_HEAD_RS*)szbuf;
    //取出信息
    rs->fileid;
    rs->userid;
    //从map里找信息 ->fd
    char idbuf[100] = "";
    FileInfo *info = nullptr;
    sprintf(idbuf, "%10d%10d",rs->userid,rs->fileid);
    if(!m_mapFileidToFileInfo.find(idbuf,info)){
        printf("file not found\n");
        return ;
    }
    //读取文件内容
    STRU_FILE_CONTENT_RQ rq;
    rq.fileid = rs->fileid;
    rq.userid = rs->userid;

    rq.len = read(info->filefd,rq.content,_DEF_BUFFER);

    //发送文件内容请求
    SendData(clientfd,(char*)&rq,sizeof(rq));
}

void CLogic::FileContentRs(sock_fd clientfd, char*szbuf, int nlen){
    printf("clientfd:%d FileContentRs\n", clientfd);
    //拆包
    STRU_FILE_CONTENT_RS *rs = (STRU_FILE_CONTENT_RS*)szbuf;
    //取出信息
    rs->fileid;
    rs->userid;
    //从map里找信息 ->fd
    char idbuf[100] = "";
    FileInfo *info = nullptr;
    sprintf(idbuf, "%10d%10d",rs->userid,rs->fileid);
    if(!m_mapFileidToFileInfo.find(idbuf,info)){
        printf("file not found\n");
        return ;
    }
    //如果不成功 文件流跳回到之前的位置 重新读
    if(rs->result == 0){
        lseek(info->filefd,-1*rs->len,SEEK_CUR);
    } else{
        //成功
        info->pos += rs->len;
            //可能文件读取结束
        if(info->pos >= info->size){
            //关闭文件
            close(info->filefd);
            //删除映射关系
            m_mapFileidToFileInfo.erase(idbuf);
        } 
    }
    //继续读取
    STRU_FILE_CONTENT_RQ rq;
    rq.fileid = rs->fileid;
    rq.userid = rs->userid;
    rq.len = read(info->filefd,rq.content,_DEF_BUFFER);
    //发送文件内容请求
    SendData(clientfd,(char*)&rq,sizeof(rq));
}
void CLogic::UploadFileRq(sock_fd clientfd, char*szbuf, int nlen){
    printf("clientfd:%d UploadFileRq\n", clientfd);
    //拆包
    STRU_UPLOAD_FILE_RQ *rq = (STRU_UPLOAD_FILE_RQ*)szbuf;
    //获得信息
    //md5 看是否能秒传 文件名+MD5+state作为条件 查 如果有 就秒传
    //不是秒传
    FileInfo *info = new FileInfo;
    char pathbuf[1024] = "";
    sprintf(pathbuf,"%s%d%s%s",DEF_PATH,rq->userid,rq->dir,rq->fileName);
    //输出pathbuf
    printf("pathbuf:%s\n",pathbuf);
    info->absolutePath = pathbuf;
    info->dir = rq->dir;
    info->md5 = rq->md5;
    info->name = rq->fileName;
    info->size = rq->size;
    info->time = rq->time;
    info->type = rq->fileType;
    //把文件信息插入到数据库 2条 文件信息
    
    
    char sqlbuf[1024] = "";
    sprintf(sqlbuf,"insert into t_file (f_name ,  f_uploadtime ,  f_size ,  f_path ,  f_count ,  f_MD5  , f_state , f_type ) values ( '%s' , '%s' , %d , '%s' , 1, '%s' , 0  , '%s' );",
            rq->fileName,rq->time,rq->size,pathbuf,rq->md5,rq->fileType);
    if(!m_sql->UpdataMysql(sqlbuf)){
        printf("sql insert error:%s\n",sqlbuf);
        return ;
    }
    //查询 获取id
    list<string> lstRes;
    sprintf(sqlbuf,"select f_id from t_file where f_name = '%s' and f_MD5 = '%s';",rq->fileName,rq->md5);
    bool res = m_sql->SelectMysql(sqlbuf,1,lstRes);
    if(!res){
        printf("sql select error:%s\n",sqlbuf);
        return ;
    }
    info->fileid = stoi(lstRes.front());
    lstRes.pop_front();
    //写数据库 用户文件关系
    sprintf(sqlbuf,"insert into t_user_file (u_id , f_id , f_dir) values ( %d , %d , '%s' );",rq->userid,info->fileid,rq->dir);
    res = m_sql->UpdataMysql(sqlbuf);
    if(!res){
        printf("sql insert error:%s\n",sqlbuf);
        return ;
    }
    //打开文件
    info->filefd = open(pathbuf,O_CREAT | O_WRONLY | O_TRUNC ,0777);//八进制
    if(info->filefd <= 0){
        printf("open file error:%d\n",errno);
        return ;
    }
    //创建文件信息结构
    
    //添加到map
    char idstr[100] = "";
    sprintf(idstr,"%10d%10d",rq->userid,info->fileid);
    m_mapFileidToFileInfo.insert(idstr,info);
    //写回复
    STRU_UPLOAD_FILE_RS rs;
    rs.fileid = info->fileid;
    rs.userid = rq->userid;
    rs.result = 1;//成功
    strcpy(rs.md5,rq->md5);
    SendData(clientfd,(char*)&rs,sizeof(rs));
}
void CLogic::FileContentRq(sock_fd clientfd, char*szbuf, int nlen){
    printf("clientfd:%d FileContentRq\n", clientfd);
    //拆包
    STRU_FILE_CONTENT_RQ *rq = (STRU_FILE_CONTENT_RQ*)szbuf;
    //从map里 取出信息
    char idbuf[100] = "";
    sprintf(idbuf, "%10d%10d",rq->userid,rq->fileid);
    FileInfo *info = nullptr;

    if(!m_mapFileidToFileInfo.find(idbuf,info)){
        printf("file not found\n");
        return ;
    }
    STRU_FILE_CONTENT_RS rs;
    //写入内容
    int ret = write(info->filefd,rq->content,rq->len);
    //失败
    if(ret != rq->len){
        lseek(info->filefd,-1*ret,SEEK_CUR);
        rs.result = 0;
        return ;
    }else{
        rs.result = 1;
        //成功 长度加
        info->pos += ret;
        //判断文件是否结束
        if(info->pos >= info->size){
            //结束 关闭文件 回收 数据库state->1
            //关闭文件
            close(info->filefd);
            //删除映射关系
            m_mapFileidToFileInfo.erase(idbuf);
            //更新数据库
            char sqlbuf[1024] = "";
            sprintf(sqlbuf,"update t_file set f_state = 1 where f_id = %d;",rq->fileid);
            m_sql->UpdataMysql(sqlbuf);
            delete info;

        }
    }
    rs.fileid = rq->fileid;
    rs.userid = rq->userid;
    rs.len = rq->len;

    //没结束就写回复
    SendData(clientfd,(char*)&rs,sizeof(rs));
}

void CLogic::AddFolderRq(sock_fd clientfd, char*szbuf, int nlen){
    printf("clientfd:%d AddFolderRq\n", clientfd);
    //拆包
    STRU_ADD_FOLDER_RQ *rq = (STRU_ADD_FOLDER_RQ*)szbuf;
    //看看是否能秒传
    char pathbuf[1024] = "";
    sprintf(pathbuf,"%s%d%s%s",DEF_PATH,rq->userid,rq->dir,rq->fileName);
    list<string> lstRes;
    char sqlbuf[1024] = "";
    sprintf(sqlbuf,"select f_id from t_file where f_name = '%s' and f_type = '%s';",rq->fileName,"dir");
    bool res = m_sql->SelectMysql(sqlbuf,1,lstRes);
    if(!res){
        printf("sql select error:%s\n",sqlbuf);
        return ;
    }
    int fileid = 0;

    if(lstRes.size() == 0){
        sprintf(sqlbuf,"insert into t_file (f_name ,  f_uploadtime ,  f_size ,  f_path ,  f_count ,  f_MD5  , f_state , f_type ) values ( '%s' , '%s' , %d , '%s' , 1, '%s' , 1  , '%s' );",
        rq->fileName,rq->time,rq->size,pathbuf,rq->md5,rq->fileType);
        if(!m_sql->UpdataMysql(sqlbuf)){
            printf("sql insert error:%s\n",sqlbuf);
            return ;
        }
        //查询 获取id
        //查询 获取id
        list<string> lstRes;
        sprintf(sqlbuf,"select f_id from t_file where f_name = '%s' and f_MD5 = '%s';",rq->fileName,rq->md5);
        bool res = m_sql->SelectMysql(sqlbuf,1,lstRes);
        if(!res){
            printf("sql select error:%s\n",sqlbuf);
            return ;
        }
        fileid = stoi(lstRes.front());
        lstRes.pop_front();
    }else {
        fileid = stoi(lstRes.front());
        lstRes.pop_front();
    }

    //写数据库 用户文件关系
    sprintf(sqlbuf,"insert into t_user_file (u_id , f_id , f_dir) values ( %d , %d , '%s' );",rq->userid,fileid,rq->dir);
    res = m_sql->UpdataMysql(sqlbuf);
    if(!res){
        printf("sql insert error:%s\n",sqlbuf);
        return ;
    }
    //创建文件夹
    umask(0);//设置权限掩码
    mkdir(pathbuf,S_IRWXU | S_IRWXG | S_IRWXO);//创建目录
    //创建文件信息结构

    STRU_ADD_FOLDER_RS rs;
    rs.result = 1;
    SendData(clientfd,(char*)&rs,sizeof(rs));
}