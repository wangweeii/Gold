/* Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "../Header/StdAfx.h"
#include "../Header/OrderCondition.h"
#include "../Header/executioncondition.h"
#include "../Header/MarginCondition.h"
#include "../Header/TimeCondition.h"
#include "../Header/PercentChangeCondition.h"
#include "../Header/PriceCondition.h"
#include "../Header/VolumeCondition.h"
#include "../Header/EDecoder.h"
#include "../Header/EClient.h"

const char *OrderCondition::readExternal(const char *ptr, const char *endPtr)
{
        std::string connector;

        DECODE_FIELD(connector)

        conjunctionConnection(connector == "a");

        return ptr;
}

void OrderCondition::writeExternal(std::ostream &msg) const
{
        ENCODE_FIELD(conjunctionConnection() ? "a" : "o")
}

std::string OrderCondition::toString()
{
        return conjunctionConnection() ? "<AND>" : "<OR>";
}

bool OrderCondition::conjunctionConnection() const
{
        return m_isConjunctionConnection;
}

void OrderCondition::conjunctionConnection(bool isConjunctionConnection)
{
        m_isConjunctionConnection = isConjunctionConnection;
}

OrderCondition::OrderConditionType OrderCondition::type()
{ return m_type; }

OrderCondition *OrderCondition::create(OrderConditionType type)
{
        OrderCondition *rval = 0;

        switch (type)
        {
                case Execution: rval = new ExecutionCondition();
                        break;

                case Margin: rval = new MarginCondition();
                        break;

                case PercentChange: rval = new PercentChangeCondition();
                        break;

                case Price: rval = new PriceCondition();
                        break;

                case Time: rval = new TimeCondition();
                        break;

                case Volume: rval = new VolumeCondition();
                        break;
        }

        if (rval != 0)
        {
                rval->m_type = type;
        }

        return rval;
}
