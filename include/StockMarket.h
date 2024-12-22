#ifndef STOCKMARKET_H
#define STOCKMARKET_H


#include "Stock.h"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class StockMarket {
    float timeStep; // timestep = 1.0 is equivalent to yearly steps; timestep = 1.0/12.0 is equivalent to monthly steps
    int simulationLength;
    std::unordered_map<std::string, Stock> stocks; // Map of stock names to Stock objects

public:
    StockMarket() = default;
    StockMarket(float timeStep, int simulationLength);

    std::vector<Stock> getStocks() const; // Retrieve all stocks in the market .getStocks() returns a list of all stocks in the market.
    double getStockPrice(std::string_view stockName) const; // getStockPrice() retrieves the price of a stock by its name.

    void simulateMarket(); // simulateMarket() performs the simulation of stock prices over time using a stochastic
                           // model, here a Geometric Brownian Motion
    void printPerformance();
};


#endif // STOCKMARKET_H
