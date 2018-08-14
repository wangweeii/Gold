//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <cstring>
#include <cstdio>

int main(int argc, char **argv)
{
        FILE *fp = fopen("d:/tick/EURUSD.csv", "r");
        char line[60];
        char *result;

        while (fgets(line, 60, fp))
        {
                line[strlen(line) - 1] = 0;
                result = strtok(line, ",");
                while (result)
                {
                        printf("%s ", result);
                        result = strtok(nullptr, ",");
                }
                printf("\n");
        }

        fclose(fp);
        printf("Shit");
        return 0;
}
