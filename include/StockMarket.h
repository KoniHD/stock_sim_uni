#ifndef STOCKMARKET_H
#define STOCKMARKET_H


#include "Stock.h"

#include <string_view>
#include <vector>

class StockMarket {
    // float, since we take timeStep as 1 for a time step of one year
    float timeStep;
    int simulationLength;
    std::vector<int> simulationData;

public:
    StockMarket(float timeStep, int simulationLength);

    // TODO add getters
    std::vector<Stock> getStocks() const;
    double getStockPrice(std::string_view stockName) const;

    // arguments and returntype might still need to be changed
    void simulateMarket();
};


#endif // STOCKMARKET_H
