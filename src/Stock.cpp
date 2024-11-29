#include "../include/Stock.h"





Stock::Stock(double Price, double expectedReturn, double variance, double priceChange) :
    Price{Price}, expectedReturn{expectedReturn}, variance{variance}, priceChange{priceChange} {}

double Stock::getExpectedReturn() const {
    return expectedReturn;
}

void Stock::updatePrice(double newPrice) {
    Price = newPrice;
}

