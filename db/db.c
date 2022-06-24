#include "db.h"

MYSQL mysql;                        //mysql句柄
const char *host = "127.0.0.1";     //本机地址
const char *user = "root";          //数据库用户名
const char *pwd = "123456";         //数据库登陆密码
const char *db = "cdb";             //数据库名
unsigned int port = 3306;           //mysql服务器端口
const char *unix_socket = NULL;     //win下设置为空
unsigned long client_flag = 0;      //这个参数一般为0
MYSQL_RES *result;                  //保存结果
MYSQL_ROW row;                      //代表的是结果集中的一行


void connectDb() {

    mysql_init(&mysql); //连接之前必须使用这个函数来初始化
    if ( mysql_real_connect(&mysql, host, user, pwd, db, port, unix_socket, client_flag) == NULL) //连接MySQL

    {
        printf("连接失败 \n");
        fprintf(stderr, " %s1\n", mysql_error(&mysql));

        exit(1);

    }
};

