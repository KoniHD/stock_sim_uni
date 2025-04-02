#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Stock.h"

#include <doctest/doctest.h>

TEST_CASE("Stock_test")
{
    REQUIRE_FALSE(std::is_default_constructible<Stock>::value);
    double price{100.0};
    double expectedReturn{0.05};
    double standardDev{0.2};
    Stock stock("TestStock", price, expectedReturn, standardDev);
    CHECK_EQ(price, stock.getPrice());
    CHECK_EQ(standardDev, stock.getStandardDev());
    CHECK_EQ("TestStock", stock.getName());
}
