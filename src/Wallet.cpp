#include "../include/Wallet.h"

#include <memory>
#include <utility>

/**
 * @brief Construct a new Wallet object and initialize the funds, strategy and market.
 */
Wallet::Wallet(double funds, LowRiskStrategy lowRiskStrategy, StockMarket &market) :
    funds{funds}, lowRiskStrategy{lowRiskStrategy}, market{market} {
    portfolio = lowRiskStrategy.pickStocks(funds, market);
}

Wallet::Wallet(double funds, HighRiskStrategy highRiskStrategy, StockMarket &market) :
    funds{funds}, highRiskStrategy{highRiskStrategy}, market{market} {
    portfolio = highRiskStrategy.pickStocks(funds, market);
}

/**
 * @brief Get the funds of the wallet.
 * @return double The funds of the wallet.
 */
double Wallet::getFunds() const { return funds; }

/**
 * @brief Calculate the total value of the portfolio.
 *
 * This function adds together the value of each stock contained in the portfolio times its current price.
 */
void Wallet::evaluateResults() {
    double total{0.0f};
    for (const auto &stock: portfolio) {
        total += stock.second * market.getStockPrice(stock.first);
    }
    funds = total;
}
