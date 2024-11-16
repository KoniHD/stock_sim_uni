#include "include/Wallet.h"

Wallet::Wallet(int funds, Strategy strategy) {
    this->fund = funds;
    this->strategy = strategy;
}
