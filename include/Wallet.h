#ifndef WALLET_H
#define WALLET_H

#include "HighRiskStrategy.h"
#include "LowRiskStrategy.h"
#include "Stock.h"
#include "StockMarket.h"
#include "Strategy.h"

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Wallet {

    double funds;
    // std::unique_ptr<Strategy> strategy;
    LowRiskStrategy lowRiskStrategy;
    HighRiskStrategy highRiskStrategy;
    // Strategy strategy;
    StockMarket market;
    std::unordered_map<std::string, int> portfolio;

public:
    Wallet() = default;
    Wallet(double funds, LowRiskStrategy lowRiskStrategy, StockMarket &market);
    Wallet(double funds, HighRiskStrategy highRiskStrategy, StockMarket &market);

    double getFunds() const;

    void evaluateResults(StockMarket &market);
};

#endif // WALLET_H
