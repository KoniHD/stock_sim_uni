#ifndef LOWRISKSTRATEGY_H
#define LOWRISKSTRATEGY_H

#include "Strategy.h"

#include <unordered_map>

class LowRiskStrategy : public Strategy {

    std::unordered_map<Stock, int> pickStocks() override;
};

#endif // LOWRISKSTRATEGY_H
