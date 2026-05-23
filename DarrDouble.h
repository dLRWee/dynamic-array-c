#ifndef DARR_DOUBLE_H 
#define DARR_DOUBLE_H

#include <stdbool.h>
#include <stddef.h>

#define DARR_NOT_FOUND SIZE_MAX

typedef struct DarrDouble
{
	double* data;
	size_t size;
	size_t capacity;
}
DarrDouble;

// --- Memory management ---

// Creates a darr with default capacity
DarrDouble* darr_create();

// Creates a darr with the specified capacity
DarrDouble* darr_create_capacity(size_t init_capacity);

// Copies the darr (deep copy)
bool darr_copy(const DarrDouble* src, DarrDouble* dst);

// Destroys the darr
void darr_destroy(DarrDouble* darr);

// Frees the darr memory
void darr_free(DarrDouble* darr);

// Ensures that the darr has enough capacity
bool darr_ensure_capacity(DarrDouble* darr, size_t min_capacity);

// --- Add ---

// Inserts a value at the specified index
bool darr_add_at(DarrDouble* darr, double value, size_t index);

// Inserts a value at the beginning
bool darr_add_first(DarrDouble* darr, double value);

// Inserts a value at the end
bool darr_add_last(DarrDouble* darr, double value);

// --- Remove ---

// Removes the value at the specified index
bool darr_remove_at(DarrDouble* darr, double* optional_dst, size_t index);

// Removes the value at the beginning
bool darr_remove_first(DarrDouble* darr, double* optional_dst);

// Removes the value at the end
bool darr_remove_last(DarrDouble* darr, double* optional_dst);

// --- State ---

// Returns the size of the darr
static inline size_t darr_size(const DarrDouble* darr) { return darr ? darr->size : 0; }

// Returns the capacity of the darr
static inline size_t darr_capacity(const DarrDouble* darr) { return darr ? darr->capacity : 0; }

// Checks if the darr is empty
static inline bool darr_is_empty(const DarrDouble* darr) { return darr ? darr->size == 0 : true; }

// Checks if the darr contains the specified value
bool darr_contains(const DarrDouble* darr, double target);

// Returns the index of the specified value (DARR_NOT_FOUND if not found)
size_t darr_index_of(const DarrDouble* darr, double target);

// Returns the current memory usage of the structure
size_t darr_memory(const DarrDouble* darr);

// --- Get and Set ---

// Getter for the value at the specified index
bool darr_get(const DarrDouble* darr, double* dst, size_t index);

// Setter for the value at the specified index
bool darr_set(DarrDouble* darr, double value, size_t index);

// --- Algorithms ---

// Performs a binary search for a value in the sorted darr (returns DARR_NOT_FOUND if missing)
size_t darr_binary_search(const DarrDouble* darr, double target);

// Sorts the darr using bubble sort
void darr_bubble_sort(DarrDouble* darr);

// Sorts the darr using quicksort
void darr_quick_sort(DarrDouble* darr, size_t start, size_t end);

#endif