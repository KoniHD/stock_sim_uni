#include "LowRiskStrategy.h"

#include "Stock.h"
#include "StockMarket.h"
#include "Strategy.h"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define LOW_RISK_PERCENTAGE  0.5
#define MID_RISK_PERCENTAGE  0.3
#define HIGH_RISK_PERCENTAGE 0.2

auto LowRiskStrategy::pickStocks(double &total_funds, const StockMarket &stockMarket) const noexcept
        -> std::unordered_map<std::string, unsigned>
{
    // Use the updated groupStocks return type
    const std::array<std::vector<const Stock*>, 3> grouped_stocks = groupStocks(stockMarket);

    std::array<double, 3> weights = {LOW_RISK_PERCENTAGE, MID_RISK_PERCENTAGE, HIGH_RISK_PERCENTAGE};

    if (grouped_stocks.at(StockRisk::LOW_RISK_STOCK).empty()) {
        std::cerr << "Currently there are no stocks considered low risk listed at the stock market." << std::endl
                  << "Abort purchase!" << std::endl;
        return {};
    }
    if (grouped_stocks.at(StockRisk::MID_RISK_STOCK).empty())
        weights.at(1) = 0.0;
    if (grouped_stocks.at(StockRisk::HIGH_RISK_STOCK).empty())
        weights.at(2) = 0.0;

    double total_weight = weights.at(0) + weights.at(1) + weights.at(2);
    for (double &weight: weights) {
        weight /= total_weight;
    }

    // Create a portfolio
    std::unordered_map<std::string, unsigned> portfolio;

    for (std::size_t i = 0; i < grouped_stocks.size(); ++i) {
        if (!grouped_stocks[i].empty()) {
            double partial_funds = total_funds * weights[i];

            // Create a copy of the stocks from pointers
            std::vector<Stock> stocks_copy;
            for (const Stock* stock_ptr : grouped_stocks[i]) {
                stocks_copy.push_back(*stock_ptr); // Dereference pointer to create a copy
            }

            // Purchase stocks for the current risk group
            auto risk_portfolio = purchaseStocks(total_funds, partial_funds, stocks_copy);
            portfolio.merge(risk_portfolio);
        }
    }

    // Prioritize low-risk stocks with remaining funds
    std::vector<Stock> low_risk_stocks_copy;
    for (const Stock* stock_ptr : grouped_stocks.at(StockRisk::LOW_RISK_STOCK)) {
        low_risk_stocks_copy.push_back(*stock_ptr); // Dereference pointer to create a copy
    }
    portfolio.merge(purchaseStocks(total_funds, total_funds, low_risk_stocks_copy));

    return portfolio;
}
