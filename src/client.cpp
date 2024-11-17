#include "../include/HighRiskStrategy.h"
#include "../include/LowRiskStrategy.h"
#include "../include/Strategy.h"
#include "../include/Wallet.h"

#include <iostream>

int main() {

    double funds{0.0f};
    Strategy *strategy; // TODO Use std::unique_prt<Strategy> instead
    int choice{0};

    // TODO: Call StockMarket() constructor

    std::cout << "Welcome to the stock market!" << std::endl;
    std::cout << "To simulate the stockmarket we will need to create a wallet." << std::endl;
    std::cout << std::endl << "Please enter the amount of funds you would like to start with: ";
    std::cin >> funds;

    while (choice != 1 and choice != 2) {
        std::cout << std::endl << "Please choose a strategy to compose your wallet (1: low risk, 2: high risk): ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                strategy = new LowRiskStrategy();
                std::cout << "Congratulations, you chose the save path and opted for the low risk strategy."
                          << std::endl;
                break;
            case 2:
                strategy = new HighRiskStrategy();
                std::cout << "You were a bit braver and decided for the high risk strategy." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again ..." << std::endl;
        }
    }

    Wallet wallet{funds, strategy};
    // TODO Call compose wallet!

    // TODO Call market.simulateMarket()

    // TODO Call wallet.evaluateResults()
}
