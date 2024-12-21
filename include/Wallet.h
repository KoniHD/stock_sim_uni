#ifndef WALLET_H
#define WALLET_H

#include "StockMarket.h"
#include "Strategy.h"

#include <memory>
#include <string>
#include <unordered_map>

class Wallet {

    double _funds;
    std::unique_ptr<Strategy> _strategy;
    std::shared_ptr<StockMarket> _market;
    std::unordered_map<std::string, int> _portfolio;

public:
    Wallet() = delete;

    /**
     * @brief Construct a new Wallet object and initialize the funds, strategy and market.
     */
    Wallet(double funds, std::unique_ptr<Strategy> strategy, std::shared_ptr<StockMarket> market);

    /**
     * @brief Get the funds of the wallet.
     * @return double The funds of the wallet.
     */
    double getFunds() const;

    /**
     * @brief Calculate the total value of the portfolio.
     *
     * This function adds together the value of each stock contained in the portfolio times its current price.
     */
    void evaluateResults();
};

#endif // WALLET_H
