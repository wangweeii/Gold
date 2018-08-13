//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <cstring>
#include <cstdio>

int main(int argc, char **argv)
{
        FILE       *fp   = fopen("d:/EURUSD.csv", "r");
        char       line[60];
        char       symbol[50];
        char       year[50];
        char       time[50];
        double     bid, ask;
        const char delim = ',';
        char       *result;


        // fscanf(fp, "%s %s", symbol, year);
        // printf("%s %s", symbol, year);
        // fscanf(fp, "%s,%s,%s", symbol, year, time);
        // printf("%s %s %s", symbol, year, time);
        for (int i = 0; i < 5; ++i)
        {
                fgets(line, 60, fp);
                // fscanf(fp, "%s,%s %s,%lf,%lf", symbol, year, time, &bid, &ask);
                printf("%s", line);
                // printf("%s %s %s %f %f\n", symbol, year, time, bid, ask);
                result = strtok(line, &delim);
                while (result)
                {
                        printf("%s---", result);
                        result = strtok(NULL, &delim);
                }
                printf("\n");
        }
        // fgets(line, 50, fp);
        // printf("%s\n", line);
        return 0;
}
