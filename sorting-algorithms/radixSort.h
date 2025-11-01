#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <cmath>
#include "printVec.h"

// Note: Not a template function
vector<int> radixSort(vector<int> vec, int numDigits, unsigned long& reads, unsigned long& allocations) { // Allocate 1 int
    reads = allocations = 0;
    int iteration, i, digit, bucket, item; // Allocate 5 int
    vector<vector<int>> buckets(10); // No allocation
    allocations += 6 * sizeof(int);
    for (iteration = 0; iteration < numDigits; ++iteration) {
        // Copy everything from vec into buckets
        for (i = 0; i < vec.size(); ++i) {
            digit = (vec[i] / int(pow(10, iteration)) % 10); // 1 Read
            buckets[digit].push_back(vec[i]); // Allocate 1 vector<int>?
            ++reads;
            allocations += sizeof(vector<int>);
        }
        // Copy everything from buckets back into vec
        i = 0;
        for (bucket = 0; bucket < buckets.size(); ++bucket) {
            for (item = 0; item < buckets[bucket].size(); ++item) {
                vec[i] = buckets[bucket][item];
                ++i;
            }
            buckets[bucket].clear();
        }
    }
    return vec;
}

#endif
