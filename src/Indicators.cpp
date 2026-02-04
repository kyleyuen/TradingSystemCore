#include "Indicators.h"
#include <iostream>

using namespace std; 

SimpleMovingAverage::SimpleMovingAverage(std::size_t N){
    nWindow = N; 
}

size_t SimpleMovingAverage::getWindowSize(){
    return nWindow; 
}


double SimpleMovingAverage::SMA(PriceData& priceData){
    vector<double> prices = priceData.returnNdata(nWindow);
    if(prices.size() < nWindow) return -1; 

    double sum = 0; 
    for(std::size_t i = 0; i < prices.size(); ++i){
        sum += prices[i]; 
    }

    return sum / static_cast<double>(nWindow); 
}
