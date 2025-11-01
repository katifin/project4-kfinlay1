#ifndef MERGESORT_H
#define MERGESORT_H

#include "printVec.h"

template<typename Comparable>
void mergeSortRec(vector<Comparable> &vec, int startIndex, int endIndex, vector<Comparable>& temp, int& i, int& leftIndex, int& rightIndex, unsigned long& reads, unsigned long& allocations) { // Allocate 2 int
    allocations += 2 * sizeof(int);
    // Recursive base case
    if (startIndex >= endIndex) {
        return;
    }

    // Recursive calls for the left and right halves
    int centerIndex = (startIndex + endIndex) / 2; // Allocate 1 int
    allocations += sizeof(int);
    mergeSortRec(vec, startIndex, centerIndex,temp, i, leftIndex, rightIndex, reads, allocations);
    mergeSortRec(vec, centerIndex + 1, endIndex,temp, i, leftIndex, rightIndex, reads, allocations);

    // Merge
    i = 0;
    leftIndex = startIndex;
    rightIndex = centerIndex + 1;
    // While leftIndex and rightIndex are in bounds of their half
    while (leftIndex <= centerIndex && rightIndex <= endIndex) {
        if (vec[leftIndex] <= vec[rightIndex]) { // 2 Reads
            temp[i] = vec[leftIndex]; // Read, allocate 1 Comparable
            ++leftIndex;
            ++reads;
            allocations += sizeof(Comparable);
        } else {
            temp[i] = vec[rightIndex]; // Read, allocate 1 Comparable
            ++rightIndex;
            ++reads;
            allocations += sizeof(Comparable);
        }
        ++i;
        reads += 2;
    }
    // Now one of the halves is empty and the other half has at least one element left to copy into temp
    while (leftIndex <= centerIndex) {
        temp[i] = vec[leftIndex]; // read, allocate 1 Comparable
        ++leftIndex;
        ++i;
        ++reads;
        allocations += sizeof(Comparable);
    }
    while (rightIndex <= endIndex) {
        temp[i] = vec[rightIndex]; // read, allocate 1 Comparable
        ++rightIndex;
        ++i;
        ++reads;
        allocations += sizeof(Comparable);
    }
    // Now everything between startIndex and endIndex is copied into temp
    // Copy everything from temp back into vec
    for (i = 0; i <= endIndex-startIndex; ++i) {
        vec[i + startIndex] = temp[i];
    }
}

template<typename Comparable>
vector<Comparable> mergeSort(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) { // No allocation
    reads = allocations = 0;
    vector<Comparable> temp(vec.size()); // No allocation
    int i, leftIndex, rightIndex; // Allocate 3 ints
    allocations += 3 * sizeof(int);
    mergeSortRec(vec, 0, vec.size() - 1, temp, i, leftIndex, rightIndex, reads, allocations);
    return vec;
}

#endif
