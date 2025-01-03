#include "StockMarket.h"

#include "Stock.h"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
#include <vector>

StockMarket::StockMarket(float timeStep, int simulationLength) :
    _time_step{timeStep},
    _simulation_length{simulationLength}
{
    _stocks["Google"]     = Stock("Google", 100.0, 0.04, 0.05, 0.0);
    _stocks["Amazon"]     = Stock("Amazon", 200.0, 0.045, 0.07, 0.0);
    _stocks["Tesla"]      = Stock("Tesla", 300.0, 0.055, 0.1, 0.0);
    _stocks["Volkswagen"] = Stock("Volkswagen", 500.0, 0.09, 0.2, 0.0);
    _stocks["Adidas"]     = Stock("Adidas", 40.0, 0.1, 0.25, 0.0);
    _stocks["Apple"]      = Stock("Apple", 320.0, 0.055, 0.13, 0.0);
    _stocks["Hellofresh"] = Stock("Hellofresh", 80.0, 0.065, 0.12, 0.0);
    _stocks["Disney"]     = Stock("Disney", 150.0, 0.07, 0.14, 0.0);
    _stocks["Airbus"]     = Stock("Airbus", 700.0, 0.075, 0.16, 0.0);
    _stocks["Nestle"]     = Stock("Nestle", 290.0, 0.095, 0.22, 0.0);
}

Stock& StockMarket::getStock(std::string_view stock_name) noexcept
{
    std::string stock_name_(stock_name);
    auto it = _stocks.find(stock_name_);
    if (it != _stocks.end()) {
        return it->second;
    }
    throw std::runtime_error("Stock not found: " + std::string(stock_name));
    //return Stock{};
}

std::vector<Stock> StockMarket::getStocks() const
{
    std::vector<Stock> stock_list;
    for (const auto &[name, stock]: _stocks) {
        stock_list.push_back(stock);
    }
    return stock_list;
}

double StockMarket::getStockPrice(std::string_view stockName) const noexcept
{
    auto it = _stocks.find(std::string(stockName));
    if (it != _stocks.end()) {
        return it->second.getPrice();
    }
    return 0.0;
}


/**
* @brief Update prices iteratively for the given simulation length.
*
* The method generates the price series for all stocks in the stock market by iterating over the given simulation length
* and all stocks in the market. If a trade had been excecuted, the updatePrice method will change the attributes
* OrderVolume and buyExcecuted or sellExecuted such that the statistical values of the corresponding stock
* are being altered (e.g. higher expectedReturn and variance in case of a buy). After one timestep, those values
* are being reset again.
*/
void StockMarket::simulateMarket()
{
    std::default_random_engine generator(std::random_device{}());
    for (int time_step = 0; time_step < _simulation_length; ++time_step) {
        for (auto &[name, stock]: _stocks) {
            if (time_step == 1) {
                stock.setOrderVolume(0.0);
                stock.setBuyExecuted(false);
                stock.setSellExecuted(false);
            }
            stock.updatePrice(_time_step, generator);
        }
    }
}

void StockMarket::outputPerformance()
{
    std::ofstream out_file("../output/market_performance.csv");
    if (not out_file.is_open()) {
        std::cerr << "Failed to open output/ directory for .csv output file!" << std::endl;
        return;
    }

    // FIXME Once timesteps are implemented correctly please use a better way of retrieving the total timesteps!
    std::size_t max_sim_length = _stocks.begin()->second.getPriceTimeSeries().size();

    std::vector<std::vector<double>> history(_stocks.size());

    // Copy data into history & write header row
    unsigned i{0};
    for (const auto &[name, stock]: _stocks) {
        history.at(i) = stock.getPriceTimeSeries();
        ++i;

        out_file << name << ",";
    }
    out_file.seekp(-1, std::ios_base::cur);
    out_file << "\n";

    // Write data into .csv
    for (unsigned i{0}; i < max_sim_length; ++i) {
        for (unsigned j{0}; j < _stocks.size(); ++j) {
            out_file << history.at(j).at(i) << ",";
        }
        out_file.seekp(-1, std::ios_base::cur);
        out_file << "\n";
    }

    out_file.close();
}
