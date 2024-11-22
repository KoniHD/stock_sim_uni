# Group-07

## Helpful links

* Programm structure in UML: [Apollon](https://apollon.ase.in.tum.de/9WJykdePRkab77YN5YeJ?view=COLLABORATE)

## Remarks for implementation of Sprint 1
- if you run the program --> client starts running
    1. stock market constructor called --> stocks and statistical values hard coded
    2. Client welcomes you... (already implemnted)
    3. based on inputs, call composeWallet() after initializing Wallet with constructor
        - Wallet calls strategy  to compose wallet contents
        - lowRisk: standarddev < 10%, midRisk < 14% otherwise highRisk \
        value based on [iShares World Minimum Volatility](https://www.ishares.com/de/privatanleger/de/produkte/251382/ishares-msci-world-minimum-volatility-ucits-etf?switchLocale=y&siteEntryPassthrough=true) and [Shares USA Min Vol Factor](https://www.ishares.com/us/products/239695/ishares-msci-usa-minimum-volatility-etf) \
        Further readings on theory: [Investopedia - Standard Deviation](https://www.investopedia.com/ask/answers/021915/how-standard-deviation-used-determine-risk.asp#toc-how-are-standard-deviation-and-variance-related) and [Investopedia - 5 Principal Risk Measures](https://www.investopedia.com/terms/r/riskmeasures.asp)
        - if lowRisk --> 50% low-risk stocks, 30% mid-risk stocks 20% high-risk stocks
        - if highRisk --> 20% low-risk stocks, 40% mid-risk stocks and 30% high-risk stocks
        - split money to be invested evenly among all stocks in respective category
    4. client calls simulateMarket(), timeStepSize and simulationLength hard coded
        - simulateMarket() iteratively calls simulateBehavior() for each stock
        - simulateBehvior() implements one time step according to [Investopedia - Monte Carlo](https://www.investopedia.com/articles/07/montecarlo.asp) for each stock
        - simualteMarket() returns stockTrend for all stocks
    5. client calls evaluateResults() from Wallet