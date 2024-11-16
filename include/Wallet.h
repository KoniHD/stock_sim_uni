#ifndef WALLET_H
#define WALLET_H

#include "Strategy.h"

#include <vector>

class Wallet {

    double funds;
    Strategy *strategy;
    std::vector<int> stockVolumes;

public:
    Wallet(double funds, Strategy *strategy);
    ~Wallet() = default;

    void composeWallet();
};


#endif // WALLET_H
