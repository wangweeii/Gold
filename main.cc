//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include "mysql.h"

char        line[60];
std::string sql;
std::string result;

void insert2db(FILE *fp)
{
        //while (fgets(line, 60, fp))
        for (int i = 0; i < 5; i++)
        {
                fgets(line, 60, fp);// 从CSV文件中读取一行
                line[strlen(line) - 1] = 0;// 去掉行尾换行符
                result = strtok(line, ",");// 获取第一串字符'EURUSD'并丢掉

                // 拼装SQL语句
                result = strtok(nullptr, ",");
                sql    = "insert into eurusd(result, bid, ask) values('";
                sql += result + "', ";
                result = strtok(nullptr, ",");
                sql += result + ", ";
                result = strtok(nullptr, ",");
                sql += result + ");";

                // 插入数据库
                std::cout << sql << std::endl;
        }
}

int main(int argc, char *argv[])
{
        //FILE        *fp = fopen("d:/tick/EURUSD.csv", "r");
        // FILE *fp = fopen("/Users/vv/Downloads/tick/EURUSD-2009-05.csv", "r");
        //insert2db(fp);

        MYSQL *db = mysql_init(nullptr);
        if (mysql_real_connect(db, "127.0.0.1", "root", "", "test", 3306, nullptr, 0))
        {
                printf("Connect Success\n");
                mysql_close(db);
                printf("Close database!\n");
        }
        else
        {
                printf("Error!!\n");
        }

        /*sql = "select * from eurusd;";
        if (mysql_real_query(db, sql.c_str(), strlen(sql.c_str())))
        {
                printf("Query Error!!!\n");
        }
        else
        {
                MYSQL_RES *res = mysql_store_result(db);
                MYSQL_ROW row  = mysql_fetch_row(res);
                for (int  i    = 0; i < mysql_num_fields(res); ++i)
                {
                        printf("%s ", row[i]);
                }
        }*/

        /*
        //while (fgets(line, 60, fp))
        for (int i = 0; i < 100; i++)
        {
                fgets(line, 60, fp);
                line[strlen(line) - 1] = 0;
                //std::cout << line << std::endl;
                result = strtok(line, ",");
                // 拼装SQL语句
                result = strtok(nullptr, ",");
                sql    = "insert into eurusd(time, bid, ask) values('";
                sql += result + "', ";
                result = strtok(nullptr, ",");
                sql += result + ", ";
                result = strtok(nullptr, ",");
                sql += result + ");";

                // 执行SQL语句
                if (mysql_real_query(db, sql.c_str(), strlen(sql.c_str())))
                {
                        printf("Insert Error!!\n");
                        break;
                }
        }
         */
        // mysql_close(db);
        // fclose(fp);

        printf("Shit");
        return 0;
}
