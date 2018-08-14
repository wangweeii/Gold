//
// Created by wangwei on 08/10.
//

#include <iostream>
#include <cstring>
#include <cstdio>

int main(int argc, char **argv)
{
        FILE        *fp = fopen("d:/tick/EURUSD.csv", "r");
        char        line[60];
        std::string symbol;
        std::string time;
        std::string Bid;
        std::string Ask;

        while (fgets(line, 60, fp))
        {
                // line[strlen(line) - 1] = 0;
                symbol = strtok(line, ",");
                time   = strtok(nullptr, ",");
                Bid    = strtok(nullptr, ",");
                Ask    = strtok(nullptr, ",");
                printf("%s-%s: %g %g\n", symbol.c_str(), time.c_str(), atof(Bid.c_str()), atof(Ask.c_str()));
        }

        fclose(fp);
        printf("Shit");
        return 0;
}
