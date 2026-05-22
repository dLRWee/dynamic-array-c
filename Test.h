#ifndef TEST_H
#define TEST_H

#include <time.h>

typedef double (*TestFunction)();

// Prints the name of the test, its time, and runs it.
void run_test(const char* test_name, TestFunction test);

// --- Stress ---

double test_stress();

// --- Sorting ---

double test_quick_sort();
double test_quick_sort_on_sorted();
double test_bubble_sort();
double test_bubble_sort_on_sorted();

#endif