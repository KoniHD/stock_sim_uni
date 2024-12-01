#include "../include/Stock.h"
#include <string>
#include <math.h>
#include <random>
#include <vector>

/* TODO MY QUESTIONS:
 * change timestep do double for consistency
 * initiaize generator in stockmarket
 * updatePrice right now void --> should we instead return to make recording of the time series easier?
 * which statistical values?
 * what about priceChange?
 * Stock's name attribute vs. map?
 */


// Constructor
Stock::Stock(double price, double expectedReturn, double variance, double priceChange) :
    price{price}, expectedReturn{expectedReturn}, variance{variance}, priceChange{priceChange}, priceTimeSeries({price}) {}

// Getters
double Stock::getPrice() const {return price;}

double Stock::getExpectedReturn() const {return expectedReturn;}

double Stock::getVariance() const {return variance;}

std::string_view Stock::getName() const {return name;}

std::vector<double> Stock::getPriceTimeSeries() const {return priceTimeSeries;}

// Setters
void Stock::saveCurrentPrice(double price) {priceTimeSeries.push_back(price);}

void Stock::setPrice(double price) {this->price = price;}

void Stock::setExpectedReturn(double expectedReturn) {this->expectedReturn = expectedReturn;}

void Stock::setVariance(double variance) {this->variance = variance;}

// generates random number from standard normal distribution
double drawRandomNumber(std::default_random_engine& generator) {
    double mean{0.0};
    double var{1.0};
    std::normal_distribution<double> distribution{mean, sqrt(var)};
    return distribution(generator);
}

// simulates new price for one timestep with Geometric Brownian Motion (see link in README)
void Stock::updatePrice(const double& timeStep, std::default_random_engine& generator) {
    double randomNumber = drawRandomNumber(generator);
    price = price + price * (expectedReturn * timeStep + randomNumber * sqrt(variance * timeStep));
}