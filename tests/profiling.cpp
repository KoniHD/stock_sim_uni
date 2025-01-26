/**
 * This script is is supposed to test the programs performance.
 * It will proced as follows:
 * 1. Create a StockMarket object based on input/stocks.json
 * 2. Create 4 wallets (the maximal number we allow in client.cpp)
 * 2.1 Wallet 1: 3'000 funds, low risk strategy, Wallet 2: 10'000 funds, high risk strategy, Wallet 3: 3'000 funds, low
 * risk strategy, Wallet 4: 10'000 funds, high risk strategy
 * 3. Run the simulation for 10'000 months.
 * 4. Print the performance of each wallet.
 * 5.1 Extend the simulation for 5'000 months.
 * 5.2 Sell 1 "Google" stock from wallet 1.
 * 6. Finish the simulation.
 */

#include "HighRiskStrategy.h"
#include "LowRiskStrategy.h"
#include "Stock.h"
#include "StockMarket.h"
#include "Wallet.h"

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{

    std::shared_ptr<StockMarket> market = std::make_shared<StockMarket>(1.0 / 12.0, 10'000, "../input/stocks.json");

    std::vector<Wallet> wallets;
    wallets.emplace_back(3000, std::make_unique<LowRiskStrategy>(), market);
    wallets.emplace_back(10'000, std::make_unique<LowRiskStrategy>(), market);
    wallets.emplace_back(3'000, std::make_unique<HighRiskStrategy>(), market);
    wallets.emplace_back(10'000, std::make_unique<HighRiskStrategy>(), market);

    market->simulateMarket();

    for (size_t i = 0; i < wallets.size(); ++i) {
        std::cout << std::endl << "---Wallet No." << std::to_string(i + 1) << " Info:---";
        wallets.at(i).printWalletInfo();
    }

    market->setSimulationLength(5'000);

    Stock google;
    if (wallets.at(0).containsStock("Google")) {
        google = market->getStock("Google");
    }
    wallets.at(0).sellStocks(google, 1);

    market->simulateMarket();

    for (size_t i = 0; i < wallets.size(); ++i) {
        std::cout << std::endl << "---Wallet No." << std::to_string(i + 1) << " Info:---";
        wallets.at(i).printWalletInfo();
    }

    for (Wallet &wallet: wallets) {
        wallet.evaluateResults();
    }

    size_t i{0};
    for (const Wallet &wallet: wallets) {
        std::cout << std::endl << "-Stats for wallet No." << std::to_string(++i) << " :" << std::endl;
        wallet.getPortfolioValue();
        wallet.getFunds();
    }

    market->outputPerformance();

    return 0;
}
