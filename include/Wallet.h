#ifndef WALLET_H
#define WALLET_H

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
     * @brief The total value of all stocks in @link _portfolio @endlink.
     */
    double _portfolio_value;

    /**
     * @brief The Strategy used for picking the stocks in @link _portfolio @endlink.
     *
     * The Strategy is unique to this Wallet. It can be implemented with low or high risk.
     */
    std::unique_ptr<Strategy> _strategy;

    /**
     * @brief The Stockmarket at which the Stocks in the @link _portfolio @endlink are listed.
     */
    std::shared_ptr<StockMarket> _market;

    /**
     * @brief The portfolio of Stocks owned by the Wallet.
     */
    std::unordered_map<std::string, unsigned> _portfolio;

public:
    Wallet() = delete;

    /**
     * @brief Construct a new Wallet object and initialize the @link _funds @endlink, @link _strategy @endlink and @link
     * _market @endlink.
     */
    Wallet(double, std::unique_ptr<Strategy>, std::shared_ptr<StockMarket>);

    /**
     * @brief Checks whether the Wallet contains the Stock specified by @p stock_name
     * @param stock_name The name of the Stock to check.
     * @return Whether the Wallet contains the Stock
     */
    bool containsStock(std::string_view) const noexcept;

    /**
     * @brief Get the @link _funds @endlink of the Wallet.
     * @return The @link _funds @endlink of the Wallet.
     */
    [[nodiscard]] double getFunds() const;

    /**
     * @brief Get the @link _portfolio_value @endlink of the Wallet.
     * @return The @link _portfolio_value @endlink of the Wallet.
     */
    [[nodiscard]] double getPortfolioValue() const;

    /**
     * @brief Allow the user to buy a specified Stock.
     * @param stock The Stock to buy
     * @param amount The amount of Stocks to be bought
     * @return Whether the purchase was succesful.
     *
     * The method attempts to buy stocks (specified by @p amount) using money from the @link _cash_position @endlink. If
     * there is not enough money in @link _cash_position @endlink and error is printed and no Stocks are bought.
     */
    bool buyStocks(const Stock &, unsigned) noexcept;

    /**
     * @brief Prints @link _cashPosition @endlink, each owned stock (value in owned stock, number stocks), and overall
     * portfolio value and performance.
     *
     * The function prints values rounded to two significant digits after dot for cash position, and the performance.
     * The other values are printed in their stored precision.
     */
    void printWalletInfo() const;

    /**
     * @brief Calculate the total value of the @link _portfolio @endlink.
     *
     * This function adds together the value of each Stock contained in the @link _portfolio @endlink times its current
     * price.
     */
    void evaluateResults();
};

#endif // WALLET_H
