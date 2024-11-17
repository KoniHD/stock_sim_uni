#include "../include/Wallet.h"


Wallet::Wallet(double funds, Strategy *strategy) : funds{funds}, strategy{strategy} {}


void Wallet::composeWallet() { strategy->pickStocks(); }
