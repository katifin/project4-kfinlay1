#ifndef SORTING_INSERTIONSORT_H
#define SORTING_INSERTIONSORT_H

#include "printVec.h"

template<typename Comparable>
vector<Comparable> insertionSort(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) { // No allocation
    reads = allocations = 0;
    int unsortedStartIndex, insertIndex; // Allocate 2 ints
    Comparable toBeInserted; // Allocate Comparable
    allocations += sizeof(int) + sizeof(int) + sizeof(Comparable);
    for (unsortedStartIndex = 1; unsortedStartIndex < vec.size(); ++unsortedStartIndex) {
        toBeInserted = vec[unsortedStartIndex]; // Read
        ++reads;
        // Loop to shift over the larger elements
        insertIndex = unsortedStartIndex - 1;
        while (insertIndex >= 0 && vec[insertIndex] > toBeInserted) { // (1+n) Reads (will always read at least once)
            vec[insertIndex + 1] = vec[insertIndex]; // Read
            reads += 2;
            --insertIndex;
        }
        ++reads;
        // Put toBeInserted back into vec
        vec[insertIndex + 1] = toBeInserted;
    }
    return vec;
}

#endif
