#include "Stock.h"

#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Constructor
Stock::Stock(std::string name, double price, double expectedReturn, double standardDev, double availableStocks) :
    name{std::move(name)},
    price{price},
    expectedReturn{expectedReturn},
    standardDev{standardDev},
    priceTimeSeries({price}),
    availableStocks{availableStocks},
    marketCap{availableStocks * price},
    sellExecuted{false},
    buyExecuted{false},
    orderVolume{0.0} {
    if (price < 0) throw std::invalid_argument("Price must be non-negative");
    if (expectedReturn < 0 || expectedReturn > 0.5) throw std::invalid_argument("Expected return must be between 0 and 0.2");
    if (standardDev < 0 || standardDev > 0.5) throw std::invalid_argument("standardDev must be between 0 and 0.5");
    if (availableStocks < 0) throw std::invalid_argument("Available stocks must be non-negative");}

Stock::Stock() :
    price{0.0},
    expectedReturn{0.0},
    standardDev{0.0}
{}

// Getters
double Stock::getPrice() const { return price; }

double Stock::getExpectedReturn() const { return expectedReturn; }

double Stock::getStandardDev() const noexcept { return standardDev; }

std::string_view Stock::getName() const { return name; }

std::vector<double> Stock::getPriceTimeSeries() const { return priceTimeSeries; }

bool Stock::getSellExecuted() const {return sellExecuted; }

bool Stock::getBuyExecuted() const {return buyExecuted; }

double Stock::getOrderVolume() const noexcept { return orderVolume; }


// Setters
void Stock::saveCurrentPrice(double price) { priceTimeSeries.push_back(price); }

void Stock::setPrice(double price) { this->price = price; }

void Stock::setExpectedReturn(double expectedReturn) { this->expectedReturn = expectedReturn; }

void Stock::setStandardDev(double standardDev) { this->standardDev = standardDev; }

void Stock::setName(std::string_view name) { this->name = name; }

void Stock::setSellExecuted(bool state) {this -> sellExecuted = state;}

void Stock::setBuyExecuted(bool state) {this -> buyExecuted = state;}

void Stock::setOrderVolume(double orderVolume) { this -> orderVolume = orderVolume; }


// generates random number from standard normal distribution
double drawRandomNumber(std::default_random_engine &generator)
{
    double mean{0.0};
    double var{1.0};
    std::normal_distribution<double> distribution{mean, sqrt(var)};
    return distribution(generator);
}


/**
* @brief Update prices accoriding to Geometric Brownian Motion (cf. README), taking buys and sells into account
* @param &timeStep value between 0 and 1 determining the time step size of the simulation (e.g. 1/12 for monthly steps)
* @param &generator Random generator responsible for the stochastics of the simulation
*
* The method is applied to a single stock and calculates the new price for a simulation time step according to a
* Geometric Brownian Motion. If a buy (or sell) has been executed, the expected return gets positively (or negatively)
* affected, proportionally to the relation between order Volume and the available stocks. Additionally, the standardDev
* , i.e. the volatility of the stock is enhanced by 20%. More details can be found in the README section concerning
* sprint 2.
*/
void Stock::updatePrice(const double &timeStep, std::default_random_engine &generator)
{
    double tradeImpactExp{0.0};
    double tradeImpactStandardDev{1.0};
    if(buyExecuted == true) {
        tradeImpactExp = 100 * standardDev * orderVolume/availableStocks; // 100 is empirical value
        tradeImpactStandardDev = 150 * orderVolume/availableStocks; // 150 is empirical value
    } else if (sellExecuted == true) {
        tradeImpactExp = -100 * standardDev * orderVolume/availableStocks;
        tradeImpactStandardDev = 150 * orderVolume/availableStocks;
    }

    double randomNumber = drawRandomNumber(generator);
    price               = price + price * ((expectedReturn + tradeImpactExp) * timeStep + randomNumber * standardDev * tradeImpactStandardDev * sqrt(timeStep));
    price               = std::max(price, 0.01);
    priceTimeSeries.push_back(price);
}


