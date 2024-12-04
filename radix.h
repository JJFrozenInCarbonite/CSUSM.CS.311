#ifndef RADIX_H
#define RADIX_H

#include <iostream>
#include <algorithm> // For max_element

using namespace std;

const int RADIX = 10; // Base 10 for decimal numbers

// Function to perform radix sort
void radixSort(int* arr, int size) {
    if (size <= 0) return;

    // Find the maximum number to determine the number of digits
    int maxNum = *max_element(arr, arr + size);
    int maxDigits = 0;
    while (maxNum > 0) {
        maxDigits++;
        maxNum /= RADIX;
    }

    // Initialize buckets
    int buckets[RADIX][size]; // Static 2D array for buckets
    int bucketCounts[RADIX] = {0}; // To track the number of elements in each bucket

    // Perform radix sort
    int powerOfRadix = 1; // RADIX^digit
    for (int digit = 0; digit < maxDigits; digit++) {
        // Reset bucket counts
        fill(bucketCounts, bucketCounts + RADIX, 0);

        // Distribute elements into buckets
        for (int i = 0; i < size; i++) {
            int digitValue = (arr[i] / powerOfRadix) % RADIX;
            buckets[digitValue][bucketCounts[digitValue]++] = arr[i];
        }

        // Collect elements from buckets back into the array
        int index = 0;
        for (int i = 0; i < RADIX; i++) {
            for (int j = 0; j < bucketCounts[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }

        // Update power of radix for the next digit
        powerOfRadix *= RADIX;
    }
}

#endif // RADIX_H