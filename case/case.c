#include "../myHead.h"
#include "stdlib.h"

void makeCase() {
    loginMenu();
    int Bool = 1;
    char instruction;
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
                printf("增加数据");
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
                printf("程序已退出");
                Bool = 0;
                break;

            default:
                printf("指令错误,请重新选择\n");
                break;
        }
    } while (Bool);

}