//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <cstring>
#include <dirent.h>
#include "mysql.h"

char          line[60];
std::string   sql;
std::string   result;
//std::string   file = "/Users/vv/Downloads/tick/";
struct dirent *ent;
DIR           *dir;

void insert2db(FILE *fp, MYSQL *db);
void file2db(DIR *dir, MYSQL *db);

int main(int argc, char *argv[])
{
        MYSQL *db = mysql_init(nullptr);

        if (mysql_real_connect(db, "127.0.0.1", "root", "", "test", 3306, nullptr, 0))
        {
                printf("Connect Success\n");
        }
        else
        {
                printf("Error: %s\n", mysql_error(db));
                return -1;
        }

        /*
        sql = "select * from eurusd;";
        if (mysql_real_query(db, sql.c_str(), strlen(sql.c_str())))
        {
                printf("Query Error!!!\n");
        }
        else
        {
                MYSQL_RES *res = mysql_store_result(db);
                MYSQL_ROW row  = mysql_fetch_row(res);
                while (row)
                {
                        for (int i = 1; i < mysql_num_fields(res); ++i)
                        {
                                //printf("%s, ", row[i]);
                        }
                        //printf("\n");
                        row        = mysql_fetch_row(res);
                }
        }
         */


        // 读取目录
        if ((dir = opendir("/Users/vv/Downloads/tick")) != nullptr)
        {
                file2db(dir,db);
        }
        else
        {
                printf("Open directory error!!\n");
        }

        mysql_close(db);
        return 0;
}

void file2db(DIR *dir, MYSQL *db)
{
        // 读取文件名
        while ((ent=readdir(dir))!= nullptr)
        {
                if (strlen(ent->d_name) > 4)
                {
                        std::string file = "/home/vv/Downloads/tick/";
                        file += ent->d_name;
                        FILE *fp = fopen(file.c_str(), "r");
                        insert2db(fp, db);
                        fclose(fp);
                        printf("Insert %s data end\n", ent->d_name);
                }
        }
        closedir(dir);
}

void insert2db(FILE *fp, MYSQL *db)
{
        //for (int i = 0; i < 2; i++)
        while (fgets(line, 60, fp))
        {
                fgets(line, 60, fp);// 从CSV文件中读取一行
                line[strlen(line) - 1] = ',';// 去掉行尾换行符
                result = strtok(line, ",");// 获取第一串字符'EURUSD'并丢掉

                // 拼装SQL语句
                sql    = "insert into eurusd(time, bid, ask) values('";
                result = strtok(nullptr, ",");
                sql += result + "', ";
                result = strtok(nullptr, ",");
                sql += result + ", ";
                result = strtok(nullptr, ",");
                sql += result + ");";

                // 插入数据库
                if (mysql_real_query(db, sql.c_str(), strlen(sql.c_str())))
                {
                        printf("Insert Error: %s\n", mysql_error(db));
                        break;
                }
        }
}

