#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "printVec.h"

template<typename Comparable>
void quickSortUnstableRec(vector<Comparable> &vec, int startIndex, int endIndex, Comparable& partition, int& i, int& largerElementIndex, Comparable& temp, unsigned long& reads, unsigned long& allocations) { // No allocations, all passed by reference
    // Recursive base case
    if (startIndex >= endIndex) {
        return;
    }

    // Choose a partition element
    partition = vec[startIndex];

    // Loop through vec from startIndex to endIndex
    // Keep track of where the > partition elements start
    largerElementIndex = startIndex+1;
    for (i = startIndex+1; i <= endIndex; ++i) {
        if (vec[i] <= partition) { // 1 Read
            // Swap the smaller/equal item to the left of the larger items
            temp = vec[i]; // 1 Read
            vec[i] = vec[largerElementIndex]; // 1 Read
            vec[largerElementIndex] = temp;
            // Update largerElementIndex
            ++largerElementIndex;
            reads += 2;
        }
        ++reads;
    }
    // Swap the partition element into place
    if (startIndex != largerElementIndex-1) {
        temp = vec[startIndex]; // 1 Read
        vec[startIndex] = vec[largerElementIndex - 1]; // 1 Read
        vec[largerElementIndex - 1] = temp;
        reads += 2;
    }

    // Recursive calls for two halves
    quickSortUnstableRec(vec, startIndex, largerElementIndex-2, partition, i, largerElementIndex, temp,reads, allocations);
    quickSortUnstableRec(vec, largerElementIndex, endIndex, partition, i, largerElementIndex, temp,reads, allocations);
}

template<typename Comparable>
vector<Comparable> quickSortUnstable(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) {
    reads = allocations = 0;
    Comparable partition, temp; // Allocate 2 Comparable
    int i, largerElementIndex; // Allocate 2 int
    allocations += 2 * sizeof(Comparable) + 2 * sizeof(int);
    quickSortUnstableRec(vec, 0, vec.size() - 1, partition, i, largerElementIndex, temp, reads, allocations);
    return vec;
}

template<typename Comparable>
void quickSortStableRec(vector<Comparable> &vec, unsigned long& reads, unsigned long& allocations, Comparable& partition, int& i) {
    // Recursive base case
    if (vec.size() <= 1) {
        return;
    }

    // Choose a partition element
    partition = vec[0];

    vector<Comparable> smaller, equal, larger; // No immediate allocations
    // Loop through vec and populate smaller, equal, larger
    for (i = 0; i < vec.size(); ++i) {
        if (vec[i] < partition) { // 1 Read
            smaller.push_back(vec[i]); // Allocate 1 Comparable
        } else if (vec[i] > partition) { // 1 Read
            larger.push_back(vec[i]); // Allocate 1 Comparable
        } else {
            equal.push_back(vec[i]); // Allocate 1 Comparable
        }
        reads += 2;
        allocations += sizeof(Comparable);
    }

    // Recursive calls
    quickSortStableRec(smaller, reads, allocations, partition, i);
    quickSortStableRec(larger, reads, allocations, partition, i);

    // Copy elements from smaller, equal, and larger back into vec
    for (i = 0; i < vec.size(); ++i) {
        if (i < smaller.size()) {
            vec[i] = smaller[i];
        } else if (i < smaller.size() + equal.size()) {
            vec[i] = equal[i - smaller.size()];
        } else {
            vec[i] = larger[i - smaller.size() - equal.size()];
        }
    }
}

template<typename Comparable>
vector<Comparable> quickSortStable(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) { // No immediate allocations
    reads = allocations = 0;
    Comparable partition; // Allocate 1 Comparable
    int i; // Allocate 1 int
    allocations += sizeof(Comparable) + sizeof(int);
    quickSortStableRec(vec, reads, allocations, partition, i);
    return vec;
}

#endif
