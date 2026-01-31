#ifndef READCSV_H
#define READCSV_H

// Forward declaration to avoid including the full PriceDataTracker header here
class PriceData;

class readCSV{
public:
    readCSV();
    bool readData(const char* filename, PriceData& priceData);

private:
    int rows; 
};

#endif