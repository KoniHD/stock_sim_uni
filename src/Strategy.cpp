#include "../include/Strategy.h"

#include <cmath>

#define LOW_RISK_BOUND 0.1
#define MID_RISK_BOUND 0.14

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
