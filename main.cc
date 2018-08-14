//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <cstring>
#include <cstdio>

int main(int argc, char **argv)
{
        FILE *fp   = fopen("d:/EURUSD.csv", "r");
        char line[60];
        char delim = ',';
        char *result;
        fgets(line,60,fp);
        printf("%s",line);

        while (fgets(line, 60, fp))
        {
                printf("%d %s", strlen(line), line);
                line[strlen(line) - 1] = 0;
                printf("%d %s\n", strlen(line), line);
                result = strtok(line, &delim);
                printf("%s",result);
                while (result)
                {
                        printf("%s\t", result);
                        result = strtok(nullptr, &delim);
                        // result=strtok(NULL,",");
                }
                printf("\n");
        }
        fclose(fp);
        printf("Shit");
        return 0;
}
