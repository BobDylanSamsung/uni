/**
 *
 * SimonC Type-Agnostic Bubble Sort Implementation
 *
 * License: CC Attribution but no Modify
 *    You may do pretty much whatever you want with this code except modify it, distribute modifications, or pass it off as your own work.
 *
 */

#include <string.h>   // Provides memcpy(...)
#include <stdlib.h>   // Need this for magic memory things
#include <stdbool.h>  // I actually hate this library, but it defines bool, true, false, so I'll use it here for readability
#include "bubble_sort.h"

void bubble_sort(void* elements, size_t n_elements, size_t size_element, comparator_function_t cmp) {
    // Flag - is the array sorted yet?
    bool is_sorted = false;
    while (!is_sorted) {
        // Assume sorted at start of iteration
        is_sorted = true;
        for (size_t i = 0; i < n_elements - 1; i++) {
            // If elements[i], elements[i+1] in wrong order
            if (cmp(
                        elements + i * size_element,
                        elements + (i+1) * size_element
                    ) > 0) {

                // Magically create memory for temporary variable whilst swapping element
                void* tmp = malloc(size_element);
                if (!tmp) exit(66);

                // Swap elements at elements[i] and elements[i+1]
                // Elements of size size_element, so need to use memcpy(...)
                memcpy(tmp, elements + i * size_element, size_element);
                memcpy(elements + i * size_element,
                        elements + (i+1) * size_element, size_element);
                memcpy(elements + (i+1) * size_element, tmp, size_element);

                // Had to swap items, so array wasn't sorted
                is_sorted = false;

                // Necessary evil relating to former magical memory creation thing
                free(tmp);
            }
        }
    }
}
