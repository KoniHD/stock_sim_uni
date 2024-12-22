#include "../include/Wallet.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

Wallet::Wallet(double funds, std::unique_ptr<Strategy> strategy, std::shared_ptr<StockMarket> market) :
    _cash_position{funds}, _funds{funds}, _portfolio_value{funds}, _strategy{std::move(strategy)}, _market{market} {
    _portfolio = _strategy->pickStocks(_funds, *_market);
}

bool Wallet::containsStock(std::string_view stock_name) const noexcept {
    std::string stock_name_(stock_name);
    auto it = _portfolio.find(stock_name_);
    return it != _portfolio.end();
}

double Wallet::getFunds() const { return _funds; }

double Wallet::getPortfolioValue() const { return _portfolio_value; }

void Wallet::evaluateResults() {
    double total{0.0f};
    for (const auto &stock: _portfolio) {
        total += stock.second * _market->getStockPrice(stock.first);
    }
    _portfolio_value = total;
}

bool Wallet::buyStocks(const Stock &stock, unsigned amount) noexcept {
    double funds_needed = stock.getPrice() * amount;
    if (funds_needed > _cash_position) {
        std::cerr << std::endl << "Not enough money in wallet to buy the specified amount of stocks." << std::endl;
        return false;
    }
    _cash_position -= funds_needed;
    std::string name(stock.getName());
    _portfolio.at(name) += amount;
    return true;
}

void Wallet::printWalletInfo() const {
    double portfolio_value{0.0};

    std::cout << std::endl
              << "Cashposition: " << std::round(_cash_position * 100.0) / 100.0 << "$" << std::endl
              << "Owned Stocks: ";

    // Printing individual stock prices and calculating the overall portfolio value
    for (const auto &stock: _portfolio) {
        double stock_value = _market->getStockPrice(stock.first);
        std::cout << "[\"" << stock.first << "\"]: " << stock.second << " stocks valued at " << stock_value << "$; ";
        portfolio_value += stock.second * stock_value;
    }

    // Evaluating the portfolio performance relative to the initial funds.s
    double performance = (portfolio_value / _funds - 1.0) * 100.0;
    std::cout << std::endl << "Total portfolio value in wallet is : " << portfolio_value;
    if (performance > 0.0) {
        std::cout << "$, up by " << std::round(performance * 100.0) / 100.0 << "%" << std::endl;
    } else {
        std::cout << "$, down by " << std::round(performance * 100.0) / 100.0 << "%" << std::endl;
    }
}
