#ifndef HIGHRISKSTRATEGY_H
#define HIGHRISKSTRATEGY_H

#include "StockMarket.h"
#include "Strategy.h"

#include <string>
#include <unordered_map>

class HighRiskStrategy : public Strategy {

public:
    /**
     * @brief Composes a high-risk portfolio of @ref Stock "Stocks".
     * @param invested_funds The funds available for purchasing @ref Stock "Stocks".
     * @param stockMarket The @ref StockMarket "Stock Market" to pick @ref Stock "Stocks" from.
     * @return The Stock portfolio.
     *
     * This strategy picks 20% @ref LOW_RISK_STOCK "low-risk stocks", 30% @ref MID_RISK_STOCK "mid-risk stocks" and 50%
     * @ref HIGH_RISK_STOCK "high-risk stocks". The amount of @ref Stock "Stocks" per @ref StockRisk "risk level" then
     * depends on the @p invested_funds. Per @ref StockRisk "risk category", the value is distributed equally
     * among the
     * @ref Stock "Stocks". By this, the number of @ref Stock "Stocks" in the portoflio is derived. The method also
     * decreases the @p invested_funds passed to it, simulating a real purchase.
     */
    [[nodiscard]] auto pickStocks(double &invested_funds, const StockMarket &stockMarket) const noexcept
            -> std::unordered_map<std::string, unsigned> override;
};

#endif // HIGHRISKSTRATEGY_H
