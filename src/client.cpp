#include "HighRiskStrategy.h"
#include "LowRiskStrategy.h"
#include "Stock.h"
#include "StockMarket.h"
#include "Strategy.h"
#include "Wallet.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#define MAX_SIM_ITERATIONS 20

unsigned getTerminalInput()
{
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

Stock& getStockFromTerminal(StockMarket &market, const Wallet &wallet)
{
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
        stock_name[0] = static_cast<char>(std::toupper(stock_name[0]));

        // Check and return a valid stock
        if (wallet.containsStock(stock_name)) {
            return market.getStock(stock_name);
        }
        std::cout << "The stock name inputed does not exist. Please try again: ";
    }
}

int main()
{
    double funds{0.0};
    unsigned user_choice{0};
    unsigned simulation_length{0};
    std::shared_ptr<StockMarket> market;
    std::vector<Wallet> wallets;

    // Determine the simulation length
    std::cout << "---Welcome to the stock market!--" << std::endl;
    std::cout << "This is a simulation of a stockmarket which you can influence!!" << std::endl;
    std::cout << "First input how long you want the simulation to run (Unit: Months, int): ";
    simulation_length = getTerminalInput();
    market = std::make_shared<StockMarket>(1.0 / 12.0, simulation_length, "../input/stocks.json");


    // Create Wallets
    std::cout << std::endl << "---Wallet creation---" << std::endl;
    std::cout << "Awesome! Now let's create some wallets based on your input!" << std::endl;
    std::cout << "First: Enter the amount of wallets you want to create (max. 4): ";
    unsigned num_wallets{getTerminalInput()};
    while (num_wallets > 4) {
        std::cout << "You are very ambitious. However please enter a lower amount: ";
        num_wallets = getTerminalInput();
    }

    for (unsigned i{0}; i < num_wallets; ++i) {
        std::unique_ptr<Strategy> strategy;

        std::cout << std::endl
                  << "---Wallet No." << std::to_string(i + 1) << "---" << std::endl
                  << "Please enter the amount of funds you would like wallet No." << std::to_string(i + 1)
                  << " to have: ";
        funds = getTerminalInput();

        user_choice = 0;
        while (user_choice != 1 and user_choice != 2) {
            std::cout << "Please choose a strategy to compose your wallet (1: low risk, 2: high risk): ";
            std::cin >> user_choice;
            if (user_choice == 1) {
                strategy = std::make_unique<LowRiskStrategy>();
                std::cout << "Congratulations, you chose the save path and opted for the low risk strategy."
                          << std::endl;
            } else if (user_choice == 2) {
                strategy = std::make_unique<HighRiskStrategy>();
                std::cout << "You were a bit braver and decided for the high risk strategy." << std::endl;
            } else {
                std::cout << "Invalid choice. Try again ..." << std::endl;
            }
        }

        wallets.emplace_back(funds, std::move(strategy), market);
    }


    // Run simulation as long as user wants max. 20 times
    for (unsigned i{0}; i < MAX_SIM_ITERATIONS; ++i) {
        market->simulateMarket();

        std::cout << std::endl
                  << "---" << std::endl
                  << "After running the simulation these are the performance metrics:" << std::endl;
        // TODO market->printCurrentStockPrices();
        for (size_t i{0}; i < num_wallets; ++i) {
            std::cout << std::endl << "---Wallet No." << std::to_string(i + 1) << " Info:---";
            wallets.at(i).printWalletInfo();
        }

        user_choice = 0;
        while (user_choice != 1 and user_choice != 2) {
            std::cout << "---" << std::endl
                      << "Now chose whether you like to (1: end the simulation) or (2: extend the simulation): ";
            user_choice = getTerminalInput();
        }

        // End simulation
        if (user_choice == 1) {
            break;
        }

        // Extend simulation for new simulation length
        simulation_length = 0;
        std::cout << "New extended simulation length: ";
        simulation_length = getTerminalInput();
        // TODO market.setSimulationLength(simulation_length);

        // Pick whether and with which wallet to interact with
        unsigned wallet_choice = 1;
        do {
            std::cout << "Do you want to interact with a Wallet (Opt. 1-" << std::to_string(num_wallets)
                      << ") or leave all wallets unchanged (Opt. " << std::to_string(num_wallets + 1) << "): ";
            wallet_choice = getTerminalInput();
        } while (wallet_choice > num_wallets + 1);
        --wallet_choice;

        // Leave all wallets unchanged for the next iteration.
        if (wallet_choice == num_wallets) {
            continue;
        }

        // Choose between 1. Add new funds to cashPosition, 2. Sell stocks, 3. Buy stocks, 4. Don't modify
        user_choice = 0;
        while (user_choice != 1 and user_choice != 2 and user_choice != 3 and user_choice != 4) {
            std::cout << "---" << std::endl
                      << "You can now modify your wallet. Do you want to" << std::endl
                      << "(1.) add new funds to the cash position," << std::endl
                      << "(2.) sell stocks from the portfolio," << std::endl
                      << "(3.) buy stocks with available cash or" << std::endl
                      << "(4.) don't modify the wallet at all" << std::endl
                      << "Your choice: ";
            user_choice = getTerminalInput();

            switch (user_choice) {
                case 1: { // add money to cash position
                    double new_cash{0.0};
                    std::cout << "Enter the amount of money you want to add to your cashposition: ";
                    new_cash = getTerminalInput();
                    wallets.at(wallet_choice).addToCashposition(new_cash);
                    break;
                }
                case 2: { // Sell stocks from portfolio
                    unsigned amount_stocks{0};
                    std::cout << "Considering the shares in your wallet, of which do you want to sell stocks: ";
                    Stock &stock = getStockFromTerminal(*market, wallets.at(wallet_choice));
                    stock = getStockFromTerminal(*market, wallets.at(wallet_choice));
                    std::cout << "How many stocks do you want to sell? ";
                    amount_stocks = getTerminalInput();
                    bool success = wallets.at(wallet_choice).sellStocks(stock, amount_stocks);
                    if (not success) {
                        std::cout << "You need to either sell fewer stocks of this type or select a differnt one. "
                        << std::endl;
                        user_choice = 0;
                    }
                    break;
                }
                case 3: { // Buy stocks with available cash
                    unsigned amount_stocks{0};
                    std::cout << "Out of the previous shares of which do you want to buy more stocks: ";
                    Stock &stock = getStockFromTerminal(*market, wallets.at(wallet_choice));
                    //stock = getStockFromTerminal(*market, wallets.at(wallet_choice));
                    std::cout << "How many stocks do you want to purchase? ";
                    amount_stocks = getTerminalInput();
                    bool success   = wallets.at(wallet_choice).buyStocks(stock, amount_stocks);
                    if (not success) {
                        std::cout << "You need to add cash to the wallet or sell a different stock first to increase "
                                     "your cash position."
                                  << std::endl;
                        user_choice = 0;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    for (Wallet &wallet: wallets) {
        wallet.evaluateResults();
    }

    std::cout << std::endl << "---Simulation finished.---" << std::endl;
    size_t i{0};
    for (const Wallet &wallet: wallets) {
        std::cout << std::endl << "-Stats for wallet No." << std::to_string(++i) << " :" << std::endl;
        std::cout << "You started the simulation with: " << wallet.getFunds() << std::endl;
        std::cout << "After the simulation your portfolio is worth: " << wallet.getPortfolioValue() << std::endl;
        std::cout << "You made a profit / loss of: " << wallet.getPortfolioValue() - wallet.getFunds() << std::endl;
    }

    market->outputPerformance();

    return 0;
}
