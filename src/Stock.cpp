#include "../include/Stock.h"

Stock::Stock(double Price, double expectedReturn, double variance, double priceChange) :
    Price{Price}, expectedReturn{expectedReturn}, variance{variance}, priceChange{priceChange} {}
