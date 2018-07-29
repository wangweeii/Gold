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

#include "StdAfx.h"
#include "TestCppClient.h"

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
        std::string  command;
        std::string  begin;
        std::string  end   = "2019";
        int          number;
        int          number2;
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

        std::thread t(processMsgs, &client);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // client.historicalDataRequests(2005);
        // std::thread trade(sendRequests,&client);
        // client.historicalDataRequests(19);


        while (true)
        {
                std::cout << "input your command: " << std::endl;
                std::cin >> command;
                if (command == "test")
                {
                        std::cout << "input three step: " << std::endl;
                        std::cin >> number >> number2 >> begin;
                        client.setStep(number, number2);
                        client.backTest(begin);
                }
                else if (command == "get")
                {
                        std::cout << "Please input the number of year begin:" << std::endl;
                        std::cin >> number;
                        // for (int i = number; i < 2020; ++i)
                        // {
                                client.historicalDataRequests(number);
                                // std::this_thread::sleep_for(std::chrono::seconds(120));
                        // }
                }
                else if (command == "exit")
                {
                        std::cout << "Exit.";
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

