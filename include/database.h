#pragma once
#include <cstdio>
#include "mysql.h"

void insert2db(FILE *fp, MYSQL *db);
void file2db(const char *dictionary, MYSQL *db);
bool query_line(MYSQL *db, const char *sql);
long long get_max_id(MYSQL *db);