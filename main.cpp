#include <iostream>
#include <fstream>
#include "PriceDataTracker.h"
#include "ReadCSV.h"

using namespace std; 

int main(int argc, char* argv[]){
    if(argc < 2){
        cerr << "Please Enter a Data in .CSV file format" << endl; 
        return -1; 
    }

    PriceData priceData;   
    readCSV reader; 

    //Read the CSV file
    bool success = reader.readData(argv[1], priceData);

    if (!success) {
        std::cerr << "Failed to read CSV\n";
        return -1;
    }

    // Print a short summary so you can see results
    std::cout << "Successfully read CSV file: " << argv[1] << "\n";
    std::cout << "Recent price: " << priceData.recentPrice() << "\n";
    std::cout << "Highest price: " << priceData.highestPrice() << "\n";
    std::cout << "Lowest price: " << priceData.lowestPrice() << "\n";

    std::cout << "Sample prices:\n";
    for (int i = 0; i < 5; ++i) {
        double p = priceData.price(i);
        if (p != -1)
            std::cout << "  t=" << i << " : " << p << "\n";
    }

    return 0;
}