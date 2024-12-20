# Group-07

Our group project implements the [Stockmarket simulation idea](https://gitlab.lrz.de/tum-i05/public/advprog-project-ideas/-/tree/master/Trading-stock-market-simulation?ref_type=heads). The description can also be found again in [idea.md](https://gitlab.lrz.de/advprog2024/group-07/-/blob/sprint1/idea.md)

## Helpful resources for the project

* Programm structure and class definitions in UML style is in `res/Trading Market Simulation.pdf`

## Details for Sprint 2
- User interaction 
    - Allow user to define simulationlength interacively
    - After simulationlength is over print Stockmarket info (current stockprices) and print Wallet information (cashPosition, portfolioValue, owned stocks (value in owned stock, number stocks)) two Options: 1. end or 2. define interaction
    - If interaction: choose wallet to interact with
    - Next:  (3 Options) 1. Add new funds to cashPosition, 2. Sell stocks, 3. Buy stocks
    - Final: set new simulationlength
- Wallet-StockMarket interaction
    - logic behind changes in wallet composition (purchases/sells) maybe research more ? optional: we still have the used parameter price_change -> maybe that's helpful.
        - which threshold for impact or proportional change ?
        - How mathematically realize the impact

## Optional ideas:

- Class for sectors
    - allows to simulate e.g. overperformance of tech stocks while other sectors underperform
    - statistial values for those sectors could be randomly determined as well
- Better overview on stock market
    - Which stocks in which sector?
    - Which risk catergorization...
    - performance overview of single stocks


## Build and run the code

### Option 1 (strongly recommended)

Use CLion IDE or another IDE the can automatically detect, build and run a CMake Project. If that is the case running the project should be as simple as clicking the run button. \
(VS Code provides an Extension for CMake that also works).

### Option 2 Run CMake manually

*Note:* Our CMake configuration prevents in-source builds. So be aware of that when building.

**Requirement:** You need `CMake` installed and a build system of your choice compatible with it. However we only tested it against `Make` so no guarantee for `Ninja` or other tools. You can the run the following commands (line by line)

Create the build directory:
```bash
mkdir build
cd build
```

Build project:
```bash
cmake ..
make
```

Now you should be able to run the program `./stockmarket` inside the `build/` directory

### Option 3 Manual compile command (strongly discuraged)

*Note:* Works but is tedious

In the terminal run:

```bash
g++ -o stockmarket -I include src/HighRiskStrategy.cpp src/LowRiskStrategy.cpp src/Stock.cpp src/StockMarket.cpp src/Strategy.cpp src/Wallet.cpp src/client.cpp
```

Like option 2 you can now run the `./stockmarket` program.

## Remarks for implementation of Sprint 1
- if you run the program --> client starts running
    1. stock market constructor called --> stocks and statistical values hard coded
    2. Client welcomes you...
    3. based on inputs, call composeWallet() after initializing Wallet with constructor
        - **Important:** Enter sufficient funds for values (roughly >3000) such that wallet will be properly filled 
        - Wallet calls strategy  to compose wallet contents
        - Stock evaluation: lowRisk: standarddev < 10%, midRisk < 14% otherwise highRisk \
        value based on [iShares World Minimum Volatility](https://www.ishares.com/de/privatanleger/de/produkte/251382/ishares-msci-world-minimum-volatility-ucits-etf?switchLocale=y&siteEntryPassthrough=true) and [Shares USA Min Vol Factor](https://www.ishares.com/us/products/239695/ishares-msci-usa-minimum-volatility-etf) \
        Further readings on theory: [Investopedia - Standard Deviation](https://www.investopedia.com/ask/answers/021915/how-standard-deviation-used-determine-risk.asp#toc-how-are-standard-deviation-and-variance-related) and [Investopedia - 5 Principal Risk Measures](https://www.investopedia.com/terms/r/riskmeasures.asp)
        - if lowRiskStrategy --> 50% low-risk stocks, 30% mid-risk stocks 20% high-risk stocks
        - if highRiskStrategy --> 20% low-risk stocks, 30% mid-risk stocks and 50% high-risk stocks
        - split money to be invested evenly among all stocks in respective category
    4. client calls simulateMarket() automatically, timeStepSize and simulationLength hard coded
        - simulateMarket() iteratively calls Stock.updatePrice() for each stock
        - Stock.updatePrice() implements one time step according to [Investopedia - How to Use Monte Carlo Simulation With GBM](https://www.investopedia.com/articles/07/montecarlo.asp) for each stock
    5. client calls evaluateResults() from Wallet
    6. printPerformance() returns stck trends for all stocks.

## Final remarks

- We used GCC Version 13.2 for successful compilation but any compiler supporting C++20 should work.
- We haven't had time to implement tests yet hence the empty `test/` directory.
- The documentation in `doc/html/index.html` is not done as we plan to introduce doxygen style documentation later on in the project so this is also "work-in-progress"