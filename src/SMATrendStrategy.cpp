#include "SMATrendStrategy.h"

using namespace std;

SMATrendStrategy::SMATrendStrategy(int windowSize)
    : sma(windowSize)
{}

Signal SMATrendStrategy::generateSignal(PriceData& priceData) {
    double SMAVal = sma.SMA(priceData);
    double recentVal = priceData.recentPrice();

    if(priceData.getState() == false) return Signal::HOLD; 
    if(recentVal == -1) return Signal::HOLD; 
    if(SMAVal == -1) return Signal::HOLD;

    if(recentVal > SMAVal) return Signal::BUY;
    if(recentVal < SMAVal) return Signal::SELL;

    return Signal::HOLD; 
}

