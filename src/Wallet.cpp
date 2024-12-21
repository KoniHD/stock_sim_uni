#include "../include/Wallet.h"

#include <memory>
#include <utility>

Wallet::Wallet(double funds, std::unique_ptr<Strategy> strategy, std::shared_ptr<StockMarket> market) :
    _funds{funds}, _strategy{std::move(strategy)}, _market{market} {
    _portfolio = _strategy->pickStocks(_funds, *_market);
}

double Wallet::getFunds() const { return _funds; }

void Wallet::evaluateResults() {
    double total{0.0f};
    for (const auto &stock: _portfolio) {
        total += stock.second * _market->getStockPrice(stock.first);
    }
    _funds = total;
}
