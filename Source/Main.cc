//
//  main.cpp
//  Gold
//
//  Created by wangwei on 2018/6/1.
//  Copyright © 2018年 vave.cc. All rights reserved.
//


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "../Header/StdAfx.h"
#include "../Header/TestCppClient.h"

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;

int main(int argc, const char * argv[]) {

        const char* host = argc > 1 ? argv[1] : "";
        unsigned int port = argc > 2 ? atoi(argv[2]) : 0;
        if (port <= 0)
                port = 7497;
        const char* connectOptions = argc > 3 ? argv[3] : "";
        int clientId = 0;
        unsigned attempt = 0;
        printf("Start of C++ Socket Client Test %u\n", attempt);
        
        while (true) {
                ++attempt;
                printf("Attempt %u of %u\n", attempt, MAX_ATTEMPTS);
                
                TestCppClient client;
                
                if (connectOptions) {
                        client.setConnectOptions(connectOptions);
                }
                
                client.connect(host, port, clientId);
                printf("Shit, I had knew how to use this application...\n");
                std::this_thread::sleep_for(std::chrono::seconds(5));
                client.historicalDataRequests();
                
                while (client.isConnected()) {
                        client.processMessages();
                }
                if (attempt >= MAX_ATTEMPTS) {
                        break;
                }
                
                
                printf("Sleeping %u seconds before next attempt\n", SLEEP_TIME);
                std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
        }
        
        printf("End of C++ Socket Client Test\n");
        
        return 0;
}
