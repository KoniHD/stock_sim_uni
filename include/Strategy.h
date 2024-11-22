#ifndef STRATEGY_H
#define STRATEGY_H

#include "Stock.h"
#include "StockMarket.h"

#include <string>
#include <unordered_map>

enum StockRisk { LOW_RISK_STOCK, MID_RISK_STOCK, HIGH_RISK_STOCK };

StockRisk assessStockRisk(Stock stock);

class Strategy {

public:
    Strategy()                                    = default;
    virtual ~Strategy()                           = default;
    Strategy(const Strategy &other)               = default;
    Strategy &operator=(const Strategy &other)    = default;
    Strategy(Strategy &&move) noexcept            = default;
    Strategy &operator=(Strategy &&move) noexcept = default;

    [[nodiscard]] virtual std::unordered_map<std::string, int> pickStocks(double funds,
                                                                          const StockMarket &stockMarket) = 0;
};

#endif // STRATEGY_H
