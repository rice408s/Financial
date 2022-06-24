# 财务管理系统
## 菜单打印
### 打印菜单
```appMenu.c```
```c
#include "appMenu.h"
    printf("\n******************************************************\n");
    printf("******************欢迎使用财务管理系统1.0****************\n");
    printf("************************请选择:***********************\n");
    printf("************      1.    查询所有数据   ****************\n");
    printf("************      2.    增加          ****************\n");
    printf("************      3.    删除          ****************\n");
    printf("************      4.    查询          ****************\n");
    printf("************      5.    修改          ****************\n");
    printf("************      0.    退出          ****************\n");
    printf("请输入命令:");
```

### 循环执行菜单,输入指令，选择功能
```case.c```
```c
#include "case.h"
#include "../menu/appMenu.h"
void makeCase() {
    int Bool = 1;
    char instruction;
    do {
        appMenu();
        scanf("%c", &instruction);
        getchar();
        switch (instruction) {
            case '1':
                queryAllInf();//查询所有数据
                break;

            case '2':
                insertInf();//插入数据
                break;

            case '3':
                deleteInf();//删除数据
                break;

            case '4':
                            //按分类查询
                break;

            case '5':
                updateInf();//更新数据
                break;

            case '0':
                printf("程序已退出");//退出程序
                Bool = 0;
                break;

            default:
                printf("指令错误,请重新选择\n");
                break;
        }
    } while (Bool);

}
```

## 配置数据库连接
1. 下载安装 **mysql**
2. 安装驱动，找到mysql包下面的libmysql.dll和libmysql.lib文件复制进项目的cmake-build-debug文件中，在CMakeLists.txt文件中写入以下内容配置Clion与数据库连接
```txt
#配置数据库连接
include_directories(C:\\Program\ Files\\MySQL\\MySQL\ Server\ 8.0\\include)  #include文件夹路径,空格后面需要添加 \
link_directories(C:\\Program\ Files\\MySQL\\MySQL\ Server\ 8.0\\lib) #lib文件夹路径,空格后面需要添加  \
link_libraries(libmysql.lib libmysql.dll) #照抄
target_link_libraries(Financial libmysql) #(项目名 libmysql)
```

### 数据库连接```db.c```
```c
#include "db.h"
#include "mysql.h"


MYSQL mysql, *sock;                 //mysql句柄
const char *host = "127.0.0.1";     //本机地址
const char *user = "root";          //数据库用户名
const char *pwd = "123456";         //数据库登陆密码
const char *db = "cdb";             //数据库名
unsigned int port = 3306;           //mysql服务器端口
const char *unix_socket = NULL;     //win下设置为空
unsigned long client_flag = 0;      //这个参数一般为0
MYSQL_RES *result;                  //保存结果集的
MYSQL_ROW row;                      //代表的是结果集中的一行
void connectDb() {

    mysql_init(&mysql); //连接之前必须使用这个函数来初始化
    if ((sock = mysql_real_connect(&mysql, host, user, pwd, db, port, unix_socket, client_flag)) == NULL) //连接MySQL

    {

        printf("连接失败 \n");

        fprintf(stderr, " %s1\n", mysql_error(&mysql));

        exit(1);

    } else {

        fprintf(stderr, "数据库连接成功\n");

    }

};
```
## 增删改查 ```db.c```
### 查询所有数据,并打印
```c
void queryAllInf() {
    //mysql_real_query如果成功,返回0 否则非0
    if (mysql_real_query(&mysql, sqlAllQuery, (unsigned long) strlen(sqlAllQuery))) {
        fprintf(stderr, "mysql_real_query err");

    } else {
        result = mysql_store_result(&mysql);
        if (result == NULL) {
            fprintf(stderr, "mysql_store_result failure！\n");
        } else {
            printf("序号        创 建 时 间                更 新 时 间         类型    姓名    金额     备注\n");
            while (row = mysql_fetch_row(result)) {
                printf("%s1\t%s1\t%s1\t%s1\t%s1\t%s1\t%s1\n",
                       row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            }
        }
    }
}
```
### 插入数据
```c
//数据结构体
typedef struct Financial {
    char type[4];
    char name[5];
    char bedRag[10];
    char remark[20];
};
struct Financial inf;//定义结构体对象
char sqlInsert[100] = "insert into inf (type,`name`,bedrag,remark) VALUES(\"";//sql语句

void insertInf() {
    //输入数据信息
    printf("请输入类型:");
    scanf("%s1", &inf.type);
    printf("请输入姓名:");
    scanf("%s1", &inf.name);
    printf("请输入金额:");
    scanf("%s1", &inf.bedRag);
    printf("请输入备注:");
    scanf("%s1", &inf.remark);

    //拼接插入数据的sql语句
    strcat(sqlInsert, inf.type);
    strcat(sqlInsert, "\",\"");
    strcat(sqlInsert, inf.name);
    strcat(sqlInsert, "\",");
    strcat(sqlInsert, inf.bedRag);
    strcat(sqlInsert, ",\"");
    strcat(sqlInsert, inf.remark);
    strcat(sqlInsert, "\");");
    //执行sql语句插入数据
    mysql_query(&mysql,sqlInsert);
}
```
### 删除数据
```c
void deleteInf() {
    strcpy(sqlDelete, s2);
    printf("请输入要删除的id:");
    scanf("%s", id);
    strcat(sqlDelete, id);

    mysql_query(&mysql, sqlDelete);
    getchar();
}
```

### 更新数据
```c
void updateInf() {

    strcpy(sqlUpdate, s3);
    printf("请输入要修改的id:");
    scanf("%s", &id);
    printf("\n1.类型\t2.姓名\t3.金额\t4.备注\n请输入要修改的数据类型:");
    getchar();
    chooseType=getchar();
    getchar();
    switch (chooseType) {
        case '1':
            strcat(sqlUpdate, "type = \"");
            break;
        case '2':
            strcat(sqlUpdate,"name = \"");
            break;
        case '3':
            strcat(sqlUpdate,"bedrag = ");
            break;
        case '4':
            strcat(sqlUpdate,"remark = \"");
    }
    printf("chooseid %c",chooseType);
    printf("请输入修改后的数据:");
    scanf("%s",Data);
    strcat(sqlUpdate,Data);
    if (chooseType!='3'){
        strcat(sqlUpdate,"\"");
    }
    strcat(sqlUpdate," where id = ");
    strcat(sqlUpdate,id);

    mysql_query(&mysql, sqlUpdate);
    getchar();
}
```