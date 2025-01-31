# Performance

- [Performance](#performance)
  - [Evaluate Performance](#evaluate-performance)
  - [Performance Improvements](#performance-improvements)
    - [1 Simulating and saving all results in one.](#1-simulating-and-saving-all-results-in-one)
    - [Note](#note)
  - [Measurements](#measurements)
    - [1. Absolute time of `./profiling` before our modification](#1-absolute-time-of-profiling-before-our-modification)
    - [2. Absolute time of `./profiling` after modification](#2-absolute-time-of-profiling-after-modification)
    - [3. Discussion of profiler output](#3-discussion-of-profiler-output)
  - [Summary Performance Improvement](#summary-performance-improvement)


## Evaluate Performance

In order to profil the performance of the program a seperate executable is create: `tests/profiling.cpp`. The purpose of this seperate file is to stress-test all classes whithout requiring user input like the `src/client.cpp` file does, since that conflicts with profiling.
Using CMake to create the executable it can be run from the build folder:
```bash
./profiling
gprof ./profiling
```
If you want to examine the output we recommend piping the profiling into a .txt: `gprof ./profiling > ../output/profiling.txt`. \
Additionally we also used the command `time ./profiling` to measure the execution time.

## Performance Improvements

From these two measurements we mainly derived one key bottlenecks:

### 1 Simulating and saving all results in one.

The program up until sprint2 had a function to simulate the market which called each stock to simulate its next timestep and saving it.
After finishing simulation this stock history would be accessed and written so a .csv file.
However the stock history has mathematically no relevance to future prices.
Hence to improve runtime we decided to simulate the next step for a stock and imediately write its  new price to the .csv output.
This saves the memory necessary for storing the stock history as well as iterating over this history in the end again.

Because of this modification we however had to consider the datastructure that stores the stocks in the StockMarket class: An unordered_map (= HashMap). 
This datastructure does not preserve the order of inserted enteries.
In our case we however don't care about this order, only about the order in which stocks are iterated through when simulating the market. Since simulating the market does not change the size of the unordered_map it will not trigger a rehash which ensures that the order in which we iterate through the stocks for each simulation step will not be changed. 
Meaning we can savely use an unordered_map, knowing our data will not be mixed.


### Note

We assume that a lot of function calls marked in the profiling might also be due to our use of an external library `json.hpp`. We didn't modify these parts since we assumed them to already be highly optimized and .json parsing is not in the scope of this project.

## Measurements

The measurements are carried out with an i7-6700HQ @ 2.60 GHz and 16GB RAM. No extra compiler optimizations turned on.

### 1. Absolute time of `./profiling` before our modification

```bash
./profiling  0,44s user 0,22s system 42% cpu 1,543 total
./profiling  0,43s user 0,17s system 42% cpu 1,413 total
./profiling  0,47s user 0,23s system 44% cpu 1,575 total
./profiling  0,40s user 0,23s system 41% cpu 1,522 total
./profiling  0,43s user 0,23s system 45% cpu 1,471 total
```
Average runtime: **0.434s**

### 2. Absolute time of `./profiling` after modification

```bash
./profiling  0,35s user 0,10s system 48% cpu 0,934 to
./profiling  0,37s user 0,09s system 52% cpu 0,886 total
./profiling  0,33s user 0,12s system 52% cpu 0,868 total
./profiling  0,33s user 0,11s system 50% cpu 0,873 total
./profiling  0,35s user 0,10s system 50% cpu 0,894 total
```

Average runtime: **0.346s**

Improvements: ~0.088s equivalent to an improvement of **20.3 %**

### 3. Discussion of profiler output

<details>
<summary>First 3 lines of the profiling output</summary>

```txt
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
  time   seconds   seconds    calls  us/call  us/call  name    
 45.45      0.05     0.05  1132012     0.04     0.04  nlohmann::json_abi_v3_11_3::basic_json<std::map, std::vector, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool, long, unsigned long, double, std::allocator, nlohmann::json_abi_v3_11_3::adl_serializer, std::vector<unsigned char, std::allocator<unsigned char> >, void>::~basic_json()
 18.18      0.07     0.02  1097367     0.02     0.02  bool nlohmann::json_abi_v3_11_3::detail::parser<nlohmann::json_abi_v3_11_3::basic_json<std::map, std::vector, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool, long, unsigned long, double, std::allocator, nlohmann::json_abi_v3_11_3::adl_serializer, std::vector<unsigned char, std::allocator<unsigned char> >, void>, nlohmann::json_abi_v3_11_3::detail::input_stream_adapter>::sax_parse_internal<nlohmann::json_abi_v3_11_3::detail::json_sax_dom_callback_parser<nlohmann::json_abi_v3_11_3::basic_json<std::map, std::vector, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool, long, unsigned long, double, std::allocator, nlohmann::json_abi_v3_11_3::adl_serializer, std::vector<unsigned char, std::allocator<unsigned char> >, void> > >(nlohmann::json_abi_v3_11_3::detail::json_sax_dom_callback_parser<nlohmann::json_abi_v3_11_3::basic_json<std::map, std::vector, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool, long, unsigned long, double, std::allocator, nlohmann::json_abi_v3_11_3::adl_serializer, std::vector<unsigned char, std::allocator<unsigned char> >, void> >*)
  9.09      0.08     0.01   762609     0.01     0.01  std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > nlohmann::json_abi_v3_11_3::detail::concat<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
```
</details>

---
From this output we can clearly see that the `updatePrice` method which is the main function responsible for the simulation as well as related helper functions are called the most.
However we believe that there is no improvement to this function anymore that is worth pursuing.

## Summary Performance Improvement

We achieved a performance improvement of **20.3 %** just by improving our methods.
We don't see any other method with similar improvment potential except turning on compiler optimizations `-O3` which brings the runtime down to an average of *0.212s*.
Feel free to test this by uncommenting the corresponding line in `CMakeLists.txt`
