#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "DarrDouble.h"
#include "Logger.h"
#include "Test.h"

#define STRESS_DARR_SIZE         200000ULL
#define QUICK_SORT_DARR_SIZE	 500000ULL
#define BUBBLE_SORT_DARR_SIZE     50000ULL

#define RECORD_TIME(ts) \
    do { \
        if (timespec_get(&(ts), TIME_UTC) == 0) { \
            LOG_ERROR("Failed to get " #ts " time"); \
        } \
    } while (0)

static double get_elapsed_time(struct timespec start, struct timespec end)
{
	return (double)(end.tv_sec - start.tv_sec) +
		(double)(end.tv_nsec - start.tv_nsec) / 1e9;
}

static bool fill(DarrDouble* darr, size_t size, bool sorted)
{
	if (darr == NULL)
		return false;

	LOG_INFO("Filling the darr");
	for (size_t i = 1; i <= size; i++)
	{
		double value = (double)i;
		if (!sorted && (i % 2 != 0))
			value = -value;

		if (!darr_add_last(darr, value))
		{
			LOG_ERROR("Couldn't add an element");
			return false;
		}
	}

	return true;
}

static double run_quick_sort_scenario(size_t size, bool sorted)
{
	struct timespec start, end;
	DarrDouble darr = { 0 };
	if (!fill(&darr, size, sorted))
	{
		LOG_ERROR("Couldn't fill the darr");
		darr_destroy(&darr);
		return 0.0;
	}

	LOG_INFO("Start sorting");
	const size_t current_size = darr_size(&darr);

	RECORD_TIME(start);
	if (current_size > 0)
	{
		darr_quick_sort(&darr, 0, current_size - 1);
	}
	RECORD_TIME(end);

	LOG_INFO("Free the darr");
	darr_destroy(&darr);

	return get_elapsed_time(start, end);
}

static double run_bubble_sort_scenario(size_t size, bool sorted)
{
	struct timespec start, end;
	DarrDouble darr = { 0 };
	if (!fill(&darr, size, sorted))
	{
		LOG_ERROR("Couldn't fill the darr");
		darr_destroy(&darr);
		return 0.0;
	}

	LOG_INFO("Start sorting");
	RECORD_TIME(start);
	darr_bubble_sort(&darr);
	RECORD_TIME(end);

	LOG_INFO("Free the darr");
	darr_destroy(&darr);

	return get_elapsed_time(start, end);
}

void run_test(const char* test_name, TestFunction test)
{
	printf("--- %s ---\n", test_name);
	double time_in_seconds = test();
	printf("--- Ended in %.6f seconds ---\n\n", time_in_seconds);
}

double test_stress()
{
	struct timespec start, end;
	double pure_time = 0.0;

	LOG_INFO("Testing size: %llu", STRESS_DARR_SIZE);
	const size_t last_half = STRESS_DARR_SIZE - STRESS_DARR_SIZE / 2;

	LOG_INFO("Creating a darr with capacity of 0");
	RECORD_TIME(start);

	DarrDouble darr = { 0 };

	RECORD_TIME(end);
	pure_time += get_elapsed_time(start, end);

	LOG_INFO("Filling the darr via darr_add_first with %llu elements", STRESS_DARR_SIZE / 2);
	RECORD_TIME(start);
	for (size_t i = 0; i < STRESS_DARR_SIZE / 2; i++)
	{
		if (!darr_add_first(&darr, (double)i)) 
		{
			LOG_ERROR("Couldn't add an element");
			darr_destroy(&darr);
			return 0.0;
		}
	}
	RECORD_TIME(end);
	pure_time += get_elapsed_time(start, end);

	LOG_INFO("Filling the darr via darr_add_last with %llu elements", last_half);
	RECORD_TIME(start);
	for (size_t i = 0; i < last_half; i++)
	{
		if (!darr_add_last(&darr, (double)i)) 
		{
			LOG_ERROR("Couldn't add an element");
			darr_destroy(&darr);
			return 0.0;
		}
	}
	RECORD_TIME(end);
	pure_time += get_elapsed_time(start, end);

	LOG_INFO("Current size: %zu", darr_size(&darr));
	LOG_INFO("Current capacity: %zu", darr_capacity(&darr));
	LOG_INFO("Current memory usage: %.2f MB", darr_memory(&darr) / 1024.0 / 1024.0);

	LOG_INFO("Getting first %llu elements", STRESS_DARR_SIZE / 2);
	RECORD_TIME(start);
	for (size_t i = 0; i < STRESS_DARR_SIZE / 2; i++)
	{
		double ignored;
		if (!darr_get(&darr, &ignored, i)) 
		{
			LOG_ERROR("Couldn't get an element");
			darr_destroy(&darr);
			return 0.0;
		}
	}
	RECORD_TIME(end);
	pure_time += get_elapsed_time(start, end);

	LOG_INFO("Setting last %llu elements", last_half);
	RECORD_TIME(start);
	for (size_t i = STRESS_DARR_SIZE / 2; i < STRESS_DARR_SIZE; i++)
	{
		if (!darr_set(&darr, 1.0, i)) 
		{
			LOG_ERROR("Couldn't set an element");
			darr_destroy(&darr);
			return 0.0;
		}
	}
	RECORD_TIME(end);
	pure_time += get_elapsed_time(start, end);

	LOG_INFO("Removing %llu elements via darr_remove_last and darr_remove_first", last_half);
	RECORD_TIME(start);
	for (size_t i = 0; i < last_half / 2; i++)
	{
		if (!darr_remove_last(&darr, NULL) || !darr_remove_first(&darr, NULL)) 
		{
			LOG_ERROR("Couldn't remove an element");
			darr_destroy(&darr);
			return 0.0;
		}
	}
	RECORD_TIME(end);
	pure_time += get_elapsed_time(start, end);

	LOG_INFO("Free the darr");
	RECORD_TIME(start);
	darr_destroy(&darr);
	RECORD_TIME(end);
	pure_time += get_elapsed_time(start, end);

	return pure_time;
}

double test_quick_sort()		    { return run_quick_sort_scenario(QUICK_SORT_DARR_SIZE, false); }
double test_quick_sort_on_sorted()  { return run_quick_sort_scenario(QUICK_SORT_DARR_SIZE, true); }
double test_bubble_sort()			{ return run_bubble_sort_scenario(BUBBLE_SORT_DARR_SIZE, false); }
double test_bubble_sort_on_sorted() { return run_bubble_sort_scenario(BUBBLE_SORT_DARR_SIZE, true); }