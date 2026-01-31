#include "PriceDataTracker.h"
#include <iostream>
#include <unordered_map>

using namespace std; 

PriceData::PriceData(){
    state = false; //ensure that data must be implmented 
}

//Return the price of a chosen time 
double PriceData::price(int time){
    if(state != true) return -1; 
    if(data.count(time) == 0) return -1; 
    else{
        return data[time]; 
    }
}

//Return the Highest price 
double PriceData::highestPrice(){
    if(state != true) return -1; 
    return this->HPrice;
}

//Returns the LowestPrice
double PriceData::lowestPrice(){
    if(state != true) return -1; 
    return this->LPrice; 
}

//Returns the most recent Price where the timestamp is the most recent
double PriceData::recentPrice(){
    if(state != true) return -1; 
    return this->latestPrice;
}

//getter for timeStamp
int PriceData::timestamp(){
    return latestTimestamp;
}

bool PriceData::getState(){
    return state; 
}

int PriceData::sizeofMap(){
    return data.size();
}

//Add a stock Data 
bool PriceData::addPrice(int time, double amount){
    if(amount < 0) return false; 
    if(state != true){
        latestTimestamp = time;
        HPrice = LPrice = latestPrice = amount; 
        state = true; 
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
    return true;
} 




