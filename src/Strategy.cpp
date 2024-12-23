#include "../include/Strategy.h"

#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>

#define LOW_RISK_BOUND 0.1
#define MID_RISK_BOUND 0.14

StockRisk assessStockRisk(const Stock &stock) noexcept {
    double standard_deviation = stock.getVariance();

    if (standard_deviation < LOW_RISK_BOUND)
        return LOW_RISK_STOCK;

    if (standard_deviation < MID_RISK_BOUND)
        return MID_RISK_STOCK;

    return HIGH_RISK_STOCK;
}

StockGroups Strategy::groupStocks(const StockMarket &market) noexcept {
    StockGroups grouped_stocks;

    // FIXME: getStocks should work differently!!
    std::vector<Stock> stocks = market.getStocks();
    for (Stock &stock: stocks) {
        switch (assessStockRisk(stock)) {
            case StockRisk::LOW_RISK_STOCK:
                std::get<0>(grouped_stocks).push_back(std::move(stock));
                break;
            case StockRisk::MID_RISK_STOCK:
                std::get<1>(grouped_stocks).push_back(std::move(stock));
                break;
            default: // StockRisk::HIGH_RISK_STOCK:
                std::get<2>(grouped_stocks).push_back(std::move(stock));
                break;
        }
    }
    return grouped_stocks;
}

std::unordered_map<std::string, unsigned>
Strategy::purchaseStocksByRisk(double &total_funds, const StockGroups &grouped_stocks,
                               std::array<double, 3> risk_percentage) noexcept {
    std::unordered_map<std::string, unsigned> portfolio;
    std::array<double, 3> funds_per_share{};

    if (not std::get<0>(grouped_stocks).empty()) {
        funds_per_share.at(0) =
                total_funds * risk_percentage.at(0) / static_cast<double>(std::get<0>(grouped_stocks).size());
    }
    if (not std::get<1>(grouped_stocks).empty()) {
        funds_per_share.at(1) =
                total_funds * risk_percentage.at(1) / static_cast<double>(std::get<1>(grouped_stocks).size());
    }
    if (not std::get<2>(grouped_stocks).empty()) {
        funds_per_share.at(2) =
                total_funds * risk_percentage.at(2) / static_cast<double>(std::get<2>(grouped_stocks).size());
    }


    for (const Stock &stock: std::get<0>(grouped_stocks)) {
        unsigned amount_of_stock{static_cast<unsigned>(std::trunc(funds_per_share.at(0) / stock.getPrice()))};
        portfolio.emplace(stock.getName(), amount_of_stock);
        total_funds -= amount_of_stock * stock.getPrice();
    }
    for (const Stock &stock: std::get<1>(grouped_stocks)) {
        unsigned amount_of_stock{static_cast<unsigned>(std::trunc(funds_per_share.at(1) / stock.getPrice()))};
        portfolio.emplace(stock.getName(), amount_of_stock);
        total_funds -= amount_of_stock * stock.getPrice();
    }
    for (const Stock &stock: std::get<2>(grouped_stocks)) {
        unsigned amount_of_stock{static_cast<unsigned>(std::trunc(funds_per_share.at(2) / stock.getPrice()))};
        portfolio.emplace(stock.getName(), amount_of_stock);
        total_funds -= amount_of_stock * stock.getPrice();
    }

    return portfolio;
}
