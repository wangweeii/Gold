#pragma once
#ifndef testcppclient_h__INCLUDED
#define testcppclient_h__INCLUDED

#include <string>
#include "mysql.h"

struct Bar
{
        std::string time;
        double open, high, low, close, bid, ask;
};

// void back_test(MYSQL *db);
// void back_test(MYSQL *db, long long max);

void back_test(const char *dictionary);

void file_test(std::string file);

void macd_test(const Bar &bar);

void ma_cross_test(const Bar &bar);

void place_order(double quantity, double price);

#endif