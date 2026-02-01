#include "Indicators.h"
#include <iostream>

using namespace std; 

SimpleMovingAverage::SimpleMovingAverage(int N){
    nWindow = N; 

}

double SimpleMovingAverage::SMA(PriceData& priceData){
    vector<double> prices = priceData.returnNdata(nWindow);
    if(prices.size() < nWindow) return -1; 

    double sum = 0; 
    for(int i = 0; i < prices.size(); i++){
        sum += prices[i]; 
    }

    return sum/nWindow; 
}
