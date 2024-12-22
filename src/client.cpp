#include "../include/HighRiskStrategy.h"
#include "../include/LowRiskStrategy.h"
#include "../include/StockMarket.h"
#include "../include/Strategy.h"
#include "../include/Wallet.h"

#include <algorithm>
#include <cctype>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
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

Stock getStockFromTerminal(const StockMarket &market, const Wallet &wallet) {
    std::string stock_name{};
    while (true) {
        std::cin >> stock_name;

        if (std::cin.fail() or stock_name.empty()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again: ";
        }

        // Unify output
        std::transform(stock_name.begin(), stock_name.end(), stock_name.begin(), ::tolower);
        stock_name[0] = std::toupper(stock_name[0]);

        // Check and return a valid stock
        if (wallet.containsStock(stock_name)) {
            return market.getStock(stock_name);
        }
        std::cout << "The stock name inputed does not exist. Please try again: ";
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
        std::cout << "New extended simulation length: ";
        simulation_length = getTerminalInput();
        // TODO market.setSimulationLength(simulation_length);

        // Choose between 1. Add new funds to cashPosition, 2. Sell stocks, 3. Buy stocks, 4. Don't modify
        choice = 0;
        while (choice != 1 and choice != 2 and choice != 3 and choice != 4) {
            std::cout << "---" << std::endl
                      << "You can now modify your wallet. Do you want to" << std::endl
                      << "(1.) add new funds to the cash position," << std::endl
                      << "(2.) sell stocks from the portfolio," << std::endl
                      << "(3.) buy stocks with available cash or" << std::endl
                      << "(4.) don't modify the wallet at all" << std::endl
                      << "Your choice: ";
            choice = getTerminalInput();

            switch (choice) {
                case 1: // TODO Add new funds to cash position
                    break;
                case 2: // TODO Sell stocks from portfolio
                    break;
                case 3: { // Buy stocks with available cash
                    Stock stock{};
                    unsigned amount_stocks{0};
                    std::cout << "Out of the previous shares of which do you want to buy more stocks: ";
                    stock = getStockFromTerminal(*market, wallet);
                    std::cout << "How many stocks do you want to purchase? (Current cash position: ";
                    amount_stocks = getTerminalInput();
                    if (not wallet.buyStocks(stock, amount_stocks)) {
                        std::cout << "You need to add cash to the wallet or sell a different stock first to increase "
                                     "your cash position."
                                  << std::endl;
                        choice = 0;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    wallet.evaluateResults();

    std::cout << std::endl << "---Simulation finished.---" << std::endl;
    std::cout << "You started the simulation with: " << funds << std::endl;
    std::cout << "After the simulation you have: " << wallet.getFunds() << std::endl;
    std::cout << "You made a profit / loss of: " << wallet.getFunds() - funds << std::endl;

    market->outputPerformance();

    return 0;
}
