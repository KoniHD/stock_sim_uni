#include "../include/StockMarket.h"
#include "../include/Stock.h"

#include <cmath>
#include <random>
#include <stdexcept>
#include <string_view>

StockMarket::StockMarket(float timeStep, int simulationLength) :
    timeStep{timeStep}, simulationLength{simulationLength} {
    // Initialize with some sample stocks
    stocks["Google"] = Stock(100.0, 0.1, 0.05, 0.0);
    stocks["Amazon"] = Stock(200.0, 0.08, 0.07, 0.0);
    stocks["Tesla"] = Stock(300.0, 0.12, 0.1, 0.0);
}

std::vector<Stock> StockMarket::getStocks() const {
    std::vector<Stock> stockList;
    for (const auto &[name, stock] : stocks) {
        stockList.push_back(stock);
    }
    return stockList;
}

double StockMarket::getStockPrice(std::string_view stockName) const {
    auto it = stocks.find(std::string(stockName));
    if (it != stocks.end()) {
        return it->second.getPrice();
    }
    throw std::runtime_error("Stock not found: " + std::string(stockName));
}

void StockMarket::simulateMarket() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, 1); // Standard normal distribution

    for (int t = 0; t < simulationLength; ++t) {
        for (auto &[name, stock] : stocks) {
            double currentPrice = stock.getPrice();
            double mu = stock.getExpectedReturn();
            double sigma = std::sqrt(stock.getVariance());
            double randomShock = d(gen);

            // Update stock price using GBM formula
            double newPrice = currentPrice * std::exp(
                (mu - 0.5 * sigma * sigma) * timeStep + sigma * std::sqrt(timeStep) * randomShock
            );
            stock.updatePrice(newPrice);
        }
    }
}
