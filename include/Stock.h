#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <random>
#include <vector>

class Stock {
    // private since nothing stated here
    std::string name;
    double price;
    double expectedReturn;
    double variance;
    double priceChange;
    std::vector<double> priceTimeSeries;

public:
    // constructor
    Stock(std::string name, double price, double expectedReturn, double variance, double priceChange);
    Stock();

    // getters
    double getPrice() const;
    double getExpectedReturn() const;
    double getVariance() const;
    std::string_view getName() const;
    std::vector<double> getPriceTimeSeries() const;

    // setters
    void saveCurrentPrice(double price);
    void setPrice(double price);
    void setExpectedReturn(double expectedReturn);
    void setVariance(double variance);
    void setName(std::string_view name);

    void updatePrice(const double& timeStep, std::default_random_engine& generator); // simulates new price for one timestep
};

#endif // STOCK_H
