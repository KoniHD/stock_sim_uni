//
// Created by User on 16.11.2024.
//

#ifndef STOCK_H
#define STOCK_H



class Stock {

    double initialPrice;
    double expectedReturn;
    double variance;
    double priceChange;

public:
    Stock(double initialPrice, double expectedReturn, double variance, double priceChange);
    ~Stock();

    // arguments and returntype might still need to be changed
    double simulateBehavior();
};

#endif //STOCK_H