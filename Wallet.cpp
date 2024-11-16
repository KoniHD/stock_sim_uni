#include "include/Wallet.h"


Wallet::Wallet(double funds, Strategy *strategy) {
    this->funds = funds;
    this->strategy = strategy;
}


void Wallet::composeWallet(Strategy *strategy) { strategy->pickStocks(); }
