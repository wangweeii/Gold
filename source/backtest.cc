#include <string>
#include <cstring>
#include <dirent.h>
#include "database.h"
#include "backtest.h"

/*
void back_test(MYSQL *db)
{
        long long max = 315258147;

        back_test(db, max);
}

void back_test(MYSQL *db, long long max)
{
        long long id = 0;
        while (id++ < max)
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
*/

void back_test(const char *dictionary)
{
        struct dirent *ent;
        DIR *dir;
        if ((dir = opendir(dictionary)) != nullptr)
        {
                printf("Begin to test files in %s\n", dictionary);

                while ((ent = readdir(dir)) != nullptr)
                {
                        if (strlen(ent->d_name) > 4)
                        {
                                std::string file = "/opt/tick/";
                                file += ent->d_name;
                                file_test(file.c_str());
                        }
                }
        }
}

void file_test(const char *file)
{
        char line[60], hour[3];
        std::string raw_time, bar_time;
        double bid, ask, midpoint;
        FILE *fp = fopen(file, "r");
        while (fgets(line, 60, fp))
        {
                line[strlen(line) - 1] = ',';
                raw_time = strtok(line, ",");
                raw_time = strtok(nullptr, ",");
                hour[0] = raw_time[9];
                hour[1] = raw_time[10];
                bar_time = raw_time.substr(0, 9);
                bar_time += hour;
                bid = atof(strtok(nullptr, ","));
                ask = atof(strtok(nullptr, ","));
                midpoint = (bid + ask) / 2;
                // printf("%s, %f, %f, %f\n", raw_time.c_str(), bid, ask, midpoint);
                printf("%s, %f, %f, %f\n", bar_time.c_str(), bid, ask, midpoint);
        }
        fclose(fp);
}