//
// Created by wangwei on 08/10.
//

#include <iostream>
// #include <dirent.h>
// #include <cstring>
// #include <string>
// #include "database.h"
#include "backtest.h"

int main(int argc, char *argv[])
{
        /*
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
        back_test(db, 100000);

        mysql_close(db);
        */
        back_test("/opt/tick");
        printf("Connect Closed.\n");
        return 0;
}