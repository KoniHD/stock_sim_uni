#include "Wallet.h"

#include "Stock.h"
#include "StockMarket.h"
#include "Strategy.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

Wallet::Wallet(double funds, std::unique_ptr<Strategy> strategy, std::shared_ptr<StockMarket> market) :
    _funds{funds},
    _cash_position{funds},
    _portfolio_value{0.0},
    _strategy{std::move(strategy)},
    _market{market},
    _added_cash{0.0}
{
    _portfolio = _strategy->pickStocks(_cash_position, *_market);
    evaluateResults();
}

bool Wallet::containsStock(std::string_view stock_name) const noexcept
{
    std::string stock_name_(stock_name);
    auto it = _portfolio.find(stock_name_);
    return it != _portfolio.end();
}

double Wallet::getFunds() const { return _funds; }

double Wallet::getPortfolioValue() const { return _portfolio_value; }

void Wallet::evaluateResults()
{
    double total{0.0f};
    for (const auto &stock: _portfolio) {
        total += stock.second * _market->getStockPrice(stock.first);
    }
    _portfolio_value = total;
}

bool Wallet::buyStocks(Stock &stock, unsigned amount)
{
    double funds_needed = stock.getPrice() * amount;
    if (funds_needed > _cash_position) {
        std::cerr << std::endl << "Not enough money in wallet to buy the specified amount of stocks." << std::endl;
        return false;
    }
    _cash_position -= funds_needed;
    std::string name(stock.getName());
    _portfolio.at(name) += amount;
    stock.setOrderVolume(amount);
    stock.setBuyExecuted(true);
    return true;
}

bool Wallet::sellStocks(Stock &stock, unsigned amount)
{
    std::string name(stock.getName());
    if (amount > _portfolio.at(name)) {
        std::cout << "You don't own enough stocks to realize the selling. " << std::endl;
        return false;
    }
    _cash_position += amount * stock.getPrice();
    _portfolio.at(name) -= amount;
    stock.setOrderVolume(amount);
    stock.setSellExecuted(true);
    return true;
}

void Wallet::printWalletInfo() const
{
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
    // double performance = (portfolio_value / _funds - 1.0) * 100.0;
    double performance = ((portfolio_value + _cash_position) / (_funds + _added_cash) - 1.0) * 100.0;
    std::cout << std::endl << "Total portfolio value in wallet is : " << portfolio_value;
    if (performance > 0.0) {
        std::cout << "$, up by " << std::round(performance * 100.0) / 100.0 << "%" << std::endl;
    } else {
        std::cout << "$, down by " << std::round(performance * 100.0) / 100.0 << "%" << std::endl;
    }
}

void Wallet::addToCashposition(double new_cash)
{
    this->_cash_position += new_cash;
    this->_added_cash += new_cash;
}
