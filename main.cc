//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <dirent.h>
#include <cstring>
#include <string>
#include "database.h"

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

        std::string sql = "select time, bid, ask from eurusd where id = ";
        while(id++ < max)
        {
                // std::cout << id << std::endl;
                // printf("%d %s\n", sql.length(), sql.c_str());
                // sql += std::to_string(id).c_str() + ';';
                // std::cout << sql.length() << " " << sql << std::endl;
                sql.append(std::to_string(id));
                sql += ';';
                if (!query_line(db, sql.c_str()))
                {
                        break;
                }
                sql = "select id, time, bid, ask from eurusd where id = ";
        }
}