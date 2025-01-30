#ifndef STOCKMARKET_H
#define STOCKMARKET_H


#include "json.hpp"
#include "Stock.h"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>



using json = nlohmann::json;

class StockMarket {
    double _time_step;
    unsigned _simulation_length;
    std::unordered_map<std::string, Stock> _stocks;

public:
    StockMarket() = delete;
    StockMarket(double timeStep, unsigned simulationLength, const std::string &jsonFilePath);


    Stock &getStock(std::string_view);
    std::vector<const Stock *> getStocks() const;

    double getStockPrice(std::string_view stockName) const noexcept;

    void setSimulationLength(unsigned new_simulation_length) noexcept;

    /**
     * @brief Update prices iteratively for the given simulation length.
     *
     * The method generates the price series for all stocks in the stock market by iterating over the given simulation
     * length and all stocks in the market. If a trade had been excecuted, the updatePrice method will change the
     * attributes OrderVolume and buyExcecuted or sellExecuted such that the statistical values of the corresponding
     * stock are being altered (e.g. higher expectedReturn and standardDev in case of a buy). After one timestep, those
     * values are being reset again.
     */
    void simulateMarket();
    void outputPerformance();
    void validateStockData(const json &stockEntry);
};


#endif // STOCKMARKET_H
