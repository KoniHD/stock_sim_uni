#include "../include/Stock.h"

Stock::Stock(double initialPrice, double expectedReturn, double variance, double priceChange) :
    initialPrice{initialPrice}, expectedReturn{expectedReturn}, variance{variance}, priceChange{priceChange} {}
