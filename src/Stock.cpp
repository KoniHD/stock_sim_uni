#include "../include/Stock.h"
#include <string>
#include <math.h>
#include <random>

/* TODO MY QUESTIONS:
 * change timestep do double for consistency
 * initiaize generator in stockmarket
 * updatePrice right now void --> should we instead return to make recording of the time series easier?
 * which statistical values?
 * what about priceChange?
 */


// Constructor
Stock::Stock(double price, double expectedReturn, double variance, double priceChange) :
    price{price}, expectedReturn{expectedReturn}, variance{variance}, priceChange{priceChange} {}

double Stock::getPrice() const {
    return price;
};

double Stock::getExpectedReturn() const {
    return expectedReturn;
};

double Stock::getVariance() const {
    return variance;
};

std::string_view Stock::getName() const {
    return name;
};

// TODO add setters

// generates random number from standard normal distribution
double drawRandomNumber(std::default_random_engine& generator) {
    double mean{0.0};
    double var{1.0};

    std::normal_distribution<double> distribution{mean, sqrt(var)};
    return distribution(generator);
}

// simulates new price for one timestep with Geometric Brownian Motion (see link in README)
void Stock::updatePrice(const double& timestep, std::default_random_engine& generator) {
    double randomNumber = drawRandomNumber(generator);
    price = price + price * (expectedReturn * timestep + randomNumber * sqrt(variance * timestep));
}


















double Stock::getExpectedReturn() const { //sarper added this, explaiantion is in Stocks.h file
    return expectedReturn;
}

void Stock::updatePrice(double newPrice) {  // sarper added this, explanation is in .h file
    price = newPrice;
}

