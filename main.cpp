#include <iostream>
#include <fstream>
#include <string>
#include "PriceDataTracker.h"
#include "ReadCSV.h"

using namespace std; 

int main(int argc, char* argv[]){
    // Built-in tests when no filename provided or when requested explicitly
    auto runTests = [](){
        std::cout << "Running built-in tests...\n";
        PriceData pd;
        bool ok = true;

        if(pd.getState()){
            std::cerr << "FAIL: initial state should be false\n"; ok = false;
        } else {
            std::cout << "PASS: initial state false\n";
        }

        if(!pd.addPrice(1000, 50.0)){ std::cerr << "FAIL: addPrice failed\n"; ok = false; }
        if(!pd.getState()){ std::cerr << "FAIL: state after add\n"; ok = false; }
        if(pd.recentPrice() != 50.0){ std::cerr << "FAIL: recentPrice expected 50.0 got " << pd.recentPrice() << "\n"; ok = false; }
        if(pd.highestPrice() != 50.0){ std::cerr << "FAIL: highestPrice expected 50.0\n"; ok = false; }
        if(pd.lowestPrice() != 50.0){ std::cerr << "FAIL: lowestPrice expected 50.0\n"; ok = false; }
        if(pd.timestamp() != 1000){ std::cerr << "FAIL: timestamp expected 1000\n"; ok = false; }
        if(pd.sizeofMap() != 1){ std::cerr << "FAIL: sizeofMap expected 1\n"; ok = false; }

        pd.addPrice(1001, 55.5);
        pd.addPrice(999, 40.0);
        if(pd.highestPrice() != 55.5){ std::cerr << "FAIL: highestPrice expected 55.5\n"; ok = false; } else { std::cout << "PASS: highestPrice updated\n"; }
        if(pd.lowestPrice() != 40.0){ std::cerr << "FAIL: lowestPrice expected 40.0\n"; ok = false; } else { std::cout << "PASS: lowestPrice updated\n"; }
        if(pd.recentPrice() != 55.5){ std::cerr << "FAIL: recentPrice expected 55.5\n"; ok = false; } else { std::cout << "PASS: recentPrice updated\n"; }
        if(pd.price(999) != 40.0){ std::cerr << "FAIL: price lookup expected 40.0\n"; ok = false; } else { std::cout << "PASS: price lookup\n"; }

        auto v = pd.returnNdata(2);
        if(v.size() != 2 || v[0] != 55.5 || v[1] != 50.0){ std::cerr << "FAIL: returnNdata expected [55.5,50.0]\n"; ok = false; } else { std::cout << "PASS: returnNdata\n"; }

        if(ok) std::cout << "All tests passed ✅\n"; else std::cout << "Some tests failed ⚠️\n";
    };

    // run tests when no filename or when --test provided
    if(argc < 2 || std::string(argv[1]) == "--test"){
        runTests();
        return 0;
    }

    PriceData priceData;
    readCSV reader;

    //Read the CSV file
    bool success = reader.readData(argv[1], priceData);

    if (!success) {
        std::cerr << "Failed to read CSV\n";
        return -1;
    }

    std::cout << "CSV read successfully. Summary:\n";
    std::cout << "  entries: " << priceData.sizeofMap() << "\n";
    std::cout << "  latest ts: " << priceData.timestamp() << ", latest price: " << priceData.recentPrice() << "\n";
    std::cout << "  high: " << priceData.highestPrice() << ", low: " << priceData.lowestPrice() << "\n";

    return 0;
}