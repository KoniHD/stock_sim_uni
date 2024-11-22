#include "../include/LowRiskStrategy.h"

#include <vector>

#define LOW_RISK_PERCENTAGE  0.5
#define MID_RISK_PERCENTAGE  0.3
#define HIGH_RISK_PERCENTAGE 0.2

/**
 * @brief Composes a low-risk portfolio of stocks.
 * @param stockMarket The stock market to pick stocks from.
 * @return The stock portfolio.
 *
 * This strategy picks 50% low-risk stocks, 30% mid-risk stocks and 20% high-risk stocks. This share is based on the
 * total available funds. Per risk category, the value is distributed equally among the stocks. By this the number of
 * stocks in the portoflio is dericed.
 */
std::unordered_map<std::string, int> LowRiskStrategy::pickStocks(double totalFunds, const StockMarket &stockMarket) {
    std::unordered_map<std::string, int> portfolio;

    std::vector<Stock> stocks = stockMarket.getStocks();
    std::vector<Stock> lowRiskStocks;
    std::vector<Stock> midRiskStocks;
    std::vector<Stock> highRiskStocks;
    for (const Stock &stock: stocks) {
        switch (assessStockRisk(stock)) {
            case StockRisk::LOW_RISK_STOCK:
                lowRiskStocks.push_back(stock);
                break;
            case StockRisk::MID_RISK_STOCK:
                midRiskStocks.push_back(stock);
                break;
            default:
                highRiskStocks.push_back(stock);
                break;
        }
    }

    double lowRiskFundsPerShare  = (totalFunds * LOW_RISK_PERCENTAGE) / static_cast<double>(lowRiskStocks.size());
    double midRiskFundsPerShare  = (totalFunds * MID_RISK_PERCENTAGE) / static_cast<double>(midRiskStocks.size());
    double highRiskFundsPerShare = (totalFunds * HIGH_RISK_PERCENTAGE) / static_cast<double>(highRiskStocks.size());

    for (const Stock &stock: lowRiskStocks) {
        portfolio.emplace(stock.getName(), static_cast<int>(lowRiskFundsPerShare / stock.getPrice()));
    }
    for (const Stock &stock: midRiskStocks) {
        portfolio.emplace(stock.getName(), static_cast<int>(midRiskFundsPerShare / stock.getPrice()));
    }
    for (const Stock &stock: highRiskStocks) {
        portfolio.emplace(stock.getName(), static_cast<int>(highRiskFundsPerShare / stock.getPrice()));
    }

    return portfolio;
}
