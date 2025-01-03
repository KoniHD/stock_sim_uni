#ifndef STOCK_H
#define STOCK_H

#include <random>
#include <string>
#include <string_view>
#include <vector>

class Stock {
    // private since nothing stated here
    std::string name;
    double price;
    double expectedReturn;
    double variance;
    double priceChange; // FIXME: parameter necessary?
    std::vector<double> priceTimeSeries;
    double availableStocks;
    double marketCap;
    bool sellExecuted;
    bool buyExecuted;
    double orderVolume;

public:
    // constructor
    Stock(std::string name, double price, double expectedReturn, double variance, double priceChange,
      double availableStocks = 1e9);
    Stock();

    // getters
    double getPrice() const;
    double getExpectedReturn() const;
    [[nodiscard]] double getVariance() const noexcept;
    std::string_view getName() const;
    std::vector<double> getPriceTimeSeries() const;
    bool getSellExecuted() const;
    bool getBuyExecuted() const;
    double getOrderVolume() const noexcept;

    // setters
    void saveCurrentPrice(double price);
    void setPrice(double price);
    void setExpectedReturn(double expectedReturn);
    void setVariance(double variance);
    void setName(std::string_view name);
    void setSellExecuted(bool state);
    void setBuyExecuted(bool state);
    void setOrderVolume(double orderVolume);

    void updatePrice(const double &timeStep,
                     std::default_random_engine &generator); // simulates new price for one timestep
};

#endif // STOCK_H
