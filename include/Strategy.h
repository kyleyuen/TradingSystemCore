#ifndef STRATEGY_H
#define STRATEGY_H

#include "Signal.h"
#include "PriceDataTracker.h"

class Strategy {
public:
    virtual ~Strategy() = default;

    // Given current market data, return a trading signal
    virtual Signal generateSignal(PriceData& priceData) = 0;
};

#endif
