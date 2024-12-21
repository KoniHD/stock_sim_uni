#include "../include/HighRiskStrategy.h"

#include <vector>

#define LOW_RISK_PERCENTAGE  0.2
#define MID_RISK_PERCENTAGE  0.3
#define HIGH_RISK_PERCENTAGE 0.5

std::unordered_map<std::string, int> HighRiskStrategy::pickStocks(double totalFunds, const StockMarket &stockMarket) {
    std::unordered_map<std::string, int> portfolio;

    // FIXME: getStocks should work differently!!
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

    double lowRiskFundsPerShare{0.0f};
    double midRiskFundsPerShare{0.0f};
    double highRiskFundsPerShare{0.0f};
    if (midRiskStocks.empty() && highRiskStocks.empty()) {
        // All stocks are low-risk, so we can't distribute the funds as intended.
        lowRiskFundsPerShare = totalFunds / static_cast<double>(lowRiskStocks.size());
    } else if (lowRiskStocks.empty() && highRiskStocks.empty()) {
        // Only mid-risk stocks are available
        midRiskFundsPerShare = totalFunds / static_cast<double>(midRiskStocks.size());
    } else if (lowRiskStocks.empty() && midRiskStocks.empty()) {
        // Only high-risk stocks are available
        highRiskFundsPerShare = totalFunds / static_cast<double>(highRiskStocks.size());
    } else if (highRiskStocks.empty()) {
        // low-risk and mid-risk stocks are available, but no high-risk stocks
        double lowRiskPercentage = LOW_RISK_PERCENTAGE / (LOW_RISK_PERCENTAGE + MID_RISK_PERCENTAGE);
        double midRiskPercentage = MID_RISK_PERCENTAGE / (LOW_RISK_PERCENTAGE + MID_RISK_PERCENTAGE);
        lowRiskFundsPerShare     = (totalFunds * lowRiskPercentage) / static_cast<double>(lowRiskStocks.size());
        midRiskFundsPerShare     = (totalFunds * midRiskPercentage) / static_cast<double>(midRiskStocks.size());
    } else if (midRiskStocks.empty()) {
        // low-risk and high-risk stocks are available, but no mid-risk stocks
        double lowRiskPercentage  = LOW_RISK_PERCENTAGE / (LOW_RISK_PERCENTAGE + HIGH_RISK_PERCENTAGE);
        double highRiskPercentage = HIGH_RISK_PERCENTAGE / (LOW_RISK_PERCENTAGE + HIGH_RISK_PERCENTAGE);
        lowRiskFundsPerShare      = (totalFunds * lowRiskPercentage) / static_cast<double>(lowRiskStocks.size());
        highRiskFundsPerShare     = (totalFunds * highRiskPercentage) / static_cast<double>(highRiskStocks.size());
    } else if (lowRiskStocks.empty()) {
        // mid-risk and high-risk stocks are available, but no low-risk stocks
        double midRiskPercentage  = MID_RISK_PERCENTAGE / (MID_RISK_PERCENTAGE + HIGH_RISK_PERCENTAGE);
        double highRiskPercentage = HIGH_RISK_PERCENTAGE / (MID_RISK_PERCENTAGE + HIGH_RISK_PERCENTAGE);
        midRiskFundsPerShare      = (totalFunds * midRiskPercentage) / static_cast<double>(midRiskStocks.size());
        highRiskFundsPerShare     = (totalFunds * highRiskPercentage) / static_cast<double>(highRiskStocks.size());
    } else {
        // All risk categories are available
        lowRiskFundsPerShare  = (totalFunds * LOW_RISK_PERCENTAGE) / static_cast<double>(lowRiskStocks.size());
        midRiskFundsPerShare  = (totalFunds * MID_RISK_PERCENTAGE) / static_cast<double>(midRiskStocks.size());
        highRiskFundsPerShare = (totalFunds * HIGH_RISK_PERCENTAGE) / static_cast<double>(highRiskStocks.size());
    }

    // TODO: Consider using std::round instead of static_cast<int>
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
