#ifndef STRATEGY_H
#define STRATEGY_H

#include "Stock.h"
#include "StockMarket.h"

#include <string>
#include <unordered_map>

enum StockRisk { LOW_RISK_STOCK, MID_RISK_STOCK, HIGH_RISK_STOCK };

/**
 * @brief Assesses the risk of a stock based on its variance and its price.
 * @param stock The stock to assess.
 * @return The risk of the stock.
 * @see StockRisk
 *
 * The risk is assessed based on the standard deviation of the stock which is computed by sqrt(variance) / Price.
 * If the standard deviation is below 0.1, the stock is considered low risk.
 * If the standard deviation is between 0.1 and 0.14, the stock is considered mid risk.
 * Everything above is considered to be high risk.
 */
StockRisk assessStockRisk(Stock stock);

class Strategy {

public:
    Strategy()                                    = default;
    virtual ~Strategy()                           = default;
    Strategy(const Strategy &other)               = default;
    Strategy &operator=(const Strategy &other)    = default;
    Strategy(Strategy &&move) noexcept            = default;
    Strategy &operator=(Strategy &&move) noexcept = default;

    [[nodiscard]] virtual std::unordered_map<std::string, unsigned> pickStocks(double, const StockMarket &) = 0;
};

#endif // STRATEGY_H
