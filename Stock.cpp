//
// Created by User on 16.11.2024.
//

#include "include/Stock.h"

Stock::Stock(double initialPrice, double expectedReturn, double variance, double priceChange) {
    this->initialPrice = initialPrice;
    this->expectedReturn = expectedReturn;
    this->variance = variance;
    this->priceChange = priceChange;
}
