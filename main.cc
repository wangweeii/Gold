//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <cstring>
#include <cstdio>

int main(int argc, char **argv)
{
        FILE       *fp     = fopen("d:/EURUSD.csv", "r");
        char       line[60];
        const char delim   = ',';
        char       *result = nullptr;

        while (fgets(line, 60, fp))
        {
                // printf("%s", line);
                result = strtok(line, &delim);
                while (result)
                {
                        printf("%s ", result);
                        result = strtok(nullptr, &delim);
                }
        }

        fclose(fp);
        printf("Shit");
        return 0;
}
