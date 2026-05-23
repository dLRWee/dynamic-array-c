# Dynamic Array Implementation in C

A robust, encapsulated Dynamic Array (Vector) implementation written in C11. This project features safe memory management, built-in sorting algorithms, and a custom colorized logging system. Built and tested using Visual Studio on Windows.

## 🚀 Features

* **Memory Safety:** Comprehensive bounds checking, overflow protections (`SIZE_MAX`), and safe capacity growth.
* **Algorithms:** Embedded implementation of Bubble Sort, Quick Sort, and Binary Search for `double` types.
* **Custom Logger:** Colorized console logger with file and line tracking for different log levels (`INFO`, `WARNING`, `ERROR`).
* **Stress Tests:** Includes benchmark tests evaluating array performance and sorting efficiency.

## 🛠️ Project Structure

* `DarrDouble.h` / `DarrDouble.c` — Core dynamic array implementation.
* `Logger.h` / `Logger.c` — Custom logging utility with ANSI colors.
* `test.h` / `test.c` — Stress tests and algorithm benchmarking.
* `main.c` — Project entry point.

## 💻 How to Run (Universal CMake Setup)

You can build and run this project using CMake from your terminal:

```bash
# 1. Configure the project (creates the build directory)
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 2. Build the executable
cmake --build build --config Release

# 3. Run the benchmarks
./build/Release/darr_double_project  # On Windows
./build/darr_double_project  # On Linux/macOS
```

## 📊 Benchmark Results

The benchmark suite isolates execution time to ensure precise results. The **STRESS TEST** measures the complete lifecycle of the container, tracking every single action from the initial creation of the array to its final destruction. In contrast, the sorting benchmarks (**QUICK SORT** and **BUBBLE SORT**) exclusively measure the time spent on the sorting algorithm itself. To maintain high accuracy, all logs and console output operations are strictly excluded from the measured execution time.

### 1. Container Stress Test
This benchmark evaluates the complete lifecycle of the dynamic array (`darr`), including mass allocations and memory re-indexing:
* **Dataset Size:** 200,000 elements (inserted via 100,000 `darr_add_first` and 100,000 `darr_add_last` calls).
* **Allocated Capacity:** 262,144 elements (reflecting automatic power-of-two growth).
* **Peak Memory Usage:** 2.00 MB.
* **Operations Tested:** Retrieval, element modification, mass removal (`darr_remove_last` / `darr_remove_first`), and container destruction.
* **Total Execution Time:** **~2.14 seconds** (includes all underlying memory reallocations).

### 2. Sorting Algorithm Performance
The sorting benchmarks measure the isolated processing time for `double` datasets. All logging operations are excluded from these timers.


| Algorithm | Array State | Element Count | Execution Time (seconds) |
| :--- | :--- | :--- | :--- |
| **Quick Sort** | Unsorted (Random) | 500,000 | **~0.015** |
| **Quick Sort** | Pre-sorted | 500,000 | **~0.004** |
| **Bubble Sort** | Unsorted (Random) | 50,000 | **~0.695** |
| **Bubble Sort** | Pre-sorted | 50,000 | **~0.00002** |

### 🔍 Key Insights
* **Quick Sort Efficiency:** The Quick Sort implementation processes a large array of 500,000 elements in just ~0.015 seconds. Notably, the execution time drops to ~0.004 seconds on a pre-sorted array. This demonstrates an effective pivot selection strategy that successfully avoids the worst-case $O(n^2)$ time complexity.
* **Bubble Sort Limitations:** As expected, Bubble Sort shows typical $O(n^2)$ performance on unsorted data, taking ~0.695 seconds for a dataset 10 times smaller than the one used for Quick Sort. However, it features a swap-detection optimization, allowing it to complete near-instantly (**~0.00002 seconds**) in a single $O(n)$ pass if the array is already sorted.
