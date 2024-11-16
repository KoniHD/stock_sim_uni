//
// Created by User on 16.11.2024.
//

#ifndef STOCK_H
#define STOCK_H



class Stock {
public:
    Stock(double initialPrice, double expectedReturn, double variance, double priceChange);
    ~Stock();

    // here: simulate Behavior method

private:
    double initialPrice;
    double expectedReturn;
    double variance;
    double priceChange;
};

#endif //STOCK_H