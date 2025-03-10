cmake_minimum_required(VERSION 3.28)

project("Stockmarket Simulation")

# try to prevent in-source builds
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(
    FATAL_ERROR
      "In-source builds are not allowed. Please create a separate 'build' directory and build in there."
  )
endif()

# set default c++ standard for compile targets
set(CMAKE_CXX_STANDARD 20)

# require C++20, don't allow falling back to older version of standard
set(CXX_STANDARD_REQUIRED ON)

# disable C++ extensions
set(CMAKE_CXX_EXTENSIONS OFF)

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
    src/HighRiskStrategy.cpp 
    src/LowRiskStrategy.cpp 
    src/Stock.cpp
    src/StockMarket.cpp
    src/Strategy.cpp 
    src/Wallet.cpp
)

target_include_directories(stockmarket PUBLIC "include")

target_sources(stockmarket PUBLIC ${SRC_DIR})

# Add profiling target using GNU Profiler
add_executable(profiling tests/profiling.cpp)

target_include_directories(profiling PUBLIC "include")

target_sources(profiling PUBLIC ${SRC_DIR})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(profiling
        PRIVATE
            -pg
            # -O3 # uncomment this line to enable optimizations
    )

    target_link_options(profiling
        PRIVATE
            -pg
    )   
endif()
