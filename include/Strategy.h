#ifndef STRATEGY_H
#define STRATEGY_H

#include <unordered_map>

#include "Stock.h"

class Strategy {

public:
    virtual std::unordered_map<Stock, int> pickStocks() = 0;
};

#endif // STRATEGY_H
