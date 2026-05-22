#include "Logger.h"
#include "Test.h"

int main()
{
	run_test("STRESS TEST", test_stress);
	run_test("QUICK SORT", test_quick_sort);
	run_test("QUICK SORT ON SORTED", test_quick_sort_on_sorted);
	run_test("BUBBLE SORT", test_bubble_sort);
	run_test("BUBBLE SORT ON SORTED", test_bubble_sort_on_sorted);
}