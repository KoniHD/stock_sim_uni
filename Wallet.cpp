#include "include/Wallet.h"


Wallet::Wallet(int funds, Strategy strategy) {
    this->funds = funds;
    this->strategy = strategy;
}


void Wallet::composeWallet(Strategy strategy) { strategy.pickStocks(); }
