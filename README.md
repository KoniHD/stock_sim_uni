# Group-07

## Helpful links

* Programm structure in UML: https://apollon.ase.in.tum.de/9WJykdePRkab77YN5YeJ?view=COLLABORATE

## Remarks for implementation of Sprint 1
- if you run the program --> client starts running
    1. stock market constructor called --> stocks and statistical values hard coded
    2. Client welcomes you... (already implemnted)
    3. based on inputs, call composeWallet() after initializing Wallet with constructor
        - Wallet calls strategy  to compose wallet contents
        - lowRisk: expected return < 7% && standarddev < someValue (Research needed); otherwise highRisk
        - if lowRisk --> 80% low risk shares, 20% highRisk shares
        - if highRisk --> 80% high risk shares, 20% lowRisk shares
        - split money to be invested evenly among all stocks in respective category
    4. client calls simulateMarket(), timeStepSize and simulationLength hard coded
        - simulateMarket() iteratively calls simulateBehavior() for each stock
        - simulateBehvior() implements one time step according to https://www.investopedia.com/articles/07/montecarlo.asp for each stock
        - simualteMarket() returns stockTrend for all stocks
    5. client calls evaluateResults() from Wallet