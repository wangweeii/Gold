// #include <string>
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
        char line[60];
        std::string time;
        double bid, ask, midpoint;
        int time_hour, hour, previous_hour = -1;
        Bar bar;
        FILE *fp = fopen(file, "r");
        while (fgets(line, 60, fp))
        {
                line[strlen(line) - 1] = ',';

                time = strtok(line, ",");
                time = strtok(nullptr, ",");
                bid = atof(strtok(nullptr, ","));
                ask = atof(strtok(nullptr, ","));
                midpoint = (bid + ask) / 2;

                hour = (time[9] - '0') * 10 + (time[10] - '0');
                time_hour = hour - (hour % 4);

                time[9] = char('0' + (time_hour / 10));
                time[10] = char('0' + (time_hour % 10));
                time[12] = '0';
                time[13] = '0';
                time[15] = '0';
                time[16] = '0';
                time[18] = '0';
                time[19] = '0';
                time[20] = '0';
                if (previous_hour != time_hour)
                {
                        bar.open = midpoint;
                        bar.high = midpoint;
                        bar.low = midpoint;
                } else
                {
                        if (midpoint > bar.high)
                        {
                                bar.high = midpoint;
                        }
                        if (midpoint < bar.low)
                        {
                                bar.low = midpoint;
                        }
                }
                bar.time = &time;
                bar.close = midpoint;
                bar.bid = bid;
                bar.ask = ask;

                // printf("%s, %f, %f, %f\n", time.c_str(), bid, ask, midpoint);
                bar_test(bar);
        }
        fclose(fp);
}

void bar_test(const Bar &bar)
{
        printf("%s Open-%f High-%f Low-%f Close-%f Bid-%f Ask-%f\n", (*bar.time).c_str(), bar.open, bar.high, bar.low, bar.close, bar.bid, bar.ask);
}