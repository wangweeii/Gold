#pragma once

#include <string>
#include "mysql.h"

struct Bar
{
        std::string *time;
        double open, high, low, close, bid, ask;
};

// void back_test(MYSQL *db);
// void back_test(MYSQL *db, long long max);

void back_test(const char *dictionary);

void file_test(const char *file);

void bar_test(const Bar &bar);