#include "../include/HighRiskStrategy.h"

#include "../include/Strategy.h"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>


#define LOW_RISK_PERCENTAGE  0.2
#define MID_RISK_PERCENTAGE  0.3
#define HIGH_RISK_PERCENTAGE 0.5

std::unordered_map<std::string, unsigned> HighRiskStrategy::pickStocks(double &total_funds,
                                                                       const StockMarket &stockMarket) const noexcept {

    StockGroups grouped_stocks = groupStocks(stockMarket);

    std::array<double, 3> weights = {LOW_RISK_PERCENTAGE, MID_RISK_PERCENTAGE, HIGH_RISK_PERCENTAGE};

    if (std::get<0>(grouped_stocks).empty())
        weights.at(0) = 0.0;
    if (std::get<1>(grouped_stocks).empty())
        weights.at(1) = 0.0;
    if (std::get<2>(grouped_stocks).empty()) {
        std::cerr << "Currently there are no stocks considered high risk listed at the stockmarket." << std::endl
                  << "Abort purchase!" << std::endl;
        return {};
    }

    double total_weight = weights.at(0) + weights.at(1) + weights.at(2);
    for (double &weight: weights) {
        weight /= total_weight;
    }

    return purchaseStocksByRisk(total_funds, grouped_stocks, weights);
}
