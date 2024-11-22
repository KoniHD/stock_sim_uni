#ifndef LOWRISKSTRATEGY_H
#define LOWRISKSTRATEGY_H

#include "Stock.h"
#include "StockMarket.h"
#include "Strategy.h"


#include <string>
#include <unordered_map>


class LowRiskStrategy : public Strategy {

public:
    [[nodiscard]] std::unordered_map<std::string, int> pickStocks(double funds,
                                                                  const StockMarket &stockMarket) override;
};

#endif // LOWRISKSTRATEGY_H
