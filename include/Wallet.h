#ifndef WALLET_H
#define WALLET_H

#include "Stock.h"
#include "StockMarket.h"
#include "Strategy.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


class Wallet {

    double funds;
    std::unique_ptr<Strategy> strategy;
    StockMarket market;
    std::unordered_map<std::string, int> portfolio;

public:
    Wallet() = delete;
    Wallet(double funds, std::unique_ptr<Strategy> strategy, StockMarket &market);

    double getFunds() const;

    void evaluateResults();
};

#endif // WALLET_H
