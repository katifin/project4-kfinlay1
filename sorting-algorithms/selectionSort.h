#ifndef SORTING_SELECTIONSORT_H
#define SORTING_SELECTIONSORT_H

#include "printVec.h"

template<typename Comparable>
vector<Comparable> selectionSort(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) { // No allocations
    reads = allocations = 0;
    int swapIndex, i, minIndex; // Allocate 3 ints
    Comparable temp; // Allocate 1 Comparable
    allocations += 3 * sizeof(int) + sizeof(Comparable);
    for (swapIndex = 0; swapIndex < vec.size()-1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex+1; i < vec.size(); ++i) {
            if (vec[i] < vec[minIndex]) { // 2 Reads
                // We have a new minimum
                minIndex = i;
            }
            reads += 2;
        }
        // Swap min value into swapIndex spot in vector
        if (minIndex != swapIndex) {
            temp = vec[swapIndex]; // 1 Read
            vec[swapIndex] = vec[minIndex]; // 1 Read
            vec[minIndex] = temp;
            reads += 2;
        }
    }
    return vec;
}

#endif
