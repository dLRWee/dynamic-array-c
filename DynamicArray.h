#ifndef DYNAMIC_ARRAY_H 
#define DYNAMIC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

#define DARR_NOT_FOUND SIZE_MAX

typedef struct DynamicArray DynamicArray;

// --- Memory management ---

// Creates a darr with default capacity
DynamicArray* darr_create();

// Creates a darr with the specified capacity
DynamicArray* darr_create_capacity(size_t init_capacity);

// Copies the darr (deep copy)
DynamicArray* darr_copy(const DynamicArray* darr);

// Frees the darr memory
void darr_free(DynamicArray* darr);

// Ensures that the darr has enough capacity
bool darr_ensure_capacity(DynamicArray* darr, size_t min_capacity);

// --- Add ---

// Inserts a value at the specified index
bool darr_add_at(DynamicArray* darr, double value, size_t index);

// Inserts a value at the beginning
bool darr_add_first(DynamicArray* darr, double value);

// Inserts a value at the end
bool darr_add_last(DynamicArray* darr, double value);

// --- Remove ---

// Removes the value at the specified index
bool darr_remove_at(DynamicArray* darr, double* optional_dst, size_t index);

// Removes the value at the beginning
bool darr_remove_first(DynamicArray* darr, double* optional_dst);

// Removes the value at the end
bool darr_remove_last(DynamicArray* darr, double* optional_dst);

// --- State ---

// Returns the size of the darr
size_t darr_size(const DynamicArray* darr);

// Returns the capacity of the darr
size_t darr_capacity(const DynamicArray* darr);

// Checks if the darr contains the specified value
bool darr_contains(const DynamicArray* darr, double target);

// Returns the index of the specified value (DARR_NOT_FOUND if not found)
size_t darr_index_of(const DynamicArray* darr, double target);

// Returns the current memory usage of the structure
size_t darr_memory(const DynamicArray* darr);

// Checks if the darr is empty
bool darr_is_empty(const DynamicArray* darr);

// --- Get and Set ---

// Getter for the value at the specified index
bool darr_get(const DynamicArray* darr, double* dst, size_t index);

// Setter for the value at the specified index
bool darr_set(DynamicArray* darr, double value, size_t index);

// --- Print ---

// Prints the darr elements
void darr_print(const DynamicArray* darr);

// Prints the darr elements and its current state (size, capacity)
void darr_print_log(const DynamicArray* darr);

// --- Algorithms ---

// Performs a binary search for a value in the sorted darr (returns DARR_NOT_FOUND if missing)
size_t darr_binary_search(const DynamicArray* darr, double target);

// Sorts the darr using bubble sort
void darr_bubble_sort(DynamicArray* darr);

// Sorts the darr using quicksort
void darr_quick_sort(DynamicArray* darr, size_t start, size_t end);

#endif