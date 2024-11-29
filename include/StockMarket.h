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
    std::vector<Stock> getStocks() const; // Retrieve all stocks in the market .getStocks() returns a list of all stocks in the market.
    double getStockPrice(std::string_view stockName) const; //getStockPrice() retrieves the price of a stock by its name.

    // arguments and returntype might still need to be changed
    void simulateMarket(); // simulateMarket() performs the simulation of stock prices over time using a stochastic model (like Geometric Brownian Motion).
};


#endif // STOCKMARKET_H
