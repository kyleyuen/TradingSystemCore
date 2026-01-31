#include <fstream>
#include <sstream>
#include "ReadCSV.h"
#include "PriceDataTracker.h"

using namespace std; 

readCSV::readCSV(){
    rows = 0; 
}

bool readCSV::readData(const char* filename, PriceData& priceData){
    ifstream dataFile(filename); 
    if(!dataFile.is_open()) {
        return false; 
    }
    string line; 
    getline(dataFile, line);

    //Extracting Data
    while(getline(dataFile, line)){

        //Variables
        int columnIndex =0; //Counting Column 
        double closePrice = 0.0; //Price per line
        string feild; //Data extracted 

        stringstream ss(line); 
        //Extract Column 4 for the Closing prices
        while(getline(ss, feild, ',')){
            if(columnIndex == 4){
                closePrice = stod(feild); //Convert to a double 
            }
            columnIndex++;
        }

        priceData.addPrice(rows, closePrice); 
        rows++; 
    }
    dataFile.close();
    return true;
}
