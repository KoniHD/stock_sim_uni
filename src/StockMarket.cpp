#include "../include/StockMarket.h"
#include "../include/Stock.h"
#include <iostream>

#include <cmath>
#include <random>
#include <stdexcept>
#include <string_view>

StockMarket::StockMarket(float timeStep, int simulationLength) : //The constructor initializes the StockMarket with a time step and simulation length.
    timeStep{timeStep}, simulationLength{simulationLength} {
    // Initialize with some sample stocks with initial values for price, expected return, variance, and price change. These are represented by the Stock class objects.
    stocks["Google"] = Stock("Google", 100.0, 0.04, 0.05, 0.0);
    stocks["Amazon"] = Stock("Amazon", 200.0, 0.045, 0.07, 0.0);
    stocks["Tesla"] = Stock("Tesla", 300.0, 0.055, 0.1, 0.0);
    stocks["Volkswagen"] = Stock("Volkswagen", 500.0, 0.09, 0.2, 0.0);
    stocks["Adidas"] = Stock("Adidas", 40.0, 0.1, 0.25, 0.0);
    stocks["Apple"] = Stock("Apple", 320.0, 0.03, 0.03, 0.0);
    stocks["Hellofresh"] = Stock("Hellofresh", 80.0, 0.065, 0.12, 0.0);
    stocks["Disney"] = Stock("Disney", 150.0, 0.07, 0.14, 0.0);
    stocks["Airbus"] = Stock("Airbus", 700.0, 0.075, 0.16, 0.0);
    stocks["Nestle"] = Stock("Nestle", 290.0, 0.95, 0.22, 0.0);
}

std::vector<Stock> StockMarket::getStocks() const {  // This method returns all the stocks in the stocks map. It loops through the map and pushes each stock into a vector to return.
    std::vector<Stock> stockList;
    for (const auto &[name, stock] : stocks) {
        stockList.push_back(stock);
    }
    return stockList;
}

double StockMarket::getStockPrice(std::string_view stockName) const { // This method looks up a stock by its name and returns the price of the stock. If the stock isn't found, it throws an exception.
    auto it = stocks.find(std::string(stockName));
    if (it != stocks.end()) {
        return it->second.getPrice();
    }
    throw std::runtime_error("Stock not found: " + std::string(stockName));
}

/*

This method below (simulateMarket) simulates the stock market over the specified number of time steps.
It uses Geometric Brownian Motion (GBM) to update stock prices based on their expected return (mu), volatility (sigma), and a random shock (randomShock).
The stock prices are updated after each time step, and the simulation runs for the entire length of the simulation (simulationLength).

*/

void StockMarket::simulateMarket() {
    std::default_random_engine generator(std::random_device{}());

    for (int t = 0; t < simulationLength; ++t) {
        for (auto &[name, stock] : stocks) {
            // Update stock price using GBM formula
            stock.updatePrice(timeStep, generator);
            // stock.saveCurrentPrice(getStockPrice(name));
        }
    }
}

void StockMarket::printPerformance() {
    for (auto &[name, stock] : stocks) {
        std::cout << "trend_" << name << ": [";
        for (double price: stock.getPriceTimeSeries()) {
            std::cout << price << ", ";
        }
        std::cout << "]" << std::endl;
    }
}
