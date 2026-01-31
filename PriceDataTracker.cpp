#include "PriceDataTracker.h"
#include <iostream>
#include <unordered_map>

using namespace std; 

double PriceData::price(int time){
    if(state != true) return -1; 
    if(data.count(time) == 0) return -1; 
    else{
        return data[time]; 
    }
}

double PriceData::highestPrice(){
    if(state != true) return -1; 
    return this->HPrice;
}

double PriceData::lowestPrice(){
    if(state != true) return -1; 
    return this->LPrice; 
}

double PriceData::recentPrice(){
    if(state != true) return -1; 
    return this->latestPrice;
}

bool PriceData::addPrice(int time, double amount){
    if(amount < 0) return false; 
    if(state != true){
        latestTimestamp = time;
        latestPrice = amount;
        HPrice = LPrice = amount; 
    }

    if(latestTimestamp < time){
        latestTimestamp = time; 
        latestPrice = amount; 
    }

    if(amount > HPrice){
        HPrice = amount;
    }
    if(amount < LPrice){
        LPrice = amount; 
    }

    data[time] = amount;   
}




