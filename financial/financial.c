#include "financial.h"
#include "../myHead.h"


typedef struct Financial {
    char type[4];
    char bedRag[10];
    char remark[20];
};

struct Financial inf;
char sqlInsert[100];
char sqlDelete[100];
char sqlUpdate[100];
char sqlQuery[100];
const char *sqlAllQuery = "select * from inf";
const char *s1 = "insert into inf (type,`name`,bedrag,remark) VALUES(\""; //常量字符串,每输入一次数据，通过此字符串将sqlInsert重置
const char *s2 = "delete from inf where id = ";
const char *s3 = "update inf set ";

char id[4];
char chooseType;
char Data[20];
float sum;
//查询




void queryAllInf() {
    float sum = 0;
    //mysql_real_query如果成功,返回0 否则非0
    if (mysql_real_query(&mysql, sqlAllQuery, (unsigned long) strlen(sqlAllQuery))) {
        fprintf(stderr, "mysql_real_query failure!\n");
    } else {
        result = mysql_store_result(&mysql);
        if (result == NULL) {
            fprintf(stderr, "mysql_store_result failure！\n");
        } else {
            printf("序号        创 建 时 间                更 新 时 间         类型    姓名    金额     备注\n");
            while (row = mysql_fetch_row(result)) {
                sum += atof(row[5]);
                printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n",
                       row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            }
            printf("总余额:%.2f\n", sum);
        }
    }
}

void insertInf() {

    printf("请输入类型:");
    scanf("%s", &inf.type);
    printf("请输入金额:");
    scanf("%s", &inf.bedRag);
    if (fabs(atof(inf.bedRag)) < 0.01) {
        printf("数据非法\n");
    } else {
        printf("请输入备注:");
        scanf("%s", &inf.remark);
        //拼接插入数据的sql语句
        strcpy(sqlInsert, s1);
        strcat(sqlInsert, inf.type);
        strcat(sqlInsert, "\",\"");
        strcat(sqlInsert, financialName);
        strcat(sqlInsert, "\",");
        strcat(sqlInsert, inf.bedRag);
        strcat(sqlInsert, ",\"");
        strcat(sqlInsert, inf.remark);
        strcat(sqlInsert, "\");");
        //执行sql语句插入数据
        mysql_query(&mysql, sqlInsert);
    }
    getchar();
}

void deleteInf() {
    strcpy(sqlDelete, s2);
    printf("请输入要删除的id:");
    scanf("%s", id);
    strcat(sqlDelete, id);

    mysql_query(&mysql, sqlDelete);
    getchar();
}

void updateInf() {

    strcpy(sqlUpdate, s3);
    printf("请输入要修改的id:");
    scanf("%s", &id);
    printf("\n1.类型\t2.金额\t3.备注\t按其他键退出编辑\n请输入要修改的数据类型:");
    getchar();
    chooseType = getchar();
    getchar();
    switch (chooseType) {
        case '1':
            strcat(sqlUpdate, "type = \"");
            break;
        case '2':
            strcat(sqlUpdate, "bedrag = ");
            break;
        case '3':
            strcat(sqlUpdate, "remark = \"");
            break;

    }
    if (chooseType == '1' || chooseType == '2' || chooseType == '3') {

        printf("请输入修改后的数据:");
        scanf("%s", Data);
        if (chooseType=='2'&&fabs(atof(Data)) < 0.01) {
            printf("数据非法\n");
        }
        strcat(sqlUpdate, Data);

        if (chooseType != '2') {
            strcat(sqlUpdate, "\"");
        }

        strcat(sqlUpdate, " where id = ");
        strcat(sqlUpdate, id);

        mysql_query(&mysql, sqlUpdate);
        getchar();
    }
}

void queryInf() {
    sum = 0;
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
                sum += atof(row[5]);
                printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n",
                       row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            }
            printf("总余额:%.2f", sum);
        }
    }
}