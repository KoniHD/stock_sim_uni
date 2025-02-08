#ifndef WALLET_H
#define WALLET_H

#include "Stock.h"
#include "StockMarket.h"
#include "Strategy.h"

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

class Wallet {

    double _funds; // FIXME should this variable be instead used as _invested_funds?
    double _cash_position;

    /**
     * @brief The total value of all @ref Stock "Stocks" in @ref _portfolio.
     */
    double _portfolio_value;

    /**
     * @brief The Strategy used for picking the stocks in @ref _portfolio.
     *
     * The Strategy is unique to this Wallet. It can be implemented with @ref LowRiskStrategy "low" or @ref
     * HighRiskStrategy "high risk".
     */
    std::unique_ptr<Strategy> _strategy;

    /**
     * @brief The StockMarket at which the @ref Stock "Stocks" in the @ref _portfolio are listed.
     */
    std::shared_ptr<StockMarket> _market;

    /**
     * @brief This variable keeps track of the cash added during the simulation, such that it is considered in the
     * performance calculation.
     */
    double _added_cash;

    /**
     * @brief The portfolio of @ref Stock "Stocks" owned by the Wallet.
     */
    std::unordered_map<std::string, unsigned> _portfolio;


public:
    Wallet() = delete;

    /**
     * @brief Construct a new Wallet object.
     *
     * The constructor initializes the @ref _funds and @ref _cash_position with @p funds and @ref _portfolio_value is
     * initially set to 0 but updated when the portflio is assembled using the @p strategy. The @ref _strategy is
     * moved to be owned by the Wallet. The @p market is the StockMarket at which the Wallet operates. Since multiple
     * @ref Wallet "Wallets" can operator on this StockMarket, @ref _market is a shared_ptr.
     */
    Wallet(double funds, std::unique_ptr<Strategy> strategy, std::shared_ptr<StockMarket> market);

    /**
     * @brief Checks whether the Wallet contains the Stock specified by @p stock_name
     * @param stock_name The name of the Stock to check.
     * @return Whether the Wallet contains the Stock
     */
    bool containsStock(std::string_view stock_name) const noexcept;

    /**
     * @brief Get the @ref _funds of the Wallet.
     * @return The @ref _funds of the Wallet.
     */
    [[nodiscard]] double getFunds() const;

    /**
     * @brief Get the @ref _portfolio_value of the Wallet.
     * @return The @ref _portfolio_value of the Wallet.
     */
    [[nodiscard]] double getPortfolioValue() const;

    /**
     * @brief Allow the user to buy a specified Stock.
     * @param stock The Stock to buy
     * @param amount The amount of @ref Stock "Stocks" to be bought
     * @return Whether the purchase was succesful.
     *
     * The method attempts to buy @ref Stock "Stocks" (specified by @p amount) using money from the @ref _cash_position.
     * If there is not enough money in @ref _cash_position an error is printed and no @ref Stock "Stocks" are bought.
     */
    bool buyStocks(Stock &stock, unsigned amount);

    /**
     * @brief Allow the user to sell a specified Stock.
     * @param stock The Stock to sell
     * @param amount The amount of @ref Stock "Stocks" to be sold
     * @return Whether the selling was succesful.
     *
     * The method attempts to sell @ref Stock "Stocks" (specified by @p amount) and add the money to the
     * @ref _cash_position. If there are not enough stocks in the wallet, an error is printed and
     * no @ref Stock "Stocks" are sold.
     */
    bool sellStocks(Stock &stock, unsigned amount);


    /**
     * @brief Prints @ref _cash_position, each owned Stock (value in owned Stock, number of @ref Stock "Stocks"), and
     * overall @ref _portfolio_value and performance.
     *
     * The function prints values rounded to two significant digits after dot for @ref _cash_position, and the
     * performance. The other values are printed in their stored precision.
     */
    void printWalletInfo() const;

    /**
     * @brief Calculate the total value of the @ref _portfolio.
     *
     * This function adds together the value of each Stock contained in the @ref _portfolio times its current price.
     */
    void evaluateResults();

    /**
     * @brief Add money to your cashposition
     * @param new_cash The amount of cash that should be added to the wallet's cashposition
     *
     * This function allows you to add money to your cashposition during the simumlation.
     */
    void addToCashposition(double new_cash);
};

#endif // WALLET_H
