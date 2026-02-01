#ifndef INDICATORS_H
#define INDICATORS_H


#include <cstddef>
#include "PriceDataTracker.h"

using namespace std;

class SimpleMovingAverage{
public:
    SimpleMovingAverage(std::size_t N);
    double SMA(PriceData& priceData);

private:
    std::size_t nWindow;
};

#endif 