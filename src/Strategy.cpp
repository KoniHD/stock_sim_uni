#include "../include/Strategy.h"

#include <cmath>

#define LOW_RISK_BOUND 0.1
#define MID_RISK_BOUND 0.14

StockRisk assessStockRisk(Stock stock) {
    double standardDeviation = stock.getVariance();

    if (standardDeviation < LOW_RISK_BOUND) {
        return LOW_RISK_STOCK;
    }
    if (standardDeviation < MID_RISK_BOUND) {
        return MID_RISK_STOCK;
    }
    return HIGH_RISK_STOCK;
}
