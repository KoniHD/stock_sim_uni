#include "Stock.h"

#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

Stock::Stock(std::string name, double price, double expectedReturn, double standardDev, double availableStocks) :
    name{std::move(name)},
    price{price},
    expectedReturn{expectedReturn},
    standardDev{standardDev},
    availableStocks{availableStocks},
    marketCap{availableStocks * price}
{
    if (price < 0)
        throw std::invalid_argument("Price must be non-negative");
    if (expectedReturn < 0 || expectedReturn > 0.5)
        throw std::invalid_argument("Expected return must be between 0 and 0.5");
    if (standardDev < 0 || standardDev > 0.5)
        throw std::invalid_argument("standardDev must be between 0 and 0.5");
    if (availableStocks < 0)
        throw std::invalid_argument("Available stocks must be non-negative");
}

// Getters
double Stock::getPrice() const { return price; }

double Stock::getStandardDev() const noexcept { return standardDev; }

std::string_view Stock::getName() const { return name; }

// Setters
void Stock::setSellExecuted(bool state) { this->sellExecuted = state; }

void Stock::setBuyExecuted(bool state) { this->buyExecuted = state; }

void Stock::setOrderVolume(double orderVolume) { this->orderVolume = orderVolume; }

// generates random number from standard normal distribution
double drawRandomNumber(std::default_random_engine &generator)
{
    double mean{0.0};
    double var{1.0};
    std::normal_distribution<double> distribution{mean, sqrt(var)};
    return distribution(generator);
}

void Stock::updatePrice(const double &timeStep, std::default_random_engine &generator)
{
    double tradeImpactExp{0.0};
    double tradeImpactStandardDev{1.0};
    if (buyExecuted == true) {
        tradeImpactExp         = 100 * standardDev * orderVolume / availableStocks; // 100 is empirical value
        tradeImpactStandardDev = 150 * orderVolume / availableStocks; // 150 is empirical value
    } else if (sellExecuted == true) {
        tradeImpactExp         = -100 * standardDev * orderVolume / availableStocks;
        tradeImpactStandardDev = 150 * orderVolume / availableStocks;
    }

    double randomNumber = drawRandomNumber(generator);
    price               = price + price * ((expectedReturn + tradeImpactExp) * timeStep +
                             randomNumber * standardDev * tradeImpactStandardDev * sqrt(timeStep));
    price               = std::max(price, 0.01);
}
