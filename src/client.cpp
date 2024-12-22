#include "../include/HighRiskStrategy.h"
#include "../include/LowRiskStrategy.h"
#include "../include/StockMarket.h"
#include "../include/Strategy.h"
#include "../include/Wallet.h"

#include <iostream>
#include <memory>
#include <utility>

#define MAX_SIM_ITERATIONS 20

unsigned getTerminalInput() {
    int input{-1};
    while (true) {
        std::cin >> input;

        if (std::cin.fail()) { // Check if input failed
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive integer: ";
        } else if (input <= 0) {
            std::cout << "Input is not positive. Please enter again: ";
        } else {
            return static_cast<unsigned>(input);
        }
    }
}

int main() {
    double funds{0.0};
    unsigned choice{0};
    unsigned simulation_length{0};
    std::unique_ptr<Strategy> strategy;
    std::shared_ptr<StockMarket> market;

    // Determine the simulation length
    std::cout << "---Welcome to the stock market!--" << std::endl;
    std::cout << "This is a simulation of a stockmarket which you can influence!!" << std::endl;
    std::cout << "First input how long you want the simulation to run (Unit: Years, int): ";
    simulation_length = getTerminalInput();
    market            = std::make_shared<StockMarket>(1.0f / 12.0f, simulation_length);

    // Create Wallets
    std::cout << std::endl << "---Wallet creation---" << std::endl;
    std::cout << "Awesome! Now let's create some wallets based on your input!" << std::endl;
    std::cout << "Please enter the amount of funds you would like to start with: ";
    funds = getTerminalInput();

    while (choice != 1 and choice != 2) {
        std::cout << "Please choose a strategy to compose your wallet (1: low risk, 2: high risk): ";
        std::cin >> choice;
        if (choice == 1) {

            strategy = std::make_unique<LowRiskStrategy>();
            std::cout << "Congratulations, you chose the save path and opted for the low risk strategy." << std::endl;
        } else if (choice == 2) {

            strategy = std::make_unique<HighRiskStrategy>();
            std::cout << "You were a bit braver and decided for the high risk strategy." << std::endl;
        } else {

            std::cout << "Invalid choice. Try again ..." << std::endl;
        }
    }

    Wallet wallet = Wallet(funds, std::move(strategy), market);


    // Run simulation as long as user wants max. 20 times
    for (unsigned i{0}; i < MAX_SIM_ITERATIONS; ++i) {
        market->simulateMarket();
        choice = 0;

        std::cout << std::endl
                  << "---" << std::endl
                  << "After running the simulation these are the performance metrics:" << std::endl;
        // TODO market->printCurrentStockPrices();
        wallet.printWalletInfo();
        while (choice != 1 and choice != 2) {
            std::cout << "---" << std::endl
                      << "Now chose whether you like to (1: end the simulation) or (2: extend the simulation): ";
            choice = getTerminalInput();
        }

        // End simulation
        if (choice == 1) {
            break;
        }

        // Extend simulation for new simulation length
        simulation_length = 0;
        std::cout << "You chose to extend the simulation. Now please enter the extended simulation length: ";
        simulation_length = getTerminalInput();
        // TODO market.setSimulationLength(simulation_length);
    }

    wallet.evaluateResults();

    std::cout << std::endl << "---Simulation finished.---" << std::endl;
    std::cout << "You started the simulation with: " << funds << std::endl;
    std::cout << "After the simulation you have: " << wallet.getFunds() << std::endl;
    std::cout << "You made a profit / loss of: " << wallet.getFunds() - funds << std::endl;

    market->outputPerformance();

    return 0;
}
