#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <random>
#include <vector>

class Stock {
    // private since nothing stated here
    double price;
    double expectedReturn;
    double variance;
    double priceChange;
    std::string name;
    std::vector<double> priceTimeSeries;

public:
    // constructor
    Stock(double price, double expectedReturn, double variance, double priceChange);

    // getters
    double getPrice() const;
    double getExpectedReturn() const;
    double getVariance() const;
    std::string_view getName() const;
    std::vector<double> getPriceTimeSeries() const;

    void saveCurrentPrice(double price);
    void setPrice(double price);
    void setExpectedReturn(double expectedReturn);
    void setVariance(double variance);

    void updatePrice(const double& timeStep, std::default_random_engine& generator); // simulates new price for one timestep
    //void updatePrice(double newPrice);  // I(Sarper) added these to make my part(StockMarket) work.

};

#endif // STOCK_H
