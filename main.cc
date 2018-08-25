//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <dirent.h>
#include <cstring>
#include <string>
#include "mysql.h"

char          line[60];
std::string   sql;
std::string   result;
struct dirent *ent;
//std::string   file = "/Users/vv/Downloads/tick/";

void insert2db(FILE *fp, MYSQL *db);
void file2db(const char *dictionary, MYSQL *db);
bool query(MYSQL *db, const char *sql);
void back_test(MYSQL *db);

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

        // sql = "select * from eurusd where id = 9;";
        // query(db, sql.c_str());
        // file2db("/home/vv/Downloads/tick", db);
        // query(db, "select * from eurusd where id<100000000;");
        back_test(db);

        mysql_close(db);
        printf("Connect Closed.\n");
        return 0;
}

void back_test(MYSQL *db)
{
        std::string time;
        double bid;
        double ask;
        double midpoint;
        // long long max=315258147;
        long long max = 10;
        long long id = 0;
        sql = "select time, bid, ask from eurusd where id = ";
        while(id++<max)
        {
                // std::cout << id << std::endl;
                // printf("%d %s\n", sql.length(), sql.c_str());
                // sql += std::to_string(id).c_str() + ';';
                // std::cout << sql.length() << " " << sql << std::endl;
                // sql.append(std::to_string(id));
                sql += ';';
                if (!query(db, sql.c_str()))
                {
                        break;
                }
                sql = "select id, time, bid, ask from eurusd where id = ";
        }
}

bool query(MYSQL *db, const char *sql)
{
        if (mysql_real_query(db, sql, strlen(sql)))
        {
                printf("Query Error!!!\n");
                printf("%s\n", sql);
                printf("%s\n", mysql_error(db));
                return false;
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
                return true;
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

