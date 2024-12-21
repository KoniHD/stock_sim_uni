#ifndef LOWRISKSTRATEGY_H
#define LOWRISKSTRATEGY_H

#include "StockMarket.h"
#include "Strategy.h"

#include <string>
#include <unordered_map>

class LowRiskStrategy : public Strategy {

public:
    /**
     * @brief Composes a low-risk portfolio of stocks.
     * @param stockMarket The stock market to pick stocks from.
     * @return The stock portfolio.
     *
     * This strategy picks 50% low-risk stocks, 30% mid-risk stocks and 20% high-risk stocks. This share is based on the
     * total available funds. Per risk category, the value is distributed equally among the stocks. By this the number
     * of stocks in the portoflio is dericed.
     */
    [[nodiscard]] std::unordered_map<std::string, int> pickStocks(double funds,
                                                                  const StockMarket &stockMarket) override;
};

#endif // LOWRISKSTRATEGY_H
