#include "../include/HighRiskStrategy.h"
#include "../include/LowRiskStrategy.h"
#include "../include/StockMarket.h"
#include "../include/Strategy.h"
#include "../include/Wallet.h"

#include <iostream>
#include <memory>

int main() {

    double funds{0.0f};
    std::unique_ptr<Strategy> strategy;
    int choice{0};

    StockMarket market = StockMarket{1.0f / 365.0f, 1};

    std::cout << "Welcome to the stock market!" << std::endl;
    std::cout << "To simulate the stockmarket we will need to create a wallet." << std::endl;
    std::cout << std::endl << "Please enter the amount of funds you would like to start with: ";
    std::cin >> funds;

    while (choice != 1 and choice != 2) {
        std::cout << std::endl << "Please choose a strategy to compose your wallet (1: low risk, 2: high risk): ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                strategy = std::make_unique<LowRiskStrategy>();
                std::cout << "Congratulations, you chose the save path and opted for the low risk strategy."
                          << std::endl;
                break;
            case 2:
                strategy = std::make_unique<HighRiskStrategy>();
                std::cout << "You were a bit braver and decided for the high risk strategy." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again ..." << std::endl;
        }
    }

    Wallet wallet{funds, std::move(strategy), market};

    market.simulateMarket();

    wallet.evaluateResults();

    std::cout << "---" << std::endl << "Simulation finished." << std::endl;
    std::cout << "You started the simulation with: " << funds << std::endl;
    std::cout << "After the simulation you have: " << wallet.getFunds() << std::endl;
    std::cout << "You made a profit / loss of: " << wallet.getFunds() - funds << std::endl;

    return 0;
}
