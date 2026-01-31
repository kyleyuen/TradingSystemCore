#ifndef INDICATORS_H
#define INDICATORS_H


#include <queue>
#include "PriceDataTracker.h"

using namespace std;

class SimpleMovingAverage{
public:
    SimpleMovingAverage(int N);
    bool SMA(PriceData& priceData);

private:
    int nWindow;
    double SMAresult; 
};

#endif 