cmake_minimum_required(VERSION 3.28)

project("Stockmarket Simulation")

set(CMAKE_CXX_STANDARD 14)
set(EXE_NAME "stockmarket")

add_executable(${EXE_NAME}
    client.cpp
)


target_include_directories(${EXE_NAME} PUBLIC 
                "include"
)

target_sources(${EXE_NAME} PUBLIC
                HighRiskStrategy.cpp
                LowRiskStrategy.cpp
                Stock.cpp
                Wallet.cpp
                
)