#ifndef WALLET_H
#define WALLET_H

#include <vector>

class Wallet {
public:
    Wallet(int funds, Stragey strategy);
    ~Wallet();

    void composeWallet(Strategy strategy);

private:
    double fund;
    Strategy strategy;
    std::vector<int> stockVolumes; // specify the size of the array
}


#endif // WALLET_H
