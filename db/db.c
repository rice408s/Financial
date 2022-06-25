#include "db.h"

MYSQL mysql;                        //mysql句柄
const char *host = "127.0.0.1";     //本机地址
const char *dbUser = "root";          //数据库用户名
const char *dbPwd = "123456";         //数据库登陆密码
const char *db = "cdb";             //数据库名
unsigned int port = 3306;           //mysql服务器端口
const char *unix_socket = NULL;     //win下设置为空
unsigned long client_flag = 0;      //这个参数一般为0
MYSQL_RES *result;                  //保存结果
MYSQL_ROW row;                      //代表的是结果集中的一行


void connectDb() {

    mysql_init(&mysql); //连接之前必须使用这个函数来初始化
    if (mysql_real_connect(&mysql, host, dbUser, dbPwd, db, port, unix_socket, client_flag) == NULL) //连接MySQL
    {
        printf("连接失败 \n");
        fprintf(stderr, " %s\n", mysql_error(&mysql));
        exit(1);
    }
    //创建表
    mysql_query(&mysql,"CREATE TABLE IF NOT EXISTS inf(\n"
                       "\tid INT auto_increment PRIMARY key not null COMMENT 'ID',\n"
                       "\tcreate_time datetime DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',\n"
                       "\tupdate_time datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',\n"
                       "\ttype VARCHAR(10) not NULL COMMENT '类型',\n"
                       "\tname VARCHAR(10)  not NULL COMMENT '姓名',\n"
                       "\tbedrag decimal(6,2) not NULL COMMENT '金额',\n"
                       "\tremark varchar(20) not NULL COMMENT '备注'\n"
                       ");\n"
                       "\n"
                       "CREATE TABLE if not EXISTS user(\n"
                       "\tid int auto_increment PRIMARY key not NULL COMMENT 'id',\n"
                       "\tname VARCHAR(10) not NULL COMMENT '名字',\n"
                       "\tpwd VARCHAR(20) not NULL COMMENT '密码'\n"
                       ")");
};

