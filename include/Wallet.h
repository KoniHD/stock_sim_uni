#ifndef WALLET_H
#define WALLET_H

#include "StockMarket.h"
#include "Strategy.h"

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

class Wallet {

    double _funds;
    double _cash_position;
    std::unique_ptr<Strategy> _strategy;
    std::shared_ptr<StockMarket> _market;
    std::unordered_map<std::string, int> _portfolio;

public:
    Wallet() = delete;

    /**
     * @brief Construct a new Wallet object and initialize the funds, strategy and market.
     */
    Wallet(double, std::unique_ptr<Strategy>, std::shared_ptr<StockMarket>);

    /**
     * @brief Checks whether the wallet contains the @link{Stock} specified by name
     * @return Whether the Wallet contains the @link{Stock}
     */
    bool containsStock(std::string_view) const noexcept;

    /**
     * @brief Get the funds of the wallet.
     * @return The funds of the wallet.
     */
    [[nodiscard]] double getFunds() const;

    /**
     * @brief Allow the user to buy a specified stock.
     * @param[0] The stock to buy
     * @param[1] The amount of stocks to be bought
     * @return Whether the purchase was succesful.
     *
     * The method attemts to buy the amount of specified stocks using money from the @link{_cash_position}. If there is
     * not enough money in @link{_cash_position} and error is printed and no stocks are bought.
     */
    bool buyStocks(const Stock &, unsigned) noexcept;

    /**
     * @brief Prints _cashPosition, each owned stock (value in owned stock, number stocks), and overall portfolio Value
     * and performance.
     *
     * The function prints values rounded to two significant digits after dot for cash position, and the performance.
     * The other values are printed in their stored precision.
     */
    void printWalletInfo();

    /**
     * @brief Calculate the total value of the portfolio.
     *
     * This function adds together the value of each stock contained in the portfolio times its current price.
     */
    void evaluateResults();
};

#endif // WALLET_H
