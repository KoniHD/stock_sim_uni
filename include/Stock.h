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
    double standardDev;
    double availableStocks;
    double marketCap;
    bool sellExecuted;
    bool buyExecuted;
    double orderVolume;

public:
    // constructor
    Stock() = delete;
    Stock(std::string name, double price, double expectedReturn, double standardDev, double availableStocks = 1e9);

    // getters
    [[nodiscard]] double getPrice() const;
    [[nodiscard]] double getStandardDev() const noexcept;
    [[nodiscard]] std::string_view getName() const;

    // setters
    void setSellExecuted(bool state);
    void setBuyExecuted(bool state);
    void setOrderVolume(double orderVolume);


    /**
     * @brief Update prices accoriding to Geometric Brownian Motion (cf. README), taking buys and sells into account
     * @param &timeStep value between 0 and 1 determining the time step size of the simulation (e.g. 1/12 for monthly
     * steps)
     * @param &generator Random generator responsible for the stochastics of the simulation
     *
     * The method is applied to a single stock and calculates the new price for a simulation time step according to a
     * Geometric Brownian Motion. If a buy (or sell) has been executed, the expected return gets positively (or
     * negatively) affected, proportionally to the relation between order Volume and the available stocks. Additionally,
     * the standardDev , i.e. the volatility of the stock is enhanced by 20%. More details can be found in the README
     * section concerning sprint 2.
     */
    void updatePrice(const double &timeStep,
                     std::default_random_engine &generator); // simulates new price for one timestep
};

#endif // STOCK_H
