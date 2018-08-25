#include <string>
#include "database.h"
#include "backtest.h"

void back_test(MYSQL *db)
{
        long long max=315258147;

        back_test(db, max);
}

void back_test(MYSQL *db, long long max)
{
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
                sql.shrink_to_fit();
        }
}