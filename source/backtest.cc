// #include <string>
#include <cmath>
#include <cstring>
#include <dirent.h>
#include "database.h"
#include "backtest.h"

static const long long LENGTH = 1000000;

double      fast[LENGTH] = {1.325355,};
double      slow[LENGTH] = {1.325355,};
double      macd[LENGTH];
double      open         = 1.324435;
double      high         = 1.324435;
double      low          = 1.324435;
double      close        = 1.324435;
double      pre_close;
std::string latest_time  = "20090501 00:00:00.000";

unsigned int fast_step = 12;
unsigned int slow_step = 55;

double fast_alpha = 2.0 / (fast_step + 1);
double slow_alpha = 2.0 / (slow_step + 1);
double fast_beta  = 1 - fast_alpha;
double slow_beta  = 1 - slow_alpha;

double have_position = 0;
double open_price    = 0;
double close_price   = 0;
double place_ema     = 0;
double highest       = 0;
double lowest        = 0;

int    bar_count   = 1;
double total_value = 9600;
double quantity    = 0;
double stop        = 0.0016;
double open_diff   = 0.0010;
double fee         = 0;

double macd_stop = 0.006;

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
        struct dirent **namelist;
        DIR           *dir;
        if ((dir = opendir(dictionary)) != nullptr)
        {
                printf("Begin to test files in %s\n", dictionary);

                int n = scandir(dictionary, &namelist, 0, alphasort);
                if (n < 0)
                {
                        printf("Scandir ERROR\n");
                }
                else
                {
                        for (int i = 0; i < n; ++i)
                        {
                                if (strlen(namelist[i]->d_name) > 10)
                                {
                                        std::string file = dictionary;
                                        file += namelist[i]->d_name;
                                        printf("%s\n", file.c_str());
                                        file_test(file);
                                }
                        }
                }

                /*
                while ((ent = readdir(dir)) != nullptr)
                {
                        if (strlen(ent->d_name) > 4)
                        {
                                std::string file = dictionary;
                                file += ent->d_name;
                                // printf("%s\n", file.c_str());
                                // file_test(file);
                        }
                }
                 */
                closedir(dir);
        }
}

void file_test(std::string file)
{
        char        line[60];
        std::string time;
        double      bid, ask, midpoint;
        int         int_time, sub_time, previous_hour = -1;
        Bar         bar;
        printf("Begin to test %s\n", file.c_str());
        FILE *fp = fopen(file.c_str(), "r");
        while (fgets(line, 60, fp))
        {
                line[strlen(line) - 1] = ',';

                // printf("%s", line);

                time     = strtok(line, ",");
                time     = strtok(nullptr, ",");
                bid      = atof(strtok(nullptr, ","));
                ask      = atof(strtok(nullptr, ","));
                midpoint = (bid + ask) / 2;

                // sub_time = (time[9] - '0') * 10 + (time[10] - '0');
                // int_time = sub_time - (sub_time % 4);
                // sub_time      = (time[12] - '0') * 10 + (time[13] - '0');
                // int_time = sub_time - (sub_time % 15);
                sub_time = (time[15] - '0') * 10 + (time[16] - '0');
                int_time = sub_time - (sub_time % 5);

                // time[9]   = char('0' + (int_time / 10));
                // time[10]  = char('0' + (int_time % 10));
                // time[12]  = '0';
                // time[13]  = '0';
                // time[12]  = char('0' + (int_time / 10));
                // time[13]  = char('0' + (int_time % 10));
                // time[15]  = '0';
                // time[16]  = '0';
                time[15]  = char('0' + (int_time / 10));
                time[16]  = char('0' + (int_time % 10));
                time[18]  = '0';
                time[19]  = '0';
                time[20]  = '0';
                if (previous_hour != int_time)
                {
                        bar.open = midpoint;
                        bar.high = midpoint;
                        bar.low  = midpoint;
                }
                else
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
                bar.time  = time;
                bar.close = midpoint;
                bar.bid   = bid;
                bar.ask   = ask;

                // printf("%s Open-%f High-%f Low-%f Close-%f Bid-%f Ask-%f\n", (bar.time).c_str(), bar.open, bar.high, bar.low, bar.close, bar.bid, bar.ask);
                // ma_cross_test(bar);
                // macd_test(bar);
                seconds_test(bar);
        }
        fclose(fp);
}

// 对秒级的数据进行测试
void seconds_test(const Bar &bar)
{
        //shit
        if (latest_time != bar.time)
        {
                int sub_time = (bar.time[9] - '0') * 10 + (bar.time[10] - '0');
                fast[bar_count] = fast_alpha * bar.close + fast_beta * fast[bar_count - 1];
                if (bar_count > 500 && close >= fast[bar_count] && pre_close < fast[bar_count - 1])
                {
                        // close short
                        if (have_position < 0)
                        {
                                highest  = close;
                                printf("--------------- %s, CLOS SHOT %f at %f\n", bar.time.c_str(), -have_position, bar.ask);
                                place_order(-have_position, bar.ask);
                        }
                        // open long
                        if (have_position == 0 && 10 < sub_time && sub_time < 23)
                        {
                                highest = close;
                                quantity = (int) (floor(total_value) / 500) * 10000;
                                printf("--------------- %s, OPEN LONG %f at %f\n", bar.time.c_str(), quantity, bar.ask);
                                place_order(quantity, bar.ask);
                                open_price = bar.ask;
                        }
                }
                else if (bar_count > 500 && close <= fast[bar_count] && pre_close > fast[bar_count - 1])
                {
                        // close long
                        if (have_position > 0)
                        {
                                lowest = close;
                                printf("--------------- %s, CLOS LONG %f at %f\n", bar.time.c_str(), -have_position, bar.bid);
                                place_order(-have_position, bar.bid);
                        }
                        // open short
                        if (have_position == 0 && 10 < sub_time && sub_time < 23)
                        {
                                lowest = close;
                                quantity = (int) (floor(total_value) / 500) * 10000;
                                printf("--------------- %s, OPEN SHOT %f at %f\n", bar.time.c_str(), quantity, bar.bid);
                                place_order(-quantity, bar.bid);
                                open_price = bar.bid;
                        }
                }
                if (total_value < 5000)
                        return;
                pre_close = close;
                bar_count++;
                latest_time = bar.time;
                open = bar.open;
                high = bar.high;
                low = bar.low;
                close = bar.close;
        }
        else
        {
                // if (have_position > 0)
                // {
                        // stop
                // }
                // else if (have_position < 0)
                // {
                        // stop
                // }
                open = bar.open;
                high = bar.high;
                low = bar.low;
                close = bar.close;
        }
}

void macd_test(const Bar &bar)
{
        if (latest_time != bar.time)
        {
                fast[bar_count] = fast_alpha * bar.close + fast_beta * fast[bar_count - 1];
                slow[bar_count] = slow_alpha * bar.close + slow_beta * slow[bar_count - 1];
                macd[bar_count] = fast[bar_count] - slow[bar_count];

                if (bar_count > 400 && macd[bar_count] > macd[bar_count - 1] && macd[bar_count - 1] < macd[bar_count - 2])
                {
                        // buy
                        if (have_position == 0)
                        {
                                highest  = close;
                                quantity = (int) (floor(total_value) / 500) * 10000;
                                printf("--------------- %s, OPEN LONG %f at %f\n", bar.time.c_str(), quantity, bar.ask);
                                place_order(quantity, bar.ask);
                                open_price = bar.ask;
                        }
                        else if (have_position < 0)
                        {
                                highest  = close;
                                quantity = (int) (floor(total_value) / 500) * 10000 - have_position;
                                printf("--------------- %s, CLOS SHOT %f & OPEN LONG total %f at %g\n", bar.time.c_str(), -have_position, quantity,
                                       bar.ask);
                                place_order(quantity, bar.ask);
                                open_price = bar.ask;
                        }
                }
                else if (bar_count > 400 && macd[bar_count] < macd[bar_count - 1] && macd[bar_count - 1] > macd[bar_count - 2])
                {
                        // sell
                        if (have_position == 0)
                        {
                                lowest   = close;
                                quantity = (int) (floor(total_value) / 500) * 10000;
                                printf("--------------- %s, OPEN SHOT %f at %f\n", bar.time.c_str(), quantity, bar.bid);
                                place_order(-quantity, bar.bid);
                                open_price = bar.bid;
                        }
                        else if (have_position > 0)
                        {
                                lowest   = close;
                                quantity = (int) (floor(total_value) / 500) * 10000 + have_position;
                                printf("--------------- %s, CLOS LONG %f & OPEN SHOT total %f at %g\n", bar.time.c_str(), have_position, quantity,
                                       bar.bid);
                                place_order(-quantity, bar.bid);
                                open_price = bar.bid;
                        }
                }

                bar_count++;
                latest_time = bar.time;
                open        = bar.open;
                high        = bar.high;
                low         = bar.low;
                close       = bar.close;
        }
        else
        {
                // stop loss
                if (have_position > 0)
                {
                        if (bar.close > highest)
                        {
                                highest = bar.close;
                        }

                        // if ((highest - open_price) >= macd_stop && bar.close < (highest - (highest - open_price) / 3))
                        // {
                        //         printf("--------------- %s, STOP LONG %f at %f\n", bar.time.c_str(), have_position, bar.bid);
                        //         place_order(-have_position, bar.bid);
                        // }
                        else if ((open_price - bar.close) >= macd_stop)
                        {
                                printf("--------------- %s, LONG LOSS %f at %f\n", bar.time.c_str(), have_position, bar.bid);
                                place_order(-have_position, bar.bid);
                        }
                }
                else if (have_position < 0)
                {
                        if (bar.close < lowest)
                        {
                                lowest = bar.close;
                        }

                        // if ((open_price - lowest) >= macd_stop && bar.close > (lowest + (open_price - lowest) / 3))
                        // {
                        //         printf("--------------- %s, STOP SHOT %f at %f\n", bar.time.c_str(), -have_position, bar.ask);
                        //         place_order(-have_position, bar.ask);
                        // }
                        if ((bar.close - open_price) >= macd_stop)
                        {
                                printf("--------------- %s, SHOT LOSS %f at %f\n", bar.time.c_str(), -have_position, bar.ask);
                                place_order(-have_position, bar.ask);
                        }
                }
                open  = bar.open;
                high  = bar.high;
                low   = bar.low;
                close = bar.close;
        }
}

void ma_cross_test(const Bar &bar)
{
        // printf("%s Open-%f High-%f Low-%f Close-%f Bid-%f Ask-%f\n", (bar.time).c_str(), bar.open, bar.high, bar.low, bar.close, bar.bid, bar.ask);
        if (latest_time != bar.time)
        {
                // printf("%s Open-%f High-%f Low-%f Close-%f\n", latest_time.c_str(), open, high, low, close);

                fast[bar_count] = fast_alpha * bar.close + fast_beta * fast[bar_count - 1];
                slow[bar_count] = slow_alpha * bar.close + slow_beta * slow[bar_count - 1];
                // printf("At %s, EMA(fast) and EMA(slow): %f, %f\n", latest_time.c_str(), fast[bar_count], slow[bar_count]);
                // printf("LiveBar. ReqId: %ld, Date: %s, Open: %g, High: %g, Low: %g, Close: %g\n", reqId, latest_time.c_str(), open, high, low, close);
                // std::cout << "The FAST EMA is: " << fast[bar_count] << ", SLOW EMA is: " << slow[bar_count] << std::endl;

                // 快线上穿慢线
                if (bar_count > 400 && fast[bar_count - 1] < slow[bar_count - 1] && fast[bar_count] >= slow[bar_count])
                {
                        if (have_position == 0 && !traded && close - fast[bar_count] <= open_diff)
                        {
                                place_ema = fast[bar_count];
                                highest   = close;
                                quantity  = (int) (floor(total_value) / 500) * 10000;
                                printf("--------------- %s, OPEN LONG %f at %f\n", bar.time.c_str(), quantity, bar.ask);
                                place_order(quantity, bar.ask);
                                open_price = bar.ask;
                        }
                        else if (have_position < 0 && !traded)
                        {
                                place_ema = fast[bar_count];
                                highest   = close;
                                quantity  = (int) (floor(total_value) / 500) * 10000 - have_position;
                                printf("--------------- %s, CLOS SHOT %f & OPEN LONG total %f at %g\n", bar.time.c_str(), -have_position, quantity,
                                       bar.ask);
                                place_order(quantity, bar.ask);
                                open_price = bar.ask;
                        }
                }

                // 快线下穿慢线
                if (bar_count > 400 && fast[bar_count - 1] > slow[bar_count - 1] && fast[bar_count] <= slow[bar_count])
                {
                        if (have_position == 0 && !traded && fast[bar_count] - close <= open_diff)
                        {
                                place_ema = fast[bar_count];
                                lowest    = close;
                                quantity  = (int) (floor(total_value) / 500) * 10000;
                                printf("--------------- %s, OPEN SHOT %f at %f\n", bar.time.c_str(), quantity, bar.bid);
                                place_order(-quantity, bar.bid);
                                open_price = bar.bid;
                        }
                        else if (have_position > 0 && !traded)
                        {
                                place_ema = fast[bar_count];
                                lowest    = close;
                                quantity  = (int) (floor(total_value) / 500) * 10000 + have_position;
                                printf("--------------- %s, CLOS LONG %f & OPEN SHOT total %f at %g\n", bar.time.c_str(), have_position, quantity,
                                       bar.bid);
                                place_order(-quantity, bar.bid);
                                open_price = bar.bid;
                        }
                }

                bar_count++;
                latest_time = bar.time;
                open        = bar.open;
                high        = bar.high;
                low         = bar.low;
                close       = bar.close;
        }
        else
        {
                // printf("%s Open-%f High-%f Low-%f Close-%f Bid-%f Ask-%f\n", (bar.time).c_str(), bar.open, bar.high, bar.low, bar.close, bar.bid, bar.ask);
                if (have_position > 0)
                {
                        if (bar.close > highest)
                        {
                                highest = bar.close;
                        }
                        // 多单盈利超过设定值又回调三分之一则平仓
                        if ((highest - open_price) >= stop && bar.close <= (highest - (highest - open_price) / 3) && !traded)
                        {
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("SELL", have_position));
                                // traded = true;
                                printf("--------------- %s, STOP LONG %f at %f\n", bar.time.c_str(), have_position, bar.bid);
                                place_order(-have_position, bar.bid);
                                // have_position = 0;
                        }
                        // 多单未盈利直接止损
                        if ((open_price - bar.close) >= stop && !traded)
                        {
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("SELL", have_position));
                                // traded = true;
                                printf("--------------- %s, LONG LOSS %f at %f\n", bar.time.c_str(), have_position, bar.bid);
                                place_order(-have_position, bar.bid);
                                // have_position = 0;
                        }
                }
                else if (have_position < 0)
                {
                        if (bar.close < lowest)
                        {
                                lowest = bar.low;
                        }
                        // 空单盈利超过设定值又回调三分之一则平仓
                        if ((open_price - lowest) >= stop && bar.close >= (lowest + (open_price - lowest) / 3) && !traded)
                        {
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("BUY", -have_position));
                                // traded = true;
                                printf("--------------- %s, STOP SHOT %f at %f\n", bar.time.c_str(), -have_position, bar.ask);
                                place_order(-have_position, bar.ask);
                                // have_position = 0;
                        }
                        // 空单未盈利直接止损
                        if ((open_price - bar.close) >= stop && !traded)
                        {
                                // m_pClient->placeOrder(m_orderId++, ContractSamples::EurUsdFx(), OrderSamples::MarketOrder("BUY", -have_position));
                                // traded = true;
                                printf("--------------- %s, SHOT LOSS %f at %f\n", bar.time.c_str(), -have_position, bar.ask);
                                place_order(-have_position, bar.ask);
                                // have_position = 0;
                        }
                }

                open  = bar.open;
                high  = bar.high;
                low   = bar.low;
                close = bar.close;
        }
}

void place_order(double quantity, double price)
{
        if (have_position > 0)
        {
                total_value += have_position * (price - open_price);
        }
        else if (have_position < 0)
        {
                total_value += have_position * (price - open_price);
        }
        if (quantity > 0)
        {
                if (quantity * price / 50000 > 2)
                {
                        fee += quantity * price / 50000;
                        total_value -= quantity * price / 50000;
                }
                else
                {
                        fee += 2;
                        total_value -= 2;
                }
        }
        else if (quantity < 0)
        {
                if (quantity * price / 50000 < -2)
                {
                        fee -= quantity * price / 50000;
                        total_value += quantity * price / 50000;
                }
                else
                {
                        fee += 2;
                        total_value -= 2;
                }
        }
        have_position += quantity;
        printf("Total value: %f, Position: %f, Total fee: %f\n", total_value, have_position, fee);
}