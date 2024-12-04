#ifndef RADIX_H
#define RADIX_H

#include <iostream>
#include <algorithm> // For max_element

using namespace std;

const int RADIX = 10; // Base 10 for decimal numbers

// Node for linked list
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Function to add an element to the end of the linked list
void append(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Function to collect elements from a linked list back into the array
void collect(Node*& head, int* arr, int& index) {
    Node* current = head;
    while (current) {
        arr[index++] = current->data;
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

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

    // Initialize buckets as linked lists
    Node* buckets[RADIX] = {nullptr};
    Node* bucketTails[RADIX] = {nullptr};

    int powerOfRadix = 1; // RADIX^digit
    for (int digit = 0; digit < maxDigits; digit++) {
        // Distribute elements into buckets
        for (int i = 0; i < size; i++) {
            int digitValue = (arr[i] / powerOfRadix) % RADIX;
            append(buckets[digitValue], bucketTails[digitValue], arr[i]);
        }

        // Collect elements from buckets back into the array
        int index = 0;
        for (int i = 0; i < RADIX; i++) {
            collect(buckets[i], arr, index);
            bucketTails[i] = nullptr; // Reset tail pointers
        }

        powerOfRadix *= RADIX; // Update power of radix for the next digit
    }
}

#endif // RADIX_H