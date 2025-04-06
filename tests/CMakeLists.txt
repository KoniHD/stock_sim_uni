cmake_minimum_required(VERSION 3.28)

project(StockMarketTests)

# Include doctest library if necessary from github
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    SOURCE_SUBDIR don-t_add_subdirectory    # don't implicitly perform add_subdirectory(doctest_SOURCE_DIR)
    EXCLUDE_FROM_ALL                        # don't include doctest in the default build
    FIND_PACKAGE_ARGS QUIET
)
FetchContent_MakeAvailable(doctest)

if(doctest_SOURCE_DIR)
    message(STATUS "Doctest not populated -> Downloaded from github")
    set(DOCTEST_INCLUDE_DIR ${doctest_SOURCE_DIR}/doctest CACHE INTERNAL "Path to include folder for doctest")
    include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
else()
    message(STATUS "Doctest already populated (found locally)")
    include(doctest)
endif()

add_executable(stockmarket_tests
    ${SRC_DIR}
    unit_tests.cpp
)

target_include_directories(stockmarket_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${DOCTEST_INCLUDE_DIR}
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

