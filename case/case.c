#include "../myHead.h"
#include "stdlib.h"

int login1 = 1;
int login2 = 1;

char instruction;

void makeCase() {
    //用户注册登录
    do {
        mainMenu();
        scanf("%c", &instruction);//输入指令
        getchar();
        system("cls");//清屏
        switch (instruction) {
            case '1':
                if (signIn() == 1) {//判断登录情况
                    login1 = 0;
                } else {
                    printf("登陆失败，请重试\n");
                }
                break;
            case '2':
                signUp();//注册
                break;

            case '3':
                if (changePwd() == 1) {
                    printf("修改密码成功!\n");
                } else {
                    printf("修改密码失败,请重试\n");
                }
                break;

            default:
                printf("重新选择");
        }
    } while (login1);

    //用户操作
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
                insertInf();//
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