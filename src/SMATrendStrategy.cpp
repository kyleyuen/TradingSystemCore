#include "SMATrendStrategy.h"

using namespace std;

//initalizes SMA with the desired window size
SMATrendStrategy::SMATrendStrategy(int windowSize)
    : sma(windowSize)
{}

//generates a signal base on the data recieved 
Signal SMATrendStrategy::generateSignal(PriceData& priceData) {
    //Retrieves both the SMA daata as wella s the recent price points
    double SMAVal = sma.SMA(priceData);
    double recentVal = priceData.recentPrice();

    //logic for SMA
    if(priceData.getState() == false) return Signal::HOLD; 
    if(recentVal == -1) return Signal::HOLD; 
    if(SMAVal == -1) return Signal::HOLD;

    if(recentVal > SMAVal) return Signal::BUY;
    if(recentVal < SMAVal) return Signal::SELL;

    return Signal::HOLD; 
}

