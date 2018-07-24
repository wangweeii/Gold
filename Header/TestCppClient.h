/* Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef testcppclient_h__INCLUDED
#define testcppclient_h__INCLUDED

#define FAST_STEP 8
#define SLOW_STEP 55

#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"

#include <memory>
#include <vector>

class EClientSocket;

enum State
{
        ST_CONNECT,
        ST_TICKDATAOPERATION,
        ST_TICKDATAOPERATION_ACK,
        ST_TICKOPTIONCOMPUTATIONOPERATION,
        ST_TICKOPTIONCOMPUTATIONOPERATION_ACK,
        ST_DELAYEDTICKDATAOPERATION,
        ST_DELAYEDTICKDATAOPERATION_ACK,
        ST_MARKETDEPTHOPERATION,
        ST_MARKETDEPTHOPERATION_ACK,
        ST_REALTIMEBARS,
        ST_REALTIMEBARS_ACK,
        ST_MARKETDATATYPE,
        ST_MARKETDATATYPE_ACK,
        ST_HISTORICALDATAREQUESTS,
        ST_HISTORICALDATAREQUESTS_ACK,
        ST_OPTIONSOPERATIONS,
        ST_OPTIONSOPERATIONS_ACK,
        ST_CONTRACTOPERATION,
        ST_CONTRACTOPERATION_ACK,
        ST_MARKETSCANNERS,
        ST_MARKETSCANNERS_ACK,
        ST_REUTERSFUNDAMENTALS,
        ST_REUTERSFUNDAMENTALS_ACK,
        ST_BULLETINS,
        ST_BULLETINS_ACK,
        ST_ACCOUNTOPERATIONS,
        ST_ACCOUNTOPERATIONS_ACK,
        ST_ORDEROPERATIONS,
        ST_ORDEROPERATIONS_ACK,
        ST_OCASAMPLES,
        ST_OCASAMPLES_ACK,
        ST_CONDITIONSAMPLES,
        ST_CONDITIONSAMPLES_ACK,
        ST_BRACKETSAMPLES,
        ST_BRACKETSAMPLES_ACK,
        ST_HEDGESAMPLES,
        ST_HEDGESAMPLES_ACK,
        ST_TESTALGOSAMPLES,
        ST_TESTALGOSAMPLES_ACK,
        ST_FAORDERSAMPLES,
        ST_FAORDERSAMPLES_ACK,
        ST_FAOPERATIONS,
        ST_FAOPERATIONS_ACK,
        ST_DISPLAYGROUPS,
        ST_DISPLAYGROUPS_ACK,
        ST_MISCELANEOUS,
        ST_MISCELANEOUS_ACK,
        ST_CANCELORDER,
        ST_CANCELORDER_ACK,
        ST_FAMILYCODES,
        ST_FAMILYCODES_ACK,
        ST_SYMBOLSAMPLES,
        ST_SYMBOLSAMPLES_ACK,
        ST_REQMKTDEPTHEXCHANGES,
        ST_REQMKTDEPTHEXCHANGES_ACK,
        ST_REQNEWSTICKS,
        ST_REQNEWSTICKS_ACK,
        ST_REQSMARTCOMPONENTS,
        ST_REQSMARTCOMPONENTS_ACK,
        ST_NEWSPROVIDERS,
        ST_NEWSPROVIDERS_ACK,
        ST_REQNEWSARTICLE,
        ST_REQNEWSARTICLE_ACK,
        ST_REQHISTORICALNEWS,
        ST_REQHISTORICALNEWS_ACK,
        ST_REQHEADTIMESTAMP,
        ST_REQHEADTIMESTAMP_ACK,
        ST_REQHISTOGRAMDATA,
        ST_REQHISTOGRAMDATA_ACK,
        ST_REROUTECFD,
        ST_REROUTECFD_ACK,
        ST_MARKETRULE,
        ST_MARKETRULE_ACK,
        ST_PNL,
        ST_PNL_ACK,
        ST_PNLSINGLE,
        ST_PNLSINGLE_ACK,
        ST_CONTFUT,
        ST_CONTFUT_ACK,
        ST_PING,
        ST_PING_ACK,
        ST_REQHISTORICALTICKS,
        ST_REQHISTORICALTICKS_ACK,
        ST_REQTICKBYTICKDATA,
        ST_REQTICKBYTICKDATA_ACK,
        ST_WHATIFSAMPLES,
        ST_WHATIFSAMPLES_ACK,
        ST_IDLE
};

//! [ewrapperimpl]
class TestCppClient : public EWrapper
{
public:

        TestCppClient();

        ~TestCppClient();

        void setConnectOptions(const std::string &);

        void processMessages();

public:

        void accountOperations();

        bool connect(const char *host, unsigned int port, int clientId = 0);

        void disconnect() const;

        void historicalDataRequests();

        bool isConnected() const;

private:
        void testMACD(const Bar &bar);

        void testEmaCross(const Bar &bar);

        double computeEMA(double *price, int tail, const int step);

        double fast_sma();

        double slow_sma();

        // bool isActive();

        void pnlOperation();

        void pnlSingleOperation();

        void tickDataOperation();

        void tickOptionComputationOperation();

        void delayedTickDataOperation();

        void marketDepthOperations();

        void realTimeBars();

        void marketDataType();

        //        void historicalDataRequests();
        void optionsOperations();

        //        void accountOperations();
        void orderOperations();

        void ocaSamples();

        void conditionSamples();

        void bracketSample();

        void hedgeSample();

        void contractOperations();

        void marketScanners();

        void reutersFundamentals();

        void bulletins();

        void testAlgoSamples();

        void financialAdvisorOrderSamples();

        void financialAdvisorOperations();

        void testDisplayGroups();

        void miscelaneous();

        void reqFamilyCodes();

        void reqMatchingSymbols();

        void reqMktDepthExchanges();

        void reqNewsTicks();

        void reqSmartComponents();

        void reqNewsProviders();

        void reqNewsArticle();

        void reqHistoricalNews();

        void reqHeadTimestamp();

        void reqHistogramData();

        void rerouteCFDOperations();

        void marketRuleOperations();

        void continuousFuturesOperations();

        void reqHistoricalTicks();

        void reqTickByTickData();

        void whatIfSamples();

        void reqCurrentTime();

public:
        // events
#include "EWrapper_prototypes.h"

private:
        void printContractMsg(const Contract &contract);

        void printContractDetailsMsg(const ContractDetails &contractDetails);

        void printContractDetailsSecIdList(const TagValueListSPtr &secIdList);

        void printBondContractDetailsMsg(const ContractDetails &contractDetails);

private:
        //! [socket_declare]
        EReaderOSSignal m_osSignal;
        EClientSocket *const m_pClient;
        //! [socket_declare]
        State m_state;
        time_t m_sleepDeadline;

        OrderId m_orderId;
        EReader *m_pReader;
        bool m_extraAuth;
        std::string m_bboExchange;

        double raw_price[10000];
        int tail = -1;

        double fast_price[FAST_STEP] = {0};
        int fast_tail = -1;

        double slow_price[SLOW_STEP] = {0};
        int slow_tail = -1;

        Bar previous_bar, current_bar;

        double fast_alpha = 2.0 / (FAST_STEP + 1);
        double slow_alpha = 2.0 / (SLOW_STEP + 1);
        double fast_beta = 1 - fast_alpha;
        double slow_beta = 1 - slow_alpha;

        double fast_ema = 0;
        double slow_ema = 0;
        double fast_total = 0;
        double slow_total = 0;

        double fast_line = 0;
        double slow_line = 0;
        double old_fast_line = 0;
        double old_slow_line = 0;
        double macd = 0;
        double last_macd = 0;
        double old_macd = 0;

        int have_position = 0;
        double buy_price = 0;
        double sel_price = 0;
        double place_price = 0;
        double highest = 0;
        double lowest = 0;

        int service_fee = 0;
        int bar_count = 0;

        int beishu = 20;
        double total_value = 9600;
        int quantity = 0;
        int commission = 0;
        double stop = 0.0019;

        int win_count = 0;
        int los_count = 0;
};
//! [ewrapperimpl]

#endif
