#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DarrDouble.h"

#define DARR_DEFAULT_CAPACITY 10
#define DARR_GROW_FACTOR 2

DarrDouble* darr_create()
{
	return darr_create_capacity(DARR_DEFAULT_CAPACITY);
}

DarrDouble* darr_create_capacity(size_t init_capacity)
{
	DarrDouble* darr = malloc(sizeof(DarrDouble));
	if (darr == NULL)
		return NULL;

	double* data = malloc(sizeof(double) * init_capacity);
	if (data == NULL)
	{
		free(darr);
		return NULL;
	}

	darr->data = data;
	darr->size = 0;
	darr->capacity = init_capacity;

	return darr;
}

bool darr_copy(const DarrDouble* src, DarrDouble* dst)
{
	if (src == NULL || dst == NULL)
		return false;

	double* data_copy = malloc(sizeof(double) * src->capacity);
	if (data_copy == NULL)
		return false;

	memcpy(data_copy, src->data, sizeof(double) * src->size);
	free(dst->data);

	dst->data = data_copy;
	dst->size = src->size;
	dst->capacity = src->capacity;

	return true;
}

void darr_destroy(DarrDouble* darr)
{
	if (darr == NULL) 
		return;

	free(darr->data);
	darr->data = NULL;
	darr->size = 0;
	darr->capacity = 0;
}

void darr_free(DarrDouble* darr)
{
	if (darr == NULL)
		return;

	darr_destroy(darr);
	free(darr);
}

bool darr_ensure_capacity(DarrDouble* darr, size_t min_capacity)
{
	if (darr == NULL || DARR_GROW_FACTOR <= 1)
		return false;

	if (darr->data != NULL && darr->capacity >= min_capacity)
		return true;

	size_t new_capacity = darr->capacity == 0 ? 1 : darr->capacity;
	while (new_capacity < min_capacity)
	{
		new_capacity *= DARR_GROW_FACTOR;
	}

	if (new_capacity > SIZE_MAX / sizeof(double))
		return false;

	double* new_data = realloc(darr->data, sizeof(double) * new_capacity);
	if (new_data == NULL)
		return false;

	darr->capacity = new_capacity;
	darr->data = new_data;

	return true;
}

bool darr_add_at(DarrDouble* darr, double value, size_t index)
{
	if (darr == NULL || index > darr->size)
		return false;

	if (darr->size >= darr->capacity)
	{
		size_t required_capacity = darr->capacity == 0 ? 1 : darr->capacity + 1;
		if (!darr_ensure_capacity(darr, required_capacity))
			return false;
	}

	memmove(&darr->data[index + 1], &darr->data[index], (darr->size - index) * sizeof(double));

	darr->data[index] = value;
	darr->size++;

	return true;
}

bool darr_add_first(DarrDouble* darr, double value)
{
	return darr_add_at(darr, value, 0);
}

bool darr_add_last(DarrDouble* darr, double value)
{
	return darr_add_at(darr, value, darr->size);
}

bool darr_remove_at(DarrDouble* darr, double* optional_dst, size_t index)
{
	if (darr == NULL || darr->data == NULL || index >= darr->size)
		return false;

	if (optional_dst != NULL)
		*optional_dst = darr->data[index];

	memmove(&darr->data[index], &darr->data[index + 1], (darr->size - index - 1) * sizeof(double));
	darr->size--;
	return true;
}

bool darr_remove_first(DarrDouble* darr, double* optional_dst)
{
	return darr_remove_at(darr, optional_dst, 0);
}

bool darr_remove_last(DarrDouble* darr, double* optional_dst)
{
	return darr_remove_at(darr, optional_dst, darr->size - 1);
}

bool darr_contains(const DarrDouble* darr, double target)
{
	if (darr == NULL || darr->data == NULL || darr->size == 0)
		return false;

	for (size_t i = 0; i < darr->size; i++)
	{
		if (fabs(darr->data[i] - target) < 1e-9)
			return true;
	}

	return false;
}

size_t darr_index_of(const DarrDouble* darr, double target)
{
	if (darr == NULL || darr->data == NULL || darr->size == 0)
		return DARR_NOT_FOUND;

	for (size_t i = 0; i < darr->size; i++)
	{
		if (fabs(darr->data[i] - target) < 1e-9)
			return i;
	}

	return DARR_NOT_FOUND;
}

size_t darr_memory(const DarrDouble* darr)
{
	if (darr == NULL) 
		return 0;

	size_t structure_size = sizeof(DarrDouble);
	size_t buffer_size = sizeof(double) * darr->capacity;

	return structure_size + buffer_size;
}

bool darr_get(const DarrDouble* darr, double* dst, size_t index)
{
	if (darr == NULL || darr->data == NULL || index >= darr->size)
		return false;

	*dst = darr->data[index];
	return true;
}

bool darr_set(DarrDouble* darr, double value, size_t index)
{
	if (darr == NULL || darr->data == NULL || index >= darr->size)
		return false;

	darr->data[index] = value;
	return true;
}

size_t darr_binary_search(const DarrDouble* darr, double target)
{
	if (darr == NULL || darr->data == NULL || darr->size == 0)
		return DARR_NOT_FOUND;

	size_t left = 0;
	size_t right = darr->size - 1;
	size_t middle;

	while (left <= right)
	{
		middle = left + (right - left) / 2;

		if (fabs(darr->data[middle] - target) < 1e-9)
			return middle;
		if (darr->data[middle] > target)
		{
			if (middle == 0) 
				break;
			right = middle - 1;
		}
		else
			left = middle + 1;
	}

	return DARR_NOT_FOUND;
}

void darr_bubble_sort(DarrDouble* darr)
{
	if (darr == NULL || darr->data == NULL || darr->size == 0)
		return;

	for (size_t i = 0; i < darr->size - 1; i++)
	{
		bool swaped = false;

		for (size_t j = 0; j < darr->size - i - 1; j++)
		{
			if (darr->data[j] > darr->data[j + 1])
			{
				double temp = darr->data[j];
				darr->data[j] = darr->data[j + 1];
				darr->data[j + 1] = temp;

				swaped = true;
			}
		}

		if (!swaped)
			return;
	}
}

void darr_quick_sort(DarrDouble* darr, size_t start, size_t end)
{
	if (darr == NULL || darr->data == NULL || darr->size == 0 || start >= end)
		return;

	double pivot = darr->data[start + (end - start) / 2];

	size_t i = start;
	size_t j = end;

	while (i <= j)
	{
		while (darr->data[i] < pivot)
			i++;

		while (darr->data[j] > pivot)
			if (j == 0) 
				break; 
			else 
				j--;

		if (i <= j)
		{
			if (i != j)
			{
				double temp = darr->data[i];
				darr->data[i] = darr->data[j];
				darr->data[j] = temp;
			}
			i++;
			if (j == 0) 
				break; 
			else j--;
		}
	}

	if (start < j)
		darr_quick_sort(darr, start, j);
	if (i < end)
		darr_quick_sort(darr, i, end);
}