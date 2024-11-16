//
// Created by User on 16.11.2024.
//

#ifndef STOCKMARKET_H
#define STOCKMARKET_H
#include <vector>


class StockMarket {
    // float, since we take timeStep as 1 for a time step of one year
    float timeStep;
    int simulationLength;

public:
    StockMarket(float timeStep, int simulationLength);
    ~StockMarket()=default;

    std::vector<int> simulationData;

    // arguments and returntype might still need to be changed
    void simulateMarket();
};



#endif //STOCKMARKET_H
