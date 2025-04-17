# Contributing

The project idea comes from: [@nagual98](https://github.com/nagual98) & [@andreadegirolamo99](https://github.com/andreadegirolamo99) \
Team members during the semester: [@EdemDenkey](https://github.com/EdemDenkey) & [@sarpergurbuz](https://github.com/sarpergurbuz). \
We worked to gether until Release v0.0.1 or commit [1bffdf2](https://github.com/KoniHD/stock_sim_uni/commit/1bffdf258fcdc5fd6574a668b9470533684fa334).

This project is meant to showcase my personal C++20 knowledge. Therefore everything past [1bffdf2](https://github.com/KoniHD/stock_sim_uni/commit/1bffdf258fcdc5fd6574a668b9470533684fa334) will be my own doing. Continuing work done by my team mates will be in their own repos.

# Contents

- [Contributing](#contributing)
- [Contents](#contents)
- [Remarks for implementation and usage](#remarks-for-implementation-and-usage)
- [Learning goals](#learning-goals)
  - [Currently in works](#currently-in-works)
  - [Helpful for the project](#helpful-for-the-project)
    - [Plot simulation](#plot-simulation)


Our group project implements a stockmarket simulation. The idea description can also be found again in [idea.md](https://github.com/KoniHD/stock_sim_uni/blob/main/idea.md)

# Remarks for implementation and usage
- **Important:** Enter sufficient funds for values (roughly >3000) such that wallet will be properly filled 
- Stock evaluation: lowRisk: standarddev < 10%, midRisk < 14% otherwise highRisk \
value based on [iShares World Minimum Volatility](https://www.ishares.com/de/privatanleger/de/produkte/251382/ishares-msci-world-minimum-volatility-ucits-etf?switchLocale=y&siteEntryPassthrough=true) and [Shares USA Min Vol Factor](https://www.ishares.com/us/products/239695/ishares-msci-usa-minimum-volatility-etf) \
Further readings on theory: [Investopedia - Standard Deviation](https://www.investopedia.com/ask/answers/021915/how-standard-deviation-used-determine-risk.asp#toc-how-are-standard-deviation-and-variance-related) and [Investopedia - 5 Principal Risk Measures](https://www.investopedia.com/terms/r/riskmeasures.asp)
- lowRiskStrategy --> 50% low-risk stocks, 30% mid-risk stocks 20% high-risk stocks
- highRiskStrategy --> 20% low-risk stocks, 30% mid-risk stocks and 50% high-risk stocks
- split money to be invested evenly among all stocks in respective category
- Stock.updatePrice() implements one time step according to [Investopedia - How to Use Monte Carlo Simulation With GBM](https://www.investopedia.com/articles/07/montecarlo.asp) for each stock
- Simulation is implemented with monthly simulation time steps

# Learning goals

I want to use this project as a challenge to write a GBM simulation with high performant code using modern C++20 features. Additionally I want to have each class covered with test cases and documented with doxgen.

On github I want to have automations for testing when merging to the main branch as well as automatically deploying the documentation.

## Currently in works

- [ ] Going over all classes to remove slop coming from the missing communication with my previous team members. Doing so in a test driven manner: **writting test cases** while deleting slop
- [ ] Improving runtime performance based on profiling and other tools to make it **blazingly fast**
- [ ] Setting up dependencies correctly. Missing dependency declaration to https://github.com/nlohmann/json
- [ ]  Correct workflow setup for deployment:
  - [ ]  Check deployments
- [ ]  Possibly using a nicer looking doxygen style
- [ ]  Improving contents of documentation:
  - [ ]  Make it complete
  - [ ]  Add better explanation on how the stockmarket is simulated
  - [ ]  Add UML class diagram

## Helpful for the project

* Directory structure:
```bash
group-07
|----docs/html  // doxygen-style documentation. Gets updated by an automatic workflow run
|----include    // .h files
|----input      // directory for initial stock data in json format
|----src        // .cpp files -> actual code xD
|----tests      // test wirtten in doctest + profiling
```
* Project documentation [here](https://konihd.github.io/stock_sim_uni/)

### Plot simulation

After executing `stockmarket` you can use the provided python script to create a plot of individual stock performances.

```bash
python3 src/plot_price_history.py
```
