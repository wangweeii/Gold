#include <string>
#include "database.h"
#include "backtest.h"

void back_test(MYSQL *db)
{
        std::string time;
        double bid;
        double ask;
        double midpoint;
        // long long max=315258147;
        long long max = 10;
        long long id = 0;

        while(id++ < max)
        {
                std::string sql = "select time, bid, ask from eurusd where id = ";
                sql.append(std::to_string(id));
                sql += ';';
                if (!query_line(db, sql.c_str()))
                {
                        break;
                }
                // sql = "select id, time, bid, ask from eurusd where id = ";
        }
}