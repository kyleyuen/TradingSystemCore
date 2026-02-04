#ifndef SMA_TREND_STRATEGY_H
#define SMA_TREND_STRATEGY_H

#include "Strategy.h"
#include "Indicators.h"

class SMATrendStrategy : public Strategy {
public:
    explicit SMATrendStrategy(int windowSize);

    Signal generateSignal(PriceData& priceData) override;

private:
    SimpleMovingAverage sma;
};

#endif
