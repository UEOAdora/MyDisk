#pragma once

#include <memory.h>
#define _DEF_BUFFER  ( 16384 ) 
#define _DEF_CONTENT_SIZE	(1024)
#define _MAX_SIZE	(40)


//自定义协议   先写协议头 再写协议结构
//登录 注册
#define _DEF_PROTOCOL_BASE	(10000)
#define _DEF_PROTOCOL_COUNT (100)

//注册
#define _DEF_PACK_REGISTER_RQ	(_DEF_PROTOCOL_BASE + 0 )
#define _DEF_PACK_REGISTER_RS	(_DEF_PROTOCOL_BASE + 1 )
//登录
#define _DEF_PACK_LOGIN_RQ	(_DEF_PROTOCOL_BASE + 2 )
#define _DEF_PACK_LOGIN_RS	(_DEF_PROTOCOL_BASE + 3 )


//返回的结果
//注册请求的结果
#define zh_is_exist		(0)
#define name_is_exist		(1)
#define register_success	(2)
//登录请求的结果
#define user_not_exist		(0)
#define password_error		(1)
#define login_success		(2)

typedef int PackType;

//协议结构
//注册
typedef struct STRU_REGISTER_RQ
{
    STRU_REGISTER_RQ():type(_DEF_PACK_REGISTER_RQ)
    {
        memset( tel  , 0, sizeof(tel));
        memset( name  , 0, sizeof(name));
        memset( password , 0, sizeof(password) );
    }
    //需要手机号码 , 密码, 昵称
    PackType type;
    char tel[_MAX_SIZE];
    char name[_MAX_SIZE];
    char password[_MAX_SIZE];

}STRU_REGISTER_RQ;

typedef struct STRU_REGISTER_RS
{
    //回复结果
    STRU_REGISTER_RS(): type(_DEF_PACK_REGISTER_RS) , result(register_success)
    {
    }
    PackType type;
    int result;

}STRU_REGISTER_RS;

//登录
typedef struct STRU_LOGIN_RQ
{
    //登录需要: 手机号 密码
    STRU_LOGIN_RQ():type(_DEF_PACK_LOGIN_RQ)
    {
        memset( tel , 0, sizeof(tel) );
        memset( password , 0, sizeof(password) );
    }
    PackType type;
    char tel[_MAX_SIZE];
    char password[_MAX_SIZE];

}STRU_LOGIN_RQ;

typedef struct STRU_LOGIN_RS
{
    // 需要 结果 , 用户的id
    STRU_LOGIN_RS(): type(_DEF_PACK_LOGIN_RS) , result(login_success),userid(0)
    {
        memset( name , 0 , sizeof(name) );
    }
    PackType type;
    int result;
    int userid;
    char name[_MAX_SIZE];
}STRU_LOGIN_RS;

#define _MAX_PATH_SIZE (260)
//用户文件列表请求
#define _DEF_PACK_FILE_LIST_RQ	(_DEF_PROTOCOL_BASE + 4 )
//文件信息
#define _DEF_PACK_FILE_INFO	(_DEF_PROTOCOL_BASE + 5 )
//用户文件列表请求
struct STRU_FILE_LIST_RQ
{
    STRU_FILE_LIST_RQ():type(_DEF_PACK_FILE_LIST_RQ)
    ,userid(0){
        memset( dir , 0 , sizeof(dir) );
    }
    PackType type;
    int userid;
    char dir[_MAX_PATH_SIZE];
};

//文件信息
struct STRU_FILE_INFO
{
    STRU_FILE_INFO() :type(_DEF_PACK_FILE_INFO)
        , userid(0)
        , fileid(0)
        , size(0)
    {
        memset( filename , 0 , sizeof(filename) );
        memset( uploadTime , 0 , sizeof(uploadTime) );
        memset( dir , 0 , sizeof(dir) );
        memset( md5 , 0 , sizeof(md5) );
        memset(fileType, 0 , sizeof(fileType) );
    }
    PackType type;
    int userid;
    int fileid;

    char filename[_MAX_PATH_SIZE];
    char uploadTime[_MAX_SIZE];//"2023-01-01 10:13:23"
    int size;//不上传2GB以上的文件
    //2 147 483 647 2GB
    char dir[_MAX_PATH_SIZE];
    char md5[_MAX_SIZE];
    char fileType[_MAX_SIZE];//"file" "dir"
};
//文件下载
//文件下载请求
#define _DEF_PACK_FILE_DOWNLOAD_RQ      (_DEF_PROTOCOL_BASE + 6 )
//文件下载回复
#define _DEF_PACK_FILE_DOWNLOAD_RS      (_DEF_PROTOCOL_BASE + 7 )
//文件头请求
#define _DEF_PACK_FILE_HEAD_RQ          (_DEF_PROTOCOL_BASE + 8 )
//文件头回复
#define _DEF_PACK_FILE_HEAD_RS          (_DEF_PROTOCOL_BASE + 9 )
//文件内容请求
#define _DEF_PACK_FILE_CONTENT_RQ       (_DEF_PROTOCOL_BASE + 10 )
//文件内容回复
#define _DEF_PACK_FILE_CONTENT_RS       (_DEF_PROTOCOL_BASE + 11 )


//文件下载请求
struct STRU_DOWNLOAD_RQ
{
    STRU_DOWNLOAD_RQ(): type(_DEF_PACK_FILE_DOWNLOAD_RQ)
      , userid(0), fileid(0){

    }
    PackType type;
    int userid;
    int fileid;
};
//文件下载回复
struct STRU_DOWNLOAD_RS
{
    STRU_DOWNLOAD_RS(): type(_DEF_PACK_FILE_DOWNLOAD_RS)
      , userid(0), fileid(0),result(1){

    }
    PackType type;
    int userid;
    int fileid;
    int result;
};
//文件头请求
struct STRU_FILE_HEAD_RQ
{
    STRU_FILE_HEAD_RQ():type(_DEF_PACK_FILE_HEAD_RQ)
      ,fileid(0),size(0){
        memset( fileName , 0, sizeof(fileName) );
        memset( dir , 0, sizeof(dir) );
        memset( md5 , 0, sizeof(md5) );
        memset( fileType , 0, sizeof(fileType) );
    }
    PackType type;
    int fileid;
    char fileName[_MAX_PATH_SIZE];
    int size;//大小
    char dir[_MAX_PATH_SIZE];//路径
    char md5[_MAX_SIZE];
    char fileType[_MAX_SIZE];//文件类型
};
//文件头回复
struct STRU_FILE_HEAD_RS
{
    STRU_FILE_HEAD_RS(): type(_DEF_PACK_FILE_HEAD_RS)
      , userid(0), fileid(0),result(1){

    }
    PackType type;
    int userid;
    int fileid;
    int result;
};
//文件内容请求
struct STRU_FILE_CONTENT_RQ
{
    STRU_FILE_CONTENT_RQ():type(_DEF_PACK_FILE_CONTENT_RQ),
        userid(0),fileid(0),len(0){
        memset( content , 0 , sizeof(content));
    }
    PackType type;
    int userid;//1)userid
    int fileid;//2)fileid
    char content[_DEF_BUFFER];//3)文件内容
    int len;//4)长度
};
//文件内容回复
struct STRU_FILE_CONTENT_RS
{
    STRU_FILE_CONTENT_RS():type(_DEF_PACK_FILE_CONTENT_RS),
        userid(0),fileid(0),result(1){

    }
    PackType type;
    int userid;//1)userid
    int fileid;//2)fileid
    int result;//3)result
    int len;//4)长度
};





