#include "../myHead.h"
#include "user.h"

const char *admin = "root";
const char *adminPwd = "123456";
char inputAdmin[10];
char inputPwd[10];
char newPwd[10];

const char *v1 = "insert into user (`name`,pwd) VALUES(\"";
const char *v2 = "select pwd from user where `name` = \"";
const char *v3="update `user` set pwd= \"";
char insertUser[100];
char queryUser[100];
char financialName[10];
char updateUser[100];

typedef struct User {
    char userName[10];
    char userPwd[10];
};

struct User user;


int signIn() {
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

int signUp() {
    printf("注册\n");
    printf("请输入管理员账号:");
    scanf("%s", inputAdmin);
    printf("请输入管理员密码:");
    scanf("%s", inputPwd);
    getchar();
    if (strcmp(admin, inputAdmin) != 0 || strcmp(adminPwd, inputPwd) != 0) {
        printf("管理员账号或密码错误\n");
        return 0;
    } else {
        printf("登录成功\n");
        printf("请创建用户名:");
        scanf("%s", &user.userName);
        getchar();
        printf("请创建用户密码:");
        scanf("%s", &user.userPwd);
        strcpy(insertUser,v1);
        strcat(insertUser, user.userName);
        strcat(insertUser, "\",\"");
        strcat(insertUser, user.userPwd);
        strcat(insertUser, "\");");
        mysql_query(&mysql, insertUser);
        getchar();
    }

}

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