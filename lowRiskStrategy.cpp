#include "include/Strategy.h"

#include <unordered_map>

class LowRiskStrategy : public Strategy {

    std::unordered_map<Stock, int> pickStocks() override {
        // some code
    }
};
