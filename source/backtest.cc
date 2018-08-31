// #include <string>
#include <cmath>
#include <cstring>
#include <dirent.h>
#include "database.h"
#include "backtest.h"

static const int LENGTH = 10000;

double fast[LENGTH] = {1.325355,};
double slow[LENGTH] = {1.325355,};
double open;
double high;
double low;
double close = 0;
std::string latest_time = "20090501 00:00:00.000";

unsigned int fast_step = 5;
unsigned int slow_step = 34;

double fast_alpha = 2.0 / (fast_step + 1);
double slow_alpha = 2.0 / (slow_step + 1);
double fast_beta = 1 - fast_alpha;
double slow_beta = 1 - slow_alpha;

double have_position = 0;
double open_price = 0;
double close_price = 0;
double place_ema = 0;
double highest = 0;
double lowest = 0;

int bar_count = 1;
double total_value = 9600;
double quantity = 0;
double stop = 0.0016;

bool traded = false;

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
                bar.time = time;
                bar.close = midpoint;
                bar.bid = bid;
                bar.ask = ask;

                // printf("%s, %f, %f, %f\n", time.c_str(), bid, ask, midpoint);
                // fast[0] = 1.325355;
                // slow[0] = 1.325355;
                ma_cross_test(bar);
        }
        fclose(fp);
}

void ma_cross_test(const Bar &bar)
{
        // printf("%s Open-%f High-%f Low-%f Close-%f Bid-%f Ask-%f\n", (bar.time).c_str(), bar.open, bar.high, bar.low, bar.close, bar.bid, bar.ask);
        if (latest_time != bar.time)
        {
                // printf("%s Open-%f High-%f Low-%f Close-%f\n", latest_time.c_str(), open, high, low, close);

                fast[bar_count] = fast_alpha * bar.close + fast_beta * fast[bar_count - 1];
                slow[bar_count] = slow_alpha * bar.close + slow_beta * slow[bar_count - 1];
                // printf("At %s, EMA(fast) and EMA(slow): %g, %g\n", latest_time.c_str(), fast[bar_count], slow[bar_count]);
                // printf("LiveBar. ReqId: %ld, Date: %s, Open: %g, High: %g, Low: %g, Close: %g\n", reqId, latest_time.c_str(), open, high, low, close);
                // std::cout << "The FAST EMA is: " << fast[bar_count] << ", SLOW EMA is: " << slow[bar_count] << std::endl;

                // 快线上穿慢线
                if (bar_count > 400 && fast[bar_count - 1] < slow[bar_count - 1] && fast[bar_count] >= slow[bar_count])
                {
                        if (have_position == 0 && !traded && close - fast[bar_count] <= 0.0010)
                        {
                                place_ema = fast[bar_count];
                                highest = close;
                                quantity = (int) (floor(total_value) / 500) * 10000;
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("BUY", quantity));
                                traded = true;
                                printf("--------------- %s, OPEN LONG %g at %g\n", bar.time.c_str(), quantity, close);
                        } else if (have_position < 0 && !traded)
                        {
                                place_ema = fast[bar_count];
                                highest = close;
                                quantity = (int) (floor(total_value) / 500) * 10000 - have_position;
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("BUY", quantity));
                                traded = true;
                                printf("--------------- %s, CLOS SHOT %g & OPEN LONG total %g at %g\n", bar.time.c_str(), -have_position, quantity,
                                       close);
                        }
                }

                // 快线下穿慢线
                if (bar_count > 400 && fast[bar_count - 1] > slow[bar_count - 1] && fast[bar_count] <= slow[bar_count])
                {
                        if (have_position == 0 && !traded && fast[bar_count] - close <= 0.0010)
                        {
                                place_ema = fast[bar_count];
                                lowest = close;
                                quantity = (int) (floor(total_value) / 500) * 10000;
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("SELL", quantity));
                                traded = true;
                                printf("--------------- %s, OPEN SHOT %g at %g\n", bar.time.c_str(), quantity, close);
                        } else if (have_position > 0 && !traded)
                        {
                                place_ema = fast[bar_count];
                                lowest = close;
                                quantity = (int) (floor(total_value) / 500) * 10000 + have_position;
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("SELL", quantity));
                                traded = true;
                                printf("--------------- %s, CLOS LONG %g & OPEN SHOT total %g at %g\n", bar.time.c_str(), have_position, quantity,
                                       close);
                        }
                }

                bar_count++;
                latest_time = bar.time;
                open = bar.open;
                high = bar.high;
                low = bar.low;
                close = bar.close;
        } else
        {
                // printf("%s Open-%f High-%f Low-%f Close-%f Bid-%f Ask-%f\n", (bar.time).c_str(), bar.open, bar.high, bar.low, bar.close, bar.bid, bar.ask);
                if (have_position > 0)
                {
                        if (bar.high > highest)
                        {
                                highest = bar.high;
                        }
                        // 多单盈利超过设定值又回调三分之一则平仓
                        if ((highest - place_ema) > stop && bar.close <= highest - (highest - place_ema) / 3 && !traded)
                        {
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("SELL", have_position));
                                traded = true;
                                printf("--------------- %s, STOP LONG %g at %g\n", bar.time.c_str(), have_position, bar.close);
                        }
                        // 多单未盈利直接止损
                        if ((bar.low - place_ema) <= -stop && !traded)
                        {
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("SELL", have_position));
                                traded = true;
                                printf("--------------- %s, LONG LOSS %g at %g\n", bar.time.c_str(), have_position, bar.close);
                        }
                } else if (have_position < 0)
                {
                        if (bar.low < lowest)
                        {
                                lowest = bar.low;
                        }
                        // 空单盈利超过设定值又回调三分之一则平仓
                        if ((lowest - place_ema) < -stop && bar.close >= lowest - (lowest - place_ema) / 3 && !traded)
                        {
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("BUY", -have_position));
                                traded = true;
                                printf("--------------- %s, STOP SHOT %g at %g\n", bar.time.c_str(), -have_position, bar.close);
                        }
                        // 空单未盈利直接止损
                        if ((bar.high - place_ema) >= stop && !traded)
                        {
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("BUY", -have_position));
                                traded = true;
                                printf("--------------- %s, SHOT LOSS %g at %g\n", bar.time.c_str(), -have_position, bar.close);
                        }
                }

                open = bar.open;
                high = bar.high;
                low = bar.low;
                close = bar.close;
        }
}