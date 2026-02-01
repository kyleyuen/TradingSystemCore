#include "Indicators.h"

class Signal{
public:
    enum status{
        HOLD,
        BUY,
        SELL
    };

bool strategyInterface(const string strat);
status SMATrendStragegy(SimpleMovingAverage& SimpleMovingAverage);




private:

};