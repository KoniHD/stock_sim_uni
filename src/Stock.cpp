#include "../include/Stock.h"

#include <math.h>
#include <random>
#include <string>
#include <utility>
#include <vector>


// Constructor
Stock::Stock(std::string name, double price, double expectedReturn, double variance, double priceChange) :
    name{std::move(name)}, price{price}, expectedReturn{expectedReturn}, variance{variance}, priceChange{priceChange},
    priceTimeSeries({price}) {}

Stock::Stock() : price{0.0}, expectedReturn{0.0}, variance{0.0}, priceChange{0.0} {}

// Getters
double Stock::getPrice() const { return price; }

double Stock::getExpectedReturn() const { return expectedReturn; }

double Stock::getVariance() const { return variance; }

std::string_view Stock::getName() const { return name; }

std::vector<double> Stock::getPriceTimeSeries() const { return priceTimeSeries; }

// Setters
void Stock::saveCurrentPrice(double price) { priceTimeSeries.push_back(price); }

void Stock::setPrice(double price) { this->price = price; }

void Stock::setExpectedReturn(double expectedReturn) { this->expectedReturn = expectedReturn; }

void Stock::setVariance(double variance) { this->variance = variance; }

void Stock::setName(std::string_view name) { this->name = name; }

// generates random number from standard normal distribution
double drawRandomNumber(std::default_random_engine &generator) {
    double mean{0.0};
    double var{1.0};
    std::normal_distribution<double> distribution{mean, sqrt(var)};
    return distribution(generator);
}

// simulates new price for one timestep with Geometric Brownian Motion (see link in README)
void Stock::updatePrice(const double &timeStep, std::default_random_engine &generator) {
    double randomNumber = drawRandomNumber(generator);
    price = price + price * (expectedReturn * timeStep + randomNumber * variance * sqrt(timeStep));
    price = std::max(price, 0.01);
    priceTimeSeries.push_back(price);
}
