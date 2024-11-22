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
};

#endif // STOCK_H
