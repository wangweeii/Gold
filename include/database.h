#pragma once
#include <cstdio>
#include "mysql.h"

bool query_line(MYSQL *db, const char *sql);
void insert2db(FILE *fp, MYSQL *db);
void file2db(const char *dictionary, MYSQL *db);