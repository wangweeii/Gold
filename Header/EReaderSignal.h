﻿/* Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once

struct EReaderSignal
{
        virtual void issueSignal() = 0;

        virtual void waitForSignal() = 0;

        virtual ~EReaderSignal()
        {}
};

