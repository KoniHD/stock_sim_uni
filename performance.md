# Performance

## Evaluate Performance

In order to profil the performance of the program a seperate executable is create: `tests/profiling.cpp`. The purpose of this seperate file is to stress-test all classes whithout requiring user input like the `src/client.cpp` file does, since that conflicts with profiling.
Using CMake to create the executable it can be run from the build folder:
```bash
gprof ./profiling
```
If you want to examine the output we recommend piping the profiling into a .txt: `gprof ./profiling > ../output/profiling.txt`. \
Additionally we also used the command `time ./profiling` to measure the execution time.

## Performance Improvements

From these two measurements we mainly derived two key bottlenecks:

### 1 Simulating and saving all results in one.

The program up until sprint2 had a function to simulate the market which called each stock to simulate its next timestep and saving it. After finishing simulation this stock history would be accessed and written so a .csv file. However the stock history has mathematically no relevance to future prices. Hence to improve runtime we decided to simulate the next step for a stock and imediately write its  new price to the .csv output. This saves the memory necessary for storing the stock history as well as iterating over this history in the end again.


### Note

We assume that a lot of function calls marked in the profiling might also be due to our use of an external library `json.hpp`. We didn't modify these parts since we assumed them to already be highly optimized and .json parsing is not in the scope of this project.
