#include "../include/Stock.h"





Stock::Stock(double Price, double expectedReturn, double variance, double priceChange) :
    Price{Price}, expectedReturn{expectedReturn}, variance{variance}, priceChange{priceChange} {}

double Stock::getExpectedReturn() const { //sarper added this, explaiantion is in Stocks.h file
    return expectedReturn;
}

void Stock::updatePrice(double newPrice) {  // sarper added this, explanation is in .h file
    Price = newPrice;
}

