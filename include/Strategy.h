#ifndef STRATEGY_H
#define STRATEGY_H

#include <unordered_map>

class Strategy {

    virtual std::unordered_map<Stock, int>() pickStocks() = 0;
};

#endif // STRATEGY_H
