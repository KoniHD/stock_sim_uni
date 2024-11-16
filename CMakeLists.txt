cmake_minimum_required(VERSION 3.28)
project(group_07)

set(CMAKE_CXX_STANDARD 14)

add_executable(group_07
    client.cpp
        include/Stock.h
        Stock.cpp
        Wallet.cpp
        StockMarket.h
        StockMarket.cpp)
