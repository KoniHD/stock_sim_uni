#ifndef STOCKMARKET_H
#define STOCKMARKET_H


#include "Stock.h"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "json.hpp"

using json = nlohmann::json;


class StockMarket {
    double _time_step;
    int _simulation_length;
    std::unordered_map<std::string, Stock> _stocks;

public:
    StockMarket() = delete;
    StockMarket(double timeStep, int simulationLength, const std::string &jsonFilePath);


    Stock& getStock(std::string_view) noexcept;
    std::vector<const Stock*> getStocks() const;

    double getStockPrice(std::string_view stockName) const noexcept;

    void simulateMarket();
    void outputPerformance();
    void validateStockData(const json &stockEntry);

};


#endif // STOCKMARKET_H
