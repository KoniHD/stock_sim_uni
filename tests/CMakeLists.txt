cmake_minimum_required(VERSION 3.28)

project(StockMarketTests)

# Include doctest library if necessary from github
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(doctest)

include(doctest)

add_executable(stockmarket_tests
    ${SRC_DIR}
    unit_tests.cpp
)

target_include_directories(stockmarket_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(stockmarket_tests
    PRIVATE
        doctest::doctest
)

doctest_discover_tests(stockmarket_tests)

###############################################################################
# Adding profiling target
###############################################################################

# Add profiling target using GNU Profiler
add_executable(profiling 
    ${SRC_DIR}
    profiling.cpp
)

target_include_directories(profiling
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(profiling
        PRIVATE
            -pg
            -O3     # comment this line to disable optimizations
    )

    target_link_options(profiling
        PRIVATE
            -pg
    )   
endif()

