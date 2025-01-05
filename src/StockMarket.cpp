#include "StockMarket.h"

#include "json.hpp" // Include the JSON library
#include "Stock.h"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// Use the nlohmann JSON namespace for convenience
using json = nlohmann::json;

StockMarket::StockMarket(double timeStep, int simulationLength, const std::string &jsonFilePath) :
    _time_step{timeStep},
    _simulation_length{simulationLength}
{
    // Load stock data from JSON file
    std::ifstream jsonFile(jsonFilePath);
    if (!jsonFile.is_open()) {
        throw std::runtime_error("Failed to open JSON file: " + jsonFilePath);
    }

    json jsonData;
    try {
        jsonFile >> jsonData; // Parse the JSON file
    } catch (const json::parse_error &e) {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    }

    // Validate and populate stocks
    for (const auto &stockEntry: jsonData) {
        try {
            validateStockData(stockEntry);

            std::string name      = stockEntry["name"];
            double initialPrice   = stockEntry["initial_price"];
            double expectedReturn = stockEntry["expected_return"];
            double standardDev    = stockEntry["standard_dev"];

            _stocks[name] = Stock(name, initialPrice, expectedReturn, standardDev);
        } catch (const std::exception &e) {
            std::cerr << "Invalid stock data: " << e.what() << std::endl;
        }
    }

    jsonFile.close();
}

void StockMarket::validateStockData(const json &stockEntry)
{
    if (!stockEntry.contains("name") || !stockEntry["name"].is_string()) {
        throw std::invalid_argument("Stock entry is missing 'name' or it is not a string.");
    }

    if (!stockEntry.contains("initial_price") || !stockEntry["initial_price"].is_number()) {
        throw std::invalid_argument("Stock entry is missing 'initial_price' or it is not a number.");
    }

    if (!stockEntry.contains("expected_return") || !stockEntry["expected_return"].is_number()) {
        throw std::invalid_argument("Stock entry is missing 'expected_return' or it is not a number.");
    }

    if (!stockEntry.contains("standard_dev") || !stockEntry["standard_dev"].is_number()) {
        throw std::invalid_argument("Stock entry is missing 'standard_dev' or it is not a number.");
    }
}

Stock &StockMarket::getStock(std::string_view stock_name) noexcept
{
    std::string stock_name_(stock_name);
    auto it = _stocks.find(stock_name_);
    if (it != _stocks.end()) {
        return it->second;
    }
    throw std::runtime_error("Stock not found: " + std::string(stock_name));
    // return Stock{};
}

std::vector<const Stock *> StockMarket::getStocks() const
{
    std::vector<const Stock *> stock_list;
    for (const auto &[name, stock]: _stocks) {
        stock_list.push_back(&stock); // Store the address of each stock
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
 * The method generates the price series for all stocks in the stock market by iterating over the given simulation
 * length and all stocks in the market. If a trade had been excecuted, the updatePrice method will change the attributes
 * OrderVolume and buyExcecuted or sellExecuted such that the statistical values of the corresponding stock
 * are being altered (e.g. higher expectedReturn and standardDev in case of a buy). After one timestep, those values
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
