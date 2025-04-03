cmake_minimum_required(VERSION 3.28)

project("Stockmarket Simulation"
    VERSION 0.1
    DESCRIPTION "A stockmarket simulation based on Monte Carlo Simulation with GBM"
    HOMEPAGE_URL https://konihd.github.io/stock_sim_uni/
)

# try to prevent in-source builds
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(
    FATAL_ERROR
      "In-source builds are not allowed. Please create a separate 'build' directory and build in there."
  )
endif()

# Language settings
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# so language servers like clangd know what the buildsystem does
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# windows needs "exported" symbols for linking
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# display many warnings during compilation
# they usually help you find some bugs
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors -Wuninitialized)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W3 /WX)

    # so the dll files are alongside the executables
    # and the windows loader is happy (no more error 0xc0000135)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Create output dir for saving stockmarket results
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

# Add executable target
add_executable(stockmarket src/client.cpp)

set(SRC_DIR 
    ${CMAKE_CURRENT_LIST_DIR}/src/HighRiskStrategy.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/LowRiskStrategy.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/Stock.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/StockMarket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Strategy.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/Wallet.cpp
)

target_include_directories(stockmarket PUBLIC "include")

target_sources(stockmarket PUBLIC ${SRC_DIR})

add_subdirectory(tests EXCLUDE_FROM_ALL)
