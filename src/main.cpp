#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "PriceDataTracker.h"
#include "ReadCSV.h"
#include "Indicators.h"
#include "SMATrendStrategy.h"

using namespace std;
using Clock = chrono::high_resolution_clock;

int main() {
    cout << "=== Trading System Core Demo ===\n\n";

    auto t_start = Clock::now();

    // -------------------------------------------------
    // Load CSV
    // -------------------------------------------------
    auto t_load_start = Clock::now();

    const string csvPath = "data/6758_jp_d.csv";

    PriceData priceData;
    readCSV reader;

    if (!reader.readData(csvPath.c_str(), priceData)) {
        cerr << "Failed to read CSV: " << csvPath << "\n";
        return 1;
    }

    auto t_load_end = Clock::now();

    cout << "Loaded CSV successfully\n";
    cout << "Total data points: " << priceData.sizeofMap() << "\n\n";

    double price = priceData.recentPrice();

    // -------------------------------------------------
    // SMA horizons
    // -------------------------------------------------
    auto t_analysis_start = Clock::now();

    vector<int> windows = {20, 50, 200};
    vector<double> smaValues;
    vector<string> trendLabels;

    cout << "=== Trend Summary ===\n";
    cout << "Latest Price: " << price << "\n\n";

    for (int w : windows) {
        SimpleMovingAverage sma(w);
        double val = sma.SMA(priceData);

        smaValues.push_back(val);

        cout << "SMA(" << w << "): ";
        if (val == -1) {
            cout << "not ready\n";
            trendLabels.push_back("N/A");
        } else {
            cout << val;
            if (price > val) {
                cout << "  → Bullish\n";
                trendLabels.push_back("BUY");
            } else {
                cout << "  → Bearish\n";
                trendLabels.push_back("SELL");
            }
        }
    }

    auto t_analysis_end = Clock::now();

    // -------------------------------------------------
    // Consensus signal
    // -------------------------------------------------
    int buyCount = 0;
    int sellCount = 0;

    for (const auto& t : trendLabels) {
        if (t == "BUY")  buyCount++;
        if (t == "SELL") sellCount++;
    }

    cout << "\n=== Consensus Signal ===\n";

    if (buyCount > sellCount) {
        cout << "Signal: BUY\n";
    } else if (sellCount > buyCount) {
        cout << "Signal: SELL\n";
    } else {
        cout << "Signal: HOLD\n";
    }

    cout << "\nReasoning:\n";
    for (size_t i = 0; i < windows.size(); ++i) {
        cout << "- SMA(" << windows[i] << "): " << trendLabels[i] << "\n";
    }

    auto t_end = Clock::now();

    // -------------------------------------------------
    // Runtime statistics
    // -------------------------------------------------
    auto load_time =
        chrono::duration_cast<chrono::microseconds>(t_load_end - t_load_start).count();

    auto analysis_time =
        chrono::duration_cast<chrono::microseconds>(t_analysis_end - t_analysis_start).count();

    auto total_time =
        chrono::duration_cast<chrono::microseconds>(t_end - t_start).count();

    cout << "\n=== Runtime ===\n";
    cout << "CSV load time:      " << load_time     << " µs\n";
    cout << "Analysis time:      " << analysis_time << " µs\n";
    cout << "Total runtime:      " << total_time    << " µs\n";

    cout << "\n=== Demo Complete ===\n";
    return 0;
}
