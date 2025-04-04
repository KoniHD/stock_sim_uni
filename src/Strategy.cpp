#include "Strategy.h"

#include "Stock.h"
#include "StockMarket.h"

#include <array>
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

#define LOW_RISK_BOUND 0.1
#define MID_RISK_BOUND 0.14

StockRisk assessStockRisk(const Stock &stock) noexcept
{
    double standard_deviation = stock.getStandardDev();

    if (standard_deviation < LOW_RISK_BOUND)
        return LOW_RISK_STOCK;

    if (standard_deviation < MID_RISK_BOUND)
        return MID_RISK_STOCK;

    return HIGH_RISK_STOCK;
}

auto Strategy::purchaseStocks(double &invested_funds, double partial_funds, const std::vector<Stock> &stocks) noexcept
        -> std::unordered_map<std::string, unsigned>
{
    if (stocks.empty())
        return {};

    std::unordered_map<std::string, unsigned> portfolio;
    double funds_per_share{partial_funds / static_cast<double>(stocks.size())};

    unsigned amount_of_stock{0};
    Stock cheapest_stock{"Not cheap", DBL_MAX, 0.0, 0.0, 0.0};
    for (const Stock &stock: stocks) {
        double stock_price = stock.getPrice();
        if (stock_price < cheapest_stock.getPrice())
            cheapest_stock = stock;

        amount_of_stock = static_cast<unsigned>(std::trunc(funds_per_share / stock_price));
        portfolio.emplace(stock.getName(), amount_of_stock);
        invested_funds -= amount_of_stock * stock_price;
        partial_funds -= amount_of_stock * stock_price;
    }
    amount_of_stock = static_cast<unsigned>(std::trunc(partial_funds / cheapest_stock.getPrice()));
    portfolio.at(std::string(cheapest_stock.getName())) += amount_of_stock;
    invested_funds -= amount_of_stock * cheapest_stock.getPrice();

    return portfolio;
}

auto Strategy::groupStocks(const StockMarket &market) noexcept -> std::array<std::vector<const Stock *>, 3>
{
    std::array<std::vector<const Stock *>, 3> grouped_stocks;

    // Updated to work with pointers from market.getStocks()
    const std::vector<const Stock *> stocks = market.getStocks();
    for (const Stock *stock: stocks) {
        StockRisk risklevel{assessStockRisk(*stock)}; // Dereference pointer to access Stock
        grouped_stocks.at(risklevel).push_back(stock); // Add pointer to the appropriate group
    }
    return grouped_stocks;
}

auto Strategy::purchaseStocksByRisk(double &invested_funds, const std::array<std::vector<Stock>, 3> &grouped_stocks,
                                    std::array<double, 3> risk_percentage) noexcept
        -> std::unordered_map<std::string, unsigned>
{
    std::unordered_map<std::string, unsigned> portfolio;

    for (std::size_t i{0}; i < grouped_stocks.size(); ++i) {
        if (not grouped_stocks.at(i).empty()) {
            double partial_invested_funds{invested_funds * risk_percentage.at(i)};
            portfolio.merge(purchaseStocks(invested_funds, partial_invested_funds, grouped_stocks.at(i)));
        }
    }

    return portfolio;
}
