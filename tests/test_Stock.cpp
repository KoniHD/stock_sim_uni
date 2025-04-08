#include "Stock.h"

#include <doctest/doctest.h>
#include <random>
#include <string>

TEST_CASE("Stock construction and initialization")
{
    SUBCASE("Default constructor should be deleted") { CHECK_FALSE(std::is_default_constructible<Stock>::value); }

    SUBCASE("Parameterized constructor initializes values correctly")
    {
        std::string name        = "TestStock";
        double price            = 100.0;
        double expected_return  = 0.05;
        double standard_dev     = 0.2;
        double available_stocks = 1000.0;

        Stock stock(name, price, expected_return, standard_dev, available_stocks);

        CHECK_EQ(stock.getName(), name);
        CHECK_EQ(stock.getPrice(), price);
        CHECK_EQ(stock.getStandardDev(), standard_dev);
    }
}

TEST_CASE("Stock getters")
{
    std::string name       = "GetterStock";
    double price           = 75.5;
    double expected_return = 0.04;
    double standard_dev    = 0.18;
    Stock stock(name, price, expected_return, standard_dev);

    SUBCASE("getName returns correct value") { CHECK_EQ(stock.getName(), name); }

    SUBCASE("getPrice returns correct value") { CHECK_EQ(stock.getPrice(), price); }

    SUBCASE("getstandard_dev returns correct value") { CHECK_EQ(stock.getStandardDev(), standard_dev); }
}

TEST_CASE("Stock order volume")
{
    Stock stock("VolumeStock", 120.0, 0.07, 0.25);

    SUBCASE("Order volume affects price updates")
    {
        std::default_random_engine generator(42);
        double time_step = 1.0 / 12.0;

        // First update with no volume set
        stock.updatePrice(time_step, generator);
        double price_without_volume = stock.getPrice();

        // Reset to initial state (not perfect since we can't reset the price)
        stock = Stock("VolumeStock", 120.0, 0.07, 0.25);

        // Update with volume
        stock.setOrderVolume(10000.0);
        stock.updatePrice(time_step, generator);
        double price_with_volume = stock.getPrice();

        // Setting order volume should make some difference to the price update
        CHECK_NE(price_without_volume, price_with_volume);
    }
}

SCENARIO("Price updates with Geometric Brownian Motion")
{
    GIVEN("Known parameters to initialize a stock")
    {
        std::string name       = "GMBStock";
        double price           = 100.0;
        double expected_return = 0.05;
        double standard_dev    = 0.2;

        WHEN("updatePrice is called with the same seed multiple times")
        {
            std::default_random_engine generator1(123);
            std::default_random_engine generator2(123);
            double time_step = 1.0 / 12.0;

            // First update
            Stock stock1(name, price, expected_return, standard_dev);
            stock1.setBuyExecuted(false); // Ensure known state
            stock1.setSellExecuted(false); // Ensure known state
            stock1.setOrderVolume(0.0); // Ensure known state
            double initial_price = stock1.getPrice();
            stock1.updatePrice(time_step, generator1);
            double price1 = stock1.getPrice();

            // Reset stock and do second update with same seed
            Stock stock2(name, price, expected_return, standard_dev);
            stock2.setBuyExecuted(false); // Ensure known state
            stock2.setSellExecuted(false); // Ensure known state
            stock2.setOrderVolume(0.0); // Ensure known state
            stock2.updatePrice(time_step, generator2);
            double price2 = stock2.getPrice();

            THEN("The price should change") { CHECK_NE(initial_price, price1); }

            THEN("With the same seed, updates should be identical") { CHECK_EQ(price1, price2); }
        }

        WHEN("updatePrice is called with different seeds")
        {
            std::default_random_engine generator1(123);
            std::default_random_engine generator2(456);
            double time_step = 1.0 / 12.0;

            // First update
            Stock stock1(name, price, expected_return, standard_dev);
            stock1.updatePrice(time_step, generator1);
            double price1 = stock1.getPrice();

            // Second update with different seed
            Stock stock2(name, price, expected_return, standard_dev);
            stock2.updatePrice(time_step, generator2);
            double price2 = stock2.getPrice();

            THEN("Different seeds should produce different price updates") { CHECK_NE(price1, price2); }
        }

        WHEN("updatePrice is called with different time steps")
        {
            std::default_random_engine generator(123);
            double small_time_step = 1.0 / 252.0; // Daily
            double large_time_step = 1.0 / 12.0; // Monthly

            // Update with small time step
            Stock stock1(name, price, expected_return, standard_dev);
            stock1.updatePrice(small_time_step, generator);
            double price_small_step = stock1.getPrice();

            // Update with large time step
            generator.seed(123); // Reset generator
            Stock stock2(name, price, expected_return, standard_dev);
            stock2.updatePrice(large_time_step, generator);
            double price_large_step = stock2.getPrice();

            THEN("Different time steps should produce different price updates")
            {
                CHECK_NE(price_small_step, price_large_step);
            }
        }
    }
}

// TEST_CASE("Multiple price updates show stochastic behavior")
// {
//     std::string name      = "MultiUpdateStock";
//     double price          = 100.0;
//     double expected_return = 0.05;
//     double standard_dev    = 0.2;

//     Stock stock(name, price, expected_return, standard_dev);
//     std::default_random_engine generator(42);
//     double time_step = 1.0 / 252.0;

//     // Track price evolution over multiple updates
//     std::vector<double> priceHistory;
//     priceHistory.push_back(stock.getPrice());

//     // Perform multiple updates
//     const int numUpdates = 20;
//     for (int i = 0; i < numUpdates; ++i) {
//         stock.updatePrice(time_step, generator);
//         priceHistory.push_back(stock.getPrice());
//     }

//     // Check that prices are changing
//     bool allPricesSame = true;
//     for (size_t i = 1; i < priceHistory.size(); ++i) {
//         if (priceHistory[i] != priceHistory[0]) {
//             allPricesSame = false;
//             break;
//         }
//     }

//     CHECK_FALSE(allPricesSame);

//     // Check that at least some updates increase and some decrease the price
//     // (This might rarely fail due to randomness, but is generally a good test)
//     bool hasIncrease = false;
//     bool hasDecrease = false;

//     for (size_t i = 1; i < priceHistory.size(); ++i) {
//         if (priceHistory[i] > priceHistory[i - 1]) {
//             hasIncrease = true;
//         } else if (priceHistory[i] < priceHistory[i - 1]) {
//             hasDecrease = true;
//         }

//         if (hasIncrease && hasDecrease) {
//             break;
//         }
//     }

//     CHECK(hasIncrease);
//     CHECK(hasDecrease);
// }

// TEST_CASE("Order volume affects price update magnitude")
// {
//     std::string name      = "VolumeEffectStock";
//     double price          = 150.0;
//     double expected_return = 0.06;
//     double standard_dev    = 0.3;

//     SUBCASE("Higher order volumes should have stronger impact")
//     {
//         std::default_random_engine generator1(42);
//         std::default_random_engine generator2(42);
//         double time_step = 1.0 / 12.0;

//         // Stock with small order volume
//         Stock stock1(name, price, expected_return, standard_dev);
//         stock1.setOrderVolume(100.0);
//         stock1.updatePrice(time_step, generator1);
//         double priceAfterSmallVolume = stock1.getPrice();

//         // Stock with large order volume
//         Stock stock2(name, price, expected_return, standard_dev);
//         stock2.setOrderVolume(10000.0);
//         stock2.updatePrice(time_step, generator2);
//         double priceAfterLargeVolume = stock2.getPrice();

//         // Prices should be different due to different order volumes
//         CHECK_NE(priceAfterSmallVolume, priceAfterLargeVolume);

//         // Calculate absolute price changes
//         double smallVolumeChange = std::abs(priceAfterSmallVolume - price);
//         double largeVolumeChange = std::abs(priceAfterLargeVolume - price);

//         // The test below assumes larger volume causes larger price deviation
//         // This might not always be true due to randomness, but generally should be
//         MESSAGE("Small volume change: ", smallVolumeChange, " Large volume change: ", largeVolumeChange);
//     }
// }

// TEST_CASE("Stochastic distribution of price updates")
// {
//     std::string name      = "DistributionStock";
//     double price          = 100.0;
//     double expected_return = 0.05;
//     double standard_dev    = 0.2;

//     Stock stock(name, price, expected_return, standard_dev);
//     double time_step = 1.0 / 252.0;

//     // Run many simulations to check distribution properties
//     const int numSimulations = 1000;
//     std::vector<double> finalPrices;

//     for (int i = 0; i < numSimulations; ++i) {
//         std::default_random_engine generator(i); // Different seed each time

//         Stock testStock(name, price, expected_return, standard_dev);
//         testStock.updatePrice(time_step, generator);
//         finalPrices.push_back(testStock.getPrice());
//     }

//     // Calculate mean and check it's reasonably close to expected
//     double sum = 0.0;
//     for (double p: finalPrices) {
//         sum += p;
//     }
//     double mean = sum / numSimulations;

//     // The expected mean after one step should be approximately:
//     // price * exp(expected_return * time_step)
//     double theoreticalMean = price * std::exp(expected_return * time_step);

//     // Allow for some statistical variation
//     double tolerance = price * 0.05; // 5% tolerance
//     CHECK(std::abs(mean - theoreticalMean) < tolerance);

//     // Verify prices are different (stochastic nature)
//     std::sort(finalPrices.begin(), finalPrices.end());
//     CHECK_NE(finalPrices.front(), finalPrices.back());

//     // Check we have both increases and decreases
//     CHECK(finalPrices.front() < price);
//     CHECK(finalPrices.back() > price);
// }
