#include "Strategy.h"

#include "Stock.h"
#include "StockMarket.h"

#include <array>
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#define LOW_RISK_BOUND 0.1
#define MID_RISK_BOUND 0.14

StockRisk assessStockRisk(const Stock &stock) noexcept
{

    double standard_deviation = stock.getVariance();

    if (standard_deviation < LOW_RISK_BOUND)
        return LOW_RISK_STOCK;

    if (standard_deviation < MID_RISK_BOUND)
        return MID_RISK_STOCK;

    return HIGH_RISK_STOCK;
}

auto Strategy::_purchaseStocks(double &total_funds, double partial_funds,
                               const std::vector<Stock> &stocks) noexcept -> std::unordered_map<std::string, unsigned>
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
        total_funds -= amount_of_stock * stock_price;
        partial_funds -= amount_of_stock * stock_price;
    }
    amount_of_stock = static_cast<unsigned>(std::trunc(partial_funds / cheapest_stock.getPrice()));
    portfolio.at(std::string(cheapest_stock.getName())) += amount_of_stock;
    total_funds -= amount_of_stock * cheapest_stock.getPrice();

    return portfolio;
}

auto Strategy::groupStocks(const StockMarket &market) noexcept -> std::array<std::vector<Stock>, 3>
{

    std::array<std::vector<Stock>, 3> grouped_stocks;

    // FIXME: getStocks should work differently!!
    std::vector<Stock> stocks = market.getStocks();
    for (Stock &stock: stocks) {
        StockRisk risklevel{assessStockRisk(stock)};
        grouped_stocks.at(risklevel).push_back(std::move(stock));
    }
    return grouped_stocks;
}

auto Strategy::purchaseStocksByRisk(double &total_funds, const std::array<std::vector<Stock>, 3> &grouped_stocks,
                                    std::array<double, 3> risk_percentage) noexcept
        -> std::unordered_map<std::string, unsigned>
{

    std::unordered_map<std::string, unsigned> portfolio;

    for (std::size_t i{0}; i < grouped_stocks.size(); ++i) {
        if (not grouped_stocks.at(i).empty()) {
            double partial_funds{total_funds * risk_percentage.at(i)};
            portfolio.merge(_purchaseStocks(total_funds, partial_funds, grouped_stocks.at(i)));
        }
    }

    return portfolio;
}
