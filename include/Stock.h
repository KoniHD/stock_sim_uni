#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock {

    double Price;
    double expectedReturn;
    double variance;
    double priceChange;
    std::string name;

public:
    Stock(double Price, double expectedReturn, double variance, double priceChange);

    // TODO add getters
    double getPrice() const;
    double getVariance() const;
    std::string_view getName() const;

    // arguments and returntype might still need to be changed
    double simulateBehavior();
    double getExpectedReturn() const;   // I(Sarper) added these to make my part(StockMarket) work.
    void updatePrice(double newPrice);  // I(Sarper) added these to make my part(StockMarket) work.
     /*
     getExpectedReturn() returns the stock's expected return.
     updatePrice() updates the stock's price.
     
     */
};

#endif // STOCK_H
