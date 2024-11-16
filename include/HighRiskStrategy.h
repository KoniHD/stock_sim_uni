#ifndef HIGHRISKSTRATEGY_H
#define HIGHRISKSTRATEGY_H

#include "Strategy.h"

#include <unordered_map>

class HighRiskStrategy : public Strategy {

    std::unordered_map<Stock, int> pickStocks() override;
};

#endif // HIGHRISKSTRATEGY_H
