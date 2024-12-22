#ifndef STOCKMARKET_H
#define STOCKMARKET_H


#include "Stock.h"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class StockMarket {
    float _time_step;
    int _simulation_length;
    std::unordered_map<std::string, Stock> _stocks;

public:
    StockMarket() = delete;
    StockMarket(float timeStep, int simulationLength);

    std::vector<Stock> getStocks() const;
    double getStockPrice(std::string_view stockName) const;

    void simulateMarket();
    void outputPerformance();
};


#endif // STOCKMARKET_H
