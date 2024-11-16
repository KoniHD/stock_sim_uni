//
// Created by User on 16.11.2024.
//

#ifndef STOCKMARKET_H
#define STOCKMARKET_H
#include <vector>


class StockMarket {
public:
    StockMarket(float timeStep, int simulationLength);
    ~StockMarket();

    void simulateMarket();

private:
    // flaot, since we take timeStep as 1 for a time step of one year
    float timeStep;
    int simulationLength;
    std::vector<int> simulationData;
};



#endif //STOCKMARKET_H
