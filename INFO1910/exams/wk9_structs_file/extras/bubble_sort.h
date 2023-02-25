/**
 *
 * SimonC Type-Agnostic Bubble Sort Implementation
 *
 * License: CC Attribution but no Modify
 *    You may do pretty much whatever you want with this code except modify it, distribute modifications, or pass it off as your own work.
 *
 */

#ifndef BUBBLE_SORT_H
// Define a "function pointer" type matching a standard comparator function
typedef int (*comparator_function_t) (void*, void*);

// Bubble sort routine
void bubble_sort(void* elements, size_t n_elements, size_t size_element, comparator_function_t);

#define BUBBLE_SORT_H
#endif
