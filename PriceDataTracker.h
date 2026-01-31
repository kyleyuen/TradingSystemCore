#ifndef PRICEDATATRACKER_H
#define PRICEDATATRACKER_H

#include <unordered_map>

class PriceData{
public:
    PriceData();
    double price(int time); //What is the price for the specific time in ms . 
    double highestPrice(); //higehst price
    double lowestPrice(); //lowest price 
    double recentPrice(); //most recent price
    bool addPrice(int time, double amount); //add a new timestamp
    int timestamp(); //get latest timestamp
    bool getState(); //get current state
    int sizeofMap(); //get size of Map

private:
    std::unordered_map<int, double> data; 
    double latestPrice; 
    int latestTimestamp; 
    double HPrice;; 
    double LPrice; 

    bool state; //handles errors surrounding no data; 
};

#endif