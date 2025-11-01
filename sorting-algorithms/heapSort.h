#ifndef SORTING_HEAPSORT_H
#define SORTING_HEAPSORT_H

#include "printVec.h"
#include <vector>
using std::vector;

// Helper function for heapSort
inline int leftChild(const int& i) {
    return 2 * i + 1;
}

// Helper function for heapSort
// i is the index of the value being percolated down
// n is the number of items in the heap
template <typename Comparable>
void percolateDown(vector<Comparable> &items, int& i, unsigned long& n, int& child, Comparable& tmp, unsigned long& reads) { // No allocation; all passed by reference
    for(tmp = items[i]; leftChild(i) < n; i = child) {
        child = leftChild(i);
        // choose the child with the larger value
        if (child != n - 1) {
            if (items[child] < items[child + 1]) { // 2 Reads
                ++child;
                reads += 2;
            }
        }
        // if the parent is less than the child, swap them
        if (tmp < items[child]) { // Read
            items[i] = items[child]; // Read
            ++reads;
        } else {
            // parent is >= both children. nothing more to do.
            break;
        }
        ++reads;
    }
    items[i] = tmp;
}

template <typename Comparable>
vector<Comparable> heapSort(vector<Comparable> items, unsigned long& reads, unsigned long& allocations) { // No allocation
    reads = allocations = 0;
    int i, child; // Allocate 2 int
    Comparable temp, tmp; // Allocate 2 Comparable
    unsigned long j, n; // Allocate 2 unsigned long
    allocations += sizeof(int) + sizeof(int) + sizeof(Comparable) + sizeof(unsigned long) + sizeof(unsigned long);
    // build the heap (with max value at root)
    for (i = items.size() / 2 - 1; i >= 0; --i) {
        n = items.size();
        percolateDown(items, i, n, child, tmp, reads);
    }

    // keep deleting the max
    for (j = items.size() - 1; j > 0; --j) {
        // swap the maximum out
        temp = items[0]; // Read
        items[0] = items[j]; // Read
        items[j] = temp; // Read
        reads += 3;

        // make it into a heap again
        i = 0;
        percolateDown(items, i, j, child, tmp, reads);
    }
    return items;
}

#endif
