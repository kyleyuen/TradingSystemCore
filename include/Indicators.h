#ifndef INDICATORS_H
#define INDICATORS_H


#include <cstddef>
#include <vector>
#include "PriceDataTracker.h"


class SimpleMovingAverage{
public:
    SimpleMovingAverage(std::size_t N);
    double SMA(PriceData& priceData);

    //getters
    size_t getWindowSize();

private:
    std::size_t nWindow;
};

#endif 