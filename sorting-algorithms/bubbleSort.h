#ifndef SORTING_BUBBLESORT_H
#define SORTING_BUBBLESORT_H

#include "printVec.h"

template<typename Comparable>
vector<Comparable> bubbleSort(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) { // No allocation
    reads = allocations = 0;
    int numPasses = 0, i; // Allocate 2 int
    Comparable temp; // Allocate 1 Comparable
    bool haveSwapped = true; // Allocate 1 bool
    allocations += sizeof(int) + sizeof(int) + sizeof(Comparable) + sizeof(bool);
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i+1 < vec.size()-numPasses; ++i) {
            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i] > vec[i+1]) { // 2 Reads
                temp = vec[i]; // Read
                vec[i] = vec[i+1]; // Read
                vec[i+1] = temp;
                reads += 2;
                // Update haveSwapped
                haveSwapped = true;
            }
            reads += 2 ;
        }
        // Update numPasses
        ++numPasses;
    }
    return vec;
}

#endif
