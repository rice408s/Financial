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
    do {
        mainMenu();
        scanf("%c", &instruction);
        getchar();
        system("cls");
        switch (instruction) {
            case '1':
                if (signIn()==1){
                    login1=0;
                } else{
                    printf("登陆失败，请重试\n");
                }
                getchar();
                break;
            case '2':
                signUp();
                getchar();
                break;
            default:
                printf("重新选择");
        }
    } while (login1);


    do {
        appMenu();
        scanf("%c", &instruction);
        getchar();
        system("cls");
        switch (instruction) {
            case '1':
                queryAllInf();//查询所有数据
                break;

            case '2':
                insertInf();
                break;

            case '3':
                deleteInf();
                break;

            case '4':
                queryInf();
                break;

            case '5':
                updateInf();
                break;

            case '0':
                login2 = 0;
                break;

            default:
                printf("指令错误,请重新选择\n");
                break;
        }
    } while (login2);

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
const char *dbUser = "root";          //数据库用户名
const char *dbPwd = "123456";         //数据库登陆密码
const char *db = "cdb";             //数据库名
unsigned int port = 3306;           //mysql服务器端口
const char *unix_socket = NULL;     //win下设置为空
unsigned long client_flag = 0;      //这个参数一般为0
MYSQL_RES *result;                  //保存结果集的
MYSQL_ROW row;                      //代表的是结果集中的一行
void connectDb() {

    mysql_init(&mysql); //连接之前必须使用这个函数来初始化
    if ((sock = mysql_real_connect(&mysql, host, dbUser, dbPwd, db, port, unix_socket, client_flag)) == NULL) //连接MySQL

    {

        printf("连接失败 \n");

        fprintf(stderr, " %s1\n", mysql_error(&mysql));

        exit(1);

    } else {

        fprintf(stderr, "数据库连接成功\n");

    }

};
```

## 对账单数据的增删改查 ```financial.c```

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
mysql_query(&mysql, sqlInsert);
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

### 账单信息管理
```c
financial.c
```
```c
void queryInf() {
    strcpy(sqlQuery, "select * from inf where ");
    printf("\t1.按类型查找\t2.按姓名查找\t3.按金额查找\t4.按备注查找\n选择查询方式:");
    chooseType = getchar();
    switch (chooseType) {
        case '1':
            strcat(sqlQuery, "type = \"");
            break;

        case '2':
            strcat(sqlQuery, "`name` = \"");
            break;

        case '3':
            strcat(sqlQuery, "bedrag = ");
            break;

        case '4':
            strcat(sqlQuery, "remark = \"");
            break;
    }
    if (chooseType == '1' || chooseType == '2' || chooseType == '3' || chooseType == '4') {
        printf("请输入查询的数据(金额保留两位小数):");
        scanf("%s", Data);
        getchar();
        strcat(sqlQuery, Data);
        if (chooseType != '3') {
            strcat(sqlQuery, "\"");
        }
    }

    if (mysql_real_query(&mysql, sqlQuery, (unsigned long) strlen(sqlQuery))) {
        fprintf(stderr, "mysql_real_query failure!\n");
    } else {
        result = mysql_store_result(&mysql);

        if (result == NULL) {
            fprintf(stderr, "mysql_store_result failure！\n");
        } else {
            printf("序号        创 建 时 间                更 新 时 间         类型    姓名金额     备注\n");
            while (row = mysql_fetch_row(result)) {
                printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
                       row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            }
        }
    }
}
```
## 用户信息管理
```c
user.c
```

### 用户的注册
```c
int signUp() {
    printf("注册\n");
    printf("请输入管理员账号:");
    scanf("%s", inputAdmin);
    printf("请输入管理员密码:");
    scanf("%s", inputPwd);
    getchar();
    if (strcmp(admin, inputAdmin) != 0 || strcmp(adminPwd, inputPwd) != 0) {
        printf("管理员账号或密码错误");
        return 0;
    } else {
        printf("登录成功\n");
        printf("请创建用户名:");
        scanf("%s", &user.userName);
        getchar();
        printf("请创建用户密码:");
        scanf("%s", &user.userPwd);
        strcpy(insertUser,v1);
        strcat(insertUser, &user.userName);
        strcat(insertUser, "\",\"");
        strcat(insertUser, &user.userPwd);
        strcat(insertUser, "\");");
        mysql_query(&mysql, insertUser);
        getchar();
    }

}

```

### 用户的登录
```c
int signIn() {
    printf("登录\n");
    printf("请输入用户名:");
    scanf("%s", &user.userName);
    strcpy(financialName,user.userName);
    getchar();
    printf("请输入用户密码:");
    scanf("%s", &user.userPwd);
    strcpy(queryUser,v2);
    strcat(queryUser, user.userName);
    strcat(queryUser, "\";");
    getchar();


    if (mysql_real_query(&mysql, queryUser, (unsigned long) strlen(queryUser))) {
        fprintf(stderr, "mysql_real_query failure!\n");
        return 0;
    } else {
        result = mysql_store_result(&mysql);
        if (result == NULL) {
            fprintf(stderr, "mysql_store_result failure！\n");
            return 0;
        } else {
            row = mysql_fetch_row(result);
            while (row) {
                if (strcmp(user.userPwd, row[0]) == 0) {
                    printf("登陆成功\n");
                    return 1;
                } else {
                    printf("登录失败\n");
                    return 0;
                }
                row = mysql_fetch_row(result);
            }
        }
    }
}
```
### 用户的修改
```c
int changePwd(){
    printf("请输入用户名:");
    scanf("%s", &user.userName);
    strcpy(financialName,user.userName);
    getchar();
    printf("请输入用户密码:");
    scanf("%s", &user.userPwd);
    strcpy(queryUser,v2);
    strcat(queryUser, user.userName);
    strcat(queryUser, "\";");
    getchar();


    if (mysql_real_query(&mysql, queryUser, (unsigned long) strlen(queryUser))) {
        fprintf(stderr, "mysql_real_query failure!\n");
        return 0;
    } else {
        result = mysql_store_result(&mysql);
        if (result == NULL) {
            fprintf(stderr, "mysql_store_result failure！\n");
            return 0;
        } else {
            printf("请输入新密码:");
            scanf("%s",newPwd);
            getchar();
            row = mysql_fetch_row(result);
            while (row) {
                if (strcmp(user.userPwd, row[0]) == 0) {
                    strcpy(updateUser,v3);
                    strcat(updateUser,newPwd);
                    strcat(updateUser,"\" WHERE `name`= \"");
                    strcat(updateUser,user.userName);
                    strcat(updateUser,"\";");
                    mysql_query(&mysql,updateUser);
                    return 1;
                } else {
                    return 0;
                }
                row = mysql_fetch_row(result);
            }
        }
    }
}
```

## 数据从数据库写入到文件中

### 写入

```c
#include "saveToFile.h"

FILE *file;
const char *readAllInf = "select * from inf";

void saveData(){
    file= fopen("financial.txt","w+");
    if (mysql_real_query(&mysql, readAllInf, (unsigned long) strlen(readAllInf))) {
        fprintf(stderr, "mysql_real_query failure!\n");
    } else {
        result = mysql_store_result(&mysql);
        if (result == NULL) {
            fprintf(stderr, "mysql_store_result failure！\n");
        } else {
            fputs("序号      创 建 时 间          更 新 时 间      类型 姓名    金额  备注\n",file);
            while (row = mysql_fetch_row(result)) {
                for (int i = 0; i < 7; ++i) {
                    fputs(row[i],file);
                    fputs("\t",file);
                }
                fputs("\n",file);

            }
        }
    }
    fclose(file);
    mysql_close(&mysql);//断开与mysql的连接
}
```

