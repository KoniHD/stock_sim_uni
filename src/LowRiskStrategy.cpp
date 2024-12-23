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

    std::array<std::vector<Stock>, 3> grouped_stocks = groupStocks(stockMarket);

    std::array<double, 3> weights = {LOW_RISK_PERCENTAGE, MID_RISK_PERCENTAGE, HIGH_RISK_PERCENTAGE};

    if (grouped_stocks.at(StockRisk::LOW_RISK_STOCK).empty()) {
        std::cerr << "Currently there are no stocks considered low risk listed at the stockmarket." << std::endl
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

    return purchaseStocksByRisk(total_funds, grouped_stocks, weights);
}
