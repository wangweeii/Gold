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
const unsigned SLEEP_TIME   = 10;

// void sendRequests(TestCppClient *client)
// {
//         while (client->isConnected())
//         {
//                 client->checkTradeSignal();
//         }
// }

void processMsgs(TestCppClient *client)
{
        while (client->isConnected())
        {
                client->processMessages();
        }
}

int main(int argc, const char *argv[])
{
        // std::string  command;
        int          command;
        const char   *host = argc > 1 ? argv[1] : "";
        unsigned int port  = argc > 2 ? atoi(argv[2]) : 0;
        if (port <= 0)
        {
                port = 8888;
        }

        const char *connectOptions = argc > 3 ? argv[3] : "";
        int        clientId        = 0;
        unsigned   attempt         = 0;
        std::cout << "Start of C++ Socket Client Test " << attempt << std::endl;

        TestCppClient client;
        client.connect(host, port, clientId);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        client.accountOperations();

        // client.historicalDataRequests(6);
        std::thread t(processMsgs, &client);
        // std::thread trade(sendRequests,&client);

        // for (int i = 9; i < 10; ++i)
        // {
        //         client.historicalDataRequests(i);
        //         std::this_thread::sleep_for(std::chrono::seconds(10));
        // }

        while (true)
        {
                std::cin >> command;
                if (command < 10)
                {
                        client.historicalDataRequests(command);
                }
                else
                {
                        break;
                }
                // switch (command)
                // {
                //         case 1:client.computeEMA();
                //                 break;
                //         case 2:client.backTest();
                //                 break;
                //         case 7:client.historicalDataRequests(7);
                //                 break;
                //         case 8:client.historicalDataRequests(8);
                //                 break;
                //         case 9:client.historicalDataRequests(9);
                //         default:break;
                // }
                // if (command == "ema")
                // {
                //         client.computeEMA();
                // }
                // else if (command == "test")
                // {
                //         client.backTest();
                // }
                // else if (command == "exit")
                // {
                //         std::cout << "Exit.";
                //         break;
                // }
        }

        /*while (port > 1000)
        {
                ++attempt;
                // printf("Attempt %u of %u\n", attempt, MAX_ATTEMPTS);

                TestCppClient client;

                if (connectOptions)
                {
                        client.setConnectOptions(connectOptions);
                }

                client.connect(host, port, clientId);
                std::this_thread::sleep_for(std::chrono::seconds(2));

                // client.accountOperations();
                // std::this_thread::sleep_for(std::chrono::seconds(2));

                client.historicalDataRequests();
                // std::thread t(processMsgs, client);

                while (client.isConnected())
                {
                        client.processMessages();
                }
                if (attempt >= MAX_ATTEMPTS)
                {
                        break;
                }

                // printf("Sleeping %u seconds before next attempt\n", SLEEP_TIME);
                std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
        }*/

        printf("End of C++ Socket Client Test\n");
        return 0;
}

