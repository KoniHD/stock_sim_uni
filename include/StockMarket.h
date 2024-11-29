#ifndef STOCKMARKET_H
#define STOCKMARKET_H


#include "Stock.h"


#include <string>
#include <unordered_map>
#include <string_view>
#include <vector>

class StockMarket {
    // float, since we take timeStep as 1 for a time step of one year
    float timeStep;
    int simulationLength;
    std::unordered_map<std::string, Stock> stocks; // Map of stock names to Stock objects

public:
    StockMarket(float timeStep, int simulationLength);

    // TODO add getters
    std::vector<Stock> getStocks() const;
    double getStockPrice(std::string_view stockName) const;

    // arguments and returntype might still need to be changed
    void simulateMarket();
};


#endif // STOCKMARKET_H
