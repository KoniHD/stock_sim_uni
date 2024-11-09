# Project: Simulate trading in a stock market

Idea contributed by Andrea De Girolamo <andrea.de-girolamo@tum.de> and Michael Pio Basile <michael.basile@tum.de>.

## General project description

The goal of this project is to simulate the performance of certain portfolios in a simulated stock market. The whole project is divided into 2 simulations: the market simulation and the investor simulation. Later, it will be possible to create interactions between the simulations of the investors and the simulations of the market, therefore creating cause and effect relationships.


The market simulation will involve the creation of a stochastic process through a mathematical model, in which the performance of each share is represented by a pseudo-random function that evolves over time. The trend of the shares will be characterized by statistical parameters that will determine their volatility over time.

The investor simulation will involve the management of many stock wallets, with each wallet being able to follow investment 'strategies'. In the first phase, the market shares will be assigned at the beginning of the simulation and will stay in the assigned wallets until the end of the simulation. Later, the wallets will be able to buy and sell market shares during the simulation by following the selected 'strategies'.

## Sources

- To better understand what the topic is about: https://en.wikipedia.org/wiki/Stock_market_simulator
- To understand what risk management is and how to deal with it (Monte Carlo simulations, statistical parameters for shares): https://www.investopedia.com/risk-management-4689652

- If you want to know more about mathematics for finance, this is a basic book on it:
https://link.springer.com/chapter/10.1007%2F1-85233-846-6_1

## Sprint 1
In the first sprint, at the beginning of the simulation, the wallets will be initialized with a limited amount of market shares. The market will evolve and modify the amount of money in the wallets. In this phase, it will be possible to choose between two types of investment 'strategies', a low-risk/low-return strategy and a high-risk strategy with more chance of higher income.

### Definion of "done"
- User will be able to input:
    - funds to invest in the market
    - strategies (e.g. percentages of available funds used on different shares, the user can choose among different possibilities)
    - shares (e.g. array of strings representing the name of the company)
    - shares' statistical parameters (e.g. change in stock market, standard deviation of returns, expected return, all float/double numbers)
    
#### Example of input
    "input": {
        "fund": 1000000, // amount of money to invest for one wallet
        "strategies": 1, // option of multichoice menu for numbered strategies for one wallet
                         // A "strategy" is a procedure to distribute invested money (fund) on shares
                         // e.g. 50% on low-risk shares, 30% on mid-risk shares, 20% on high-risk shares
        "shares": ["Google", "Amazon", "Tesla", "Ferrero"], // array of strings, each string is the company to which the shares refer
        "variance": [3.1415927, 1.5707963, 6.2831853, 1.0471975], // statistical parameters for each share
        "price_change": [-4.27, 2.75, 0.23, 5.02], // statistical parameters for each share
        "expected_return": [0.10, 0.05, 0.2, 0.25], // statistical parameters for each share (percentage)
        "initial_value": [10.34, 1.92, 5.23, 4.01] // initial values of the shares
    }


- Output will be:
    - trends of the market shares (e.g. a float/double data structure which can register the fluctuations) at the end of the market simulation
    - funds available on the wallets, or percentage of income/loss, at the end of the wallet investments simulation

#### Example of output
    "output": {
        "trend_google": [10.34, 9.84, 11.05, 13.22, 25.85, ...], // trends for each share
        "trend_amazon": [1.92, 1.89, 1.85, 1.95, 1.99, ...], // trends for each share
        "trend_tesla": [5.23, 25.23, 24.78, 17.12, 4.56, ...], // trends for each share
        "trend_ferrero": [4.01, 4.02, 4.04, 4.51, 5.01, ...], // trends for each share
        ...,
        "final_funds": 1014593.52 // final amount of money in the wallet
                                  // alternatively: "income": 0.23, percentage of income at the end of the simulation
    }

## Sprint 2
The objective of the second sprint is, thanks to the use of object-oriented programming, to create different classes for shares, wallets, strategies.Through this code refactoring, it will be possible to create interactions between the market simulation and the wallets simulation. A massive shares purchase in the market will consequentially change the value of the shares themselves. The statistical data concerning the recent market fluctuations and the quotes will be registered, and they can be utilized in the single investment strategies.

### Definition of "done"
- The market model and the investment model were successfully converted to object-oriented models

#### Example of possible class implementation

    "Share": {
        "name": "string",
        "startValue": "initial_market_value",
        "variance": "statParam1",
        "price_change": "statParam2",
        "expected_return": "statParam3"
    }

    "Wallet": {
        "name": "string",
        "funds": "float",
        "shares": "array(int)",
        "strategy": "int".
    }

    "Strategy": {
        "id": "int",
        "fppsr": "array(double)" //fppsr = funding percentage per share risk
    }

- The simulations were correctly interconnected, i.e., there is a cause-effect relationship between purchases and market values: for example, if many wallets buy the same share, this share is affected by this in the form of a rise in its value.

This can be done, for example, by inserting as input of the simulation a new object with information on the number of purchases for each share, and using this information to modify the fluctuations of the shares.



## Sprint 3
In the final sprint, the code performance will be evaluated and improved. To do this, bulk tests will be executed. Finding potential bottlenecks and investigating optimization options for the code, including loop transformations, STL containers, vectorization options and complexity analysis to find potential improvements will also be part of this sprint.

### Definition of "done"
- A file `performance.md` presents the observations from the performance analysis
- The same file presents at least one different optimization technique you applied, with the observable performance effects.

