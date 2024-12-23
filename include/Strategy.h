#ifndef STRATEGY_H
#define STRATEGY_H

#include "Stock.h"
#include "StockMarket.h"

#include <array>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

/**
 * @typedef StockGroups
 * @brief A tuple of three vectors of Stock objects.
 * @see StockRisk
 *
 * This typedef is intended to group @ref Stock "Stocks" into the three risk levels.
 */
typedef std::tuple<std::vector<Stock>, std::vector<Stock>, std::vector<Stock>> StockGroups;

/**
 * @enum StockRisk
 * @brief Represents the risk level of a stock.
 */
enum StockRisk {
    LOW_RISK_STOCK, /**<low risk level */
    MID_RISK_STOCK, /**<mid risk level */
    HIGH_RISK_STOCK, /**<high risk level */
    COUNT /**<Number of risk levels */
};

/**
 * @brief Assesses the risk of a stock based on its variance and its price.
 * @param stock The stock to assess.
 * @return The risk of the Stock.
 * @see StockRisk
 *
 * The @ref StockRisk "risk" is assessed based on the standard deviation of the Stock which is computed by
 * sqrt(variance) / Price. If the standard deviation is below 0.1, the Stock is considered @ref LOW_RISK_STOCK "low
 * risk". If the standard deviation is between 0.1 and 0.14, the Stock is considered @ref MID_RISK_STOCK "mid risk".
 * Everything above is considered to be @ref HIGH_RISK_STOCK "high risk".
 */
StockRisk assessStockRisk(const Stock &) noexcept;

class Strategy {

protected:
    /**
     * @brief Method groups all @ref Stock "Stocks" listed at @p market into @ref LOW_RISK_STOCK, @ref MID_RISK_STOCK,
     * and @ref HIGH_RISK_STOCK
     * @param market The StockMarket from which the  @ref Stock "Stocks" should be fetched.
     * @return @ref Stock "Stocks" grouped acording to their @ref StockRisk "Stock Risk" level.

     */
    [[nodiscard]] static StockGroups groupStocks(const StockMarket &) noexcept;

    /**
     * @brief Method attempts to buy as many @ref Stock "Stocks" for each @ref StockRisk "stock risk" as possible with
     * the given @p total_funds.
     * @param total_funds Total available funds across all @ref StockRisk "stock risk" levels. @p total_funds will also
     * be spent (i.e. the variable decreases).
     * @param grouped_stocks Predetermined container of @ref StockGroups.
     * @param risk_percentage Array specifying how much [0] @ref LOW_RISK_STOCK "low risk stocks", [1] @ref
     * MID_RISK_STOCK "mid risk stocks", and [2] @ref HIGH_RISK_STOCK "high risk stocks" (in decimal) to buy.
     * @return The Stock portfolio.
     *
     * The method optimizes the Stock purchase such that first funds for each @ref StockRisk "risk level" are
     * determined. The resulting fraction is then divided by the amount of @ref Stock "Stocks" to create a budget for
     * that Stock. Then the biggest possible amount of @ref Stock "Stocks" is bought with that budget. Finally using the
     * left-over budget it is attemted to buy the cheapest Stock in the @ref StockRisk "stock risk category".
     */
    [[nodiscard]] static std::unordered_map<std::string, unsigned> purchaseStocksByRisk(double &, const StockGroups &,
                                                                                        std::array<double, 3>) noexcept;

public:
    Strategy()                                    = default;
    virtual ~Strategy()                           = default;
    Strategy(const Strategy &other)               = default;
    Strategy &operator=(const Strategy &other)    = default;
    Strategy(Strategy &&move) noexcept            = default;
    Strategy &operator=(Strategy &&move) noexcept = default;


    /**
     * @brief Function to buy @ref Stock "Stocks" for a portfolio based on their @ref StockRisk "Risk". Implemented in
     * LowRiskStrategy and HighRiskStrategy.
     * @return The portfolio of @ref Stock "Stocks".
     */
    [[nodiscard]] virtual std::unordered_map<std::string, unsigned> pickStocks(double &,
                                                                               const StockMarket &) const noexcept = 0;
};

#endif // STRATEGY_H
