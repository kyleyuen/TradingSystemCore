#include "Indicators.h"
#include <queue>
#include <iostream>

using namespace std; 

SimpleMovingAverage::SimpleMovingAverage(int N){
    nWindow = N; 
    SMAresult = 0; 
}

bool SimpleMovingAverage::SMA(PriceData& priceData){
    if(!priceData.getState()) return false; 
    queue<double> Ncurrent; 
    double t = priceData.timestamp(); 
    int counter = 0; 

    while(counter < nWindow && t >= 0){
        if(priceData.price(t - counter) != -1){
            Ncurrent.push(priceData.price(t-counter));
        }
        counter++; 
    }

    if(counter < nWindow){
        cerr << "Not enough data for N Window, please choose a smaller N" << endl;
        return false; 
    }

    double total  = 0; 
    while(!Ncurrent.empty()){
        total += Ncurrent.front();
        Ncurrent.pop();
    }

    SMAresult = total/nWindow;
    return true; 
}
