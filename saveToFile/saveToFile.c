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