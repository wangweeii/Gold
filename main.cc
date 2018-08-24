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
struct dirent *ent;
//std::string   file = "/Users/vv/Downloads/tick/";

void insert2db(FILE *fp, MYSQL *db);
void file2db(const char *dictionary, MYSQL *db);
void query(MYSQL *db, const char *sql);

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

        // file2db("/home/vv/Downloads/tick", db);
        query(db, "select id, time, bid, ask from eurusd where id<30;");

        mysql_close(db);
        printf("Connect Closed.\n");
        return 0;
}

void query(MYSQL *db, const char *sql)
{
        if (mysql_real_query(db, sql, strlen(sql)))
        {
                printf("Query Error!!!\n");
        }
        else {
                MYSQL_RES *res = mysql_store_result(db);
                MYSQL_ROW row  = mysql_fetch_row(res);
                while (row)
                {
                        for (int i = 0; i < mysql_num_fields(res); ++i) {
                                printf("%s ",row[i]);
                        }
                        printf("\n");
                        row = mysql_fetch_row(res);
                }
        }
}

void file2db(const char *dictionary, MYSQL *db)
{
        // 读取目录
        DIR *dir;
        if ((dir = opendir(dictionary)) != nullptr)
        {
                printf("Begin to insert into database.\n");
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
        else
        {
                printf("Open directory error!!\n");
        }
}

void insert2db(FILE *fp, MYSQL *db)
{
        // 开始事务
        sql = "begin";
        mysql_real_query(db, sql.c_str(), strlen(sql.c_str()));

        while (fgets(line, 60, fp))
        {
                fgets(line, 60, fp);// 从CSV文件中读取一行
                line[strlen(line) - 1] = ',';// 去掉行尾换行符
                result = strtok(line, ",");// 获取第一串字符'EURUSD'并丢掉

                // 拼接SQL语句
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
                        sql = "rollback";
                        mysql_real_query(db, sql.c_str(), strlen(sql.c_str()));
                        break;
                }/*else
                {
                        printf("%s\n", sql.c_str());
                }*/
        }
        // 结束事务
        sql = "commit";
        mysql_real_query(db, sql.c_str(), strlen(sql.c_str()));
}

