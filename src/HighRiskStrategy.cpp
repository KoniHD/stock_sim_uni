#include "../include/HighRiskStrategy.h"

#include <vector>

#define LOW_RISK_PERCENTAGE  0.2
#define MID_RISK_PERCENTAGE  0.4
#define HIGH_RISK_PERCENTAGE 0.3

/**
 * @brief Composes a high-risk portfolio of stocks.
 * @param stockMarket The stock market to pick stocks from.
 * @return The stock portfolio.
 *
 * This strategy picks 20% low-risk stocks, 40% mid-risk stocks and 30% high-risk stocks. This share is based on the
 * total available funds. Per risk category, the value is distributed equally among the stocks. By this the number of
 * stocks in the portoflio is dericed.
 */
std::unordered_map<std::string, int> HighRiskStrategy::pickStocks(double totalFunds, const StockMarket &stockMarket) {
    std::unordered_map<std::string, int> portfolio;

    std::vector<Stock> stocks = stockMarket.getStocks();
    std::vector<Stock> lowRiskStocks;
    std::vector<Stock> midRiskStocks;
    std::vector<Stock> highRiskStocks;
    for (const Stock stock: stocks) {
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
        portfolio.emplace(stock.getName(), static_cast<int>(lowRiskFundsPerShare / stock.getInitialPrice()));
    }
    for (const Stock &stock: midRiskStocks) {
        portfolio.emplace(stock.getName(), static_cast<int>(midRiskFundsPerShare / stock.getInitialPrice()));
    }
    for (const Stock &stock: highRiskStocks) {
        portfolio.emplace(stock.getName(), static_cast<int>(highRiskFundsPerShare / stock.getInitialPrice()));
    }

    return portfolio;
}
