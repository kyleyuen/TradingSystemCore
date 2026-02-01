#ifndef PRICEDATATRACKER_H
#define PRICEDATATRACKER_H

#include <unordered_map>
#include <set>
#include <vector>
#include <cstddef>

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
    std::vector<double> returnNdata(std::size_t N); //return N data for SMA 

private:
    std::unordered_map<int, double> data; 
    std::set<int> timestamps; 

    double latestPrice; 
    int latestTimestamp; 
    double HPrice;; 
    double LPrice; 

    bool state; //handles errors surrounding no data; 
};

#endif