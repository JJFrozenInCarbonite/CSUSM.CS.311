#ifndef RADIX_H
#define RADIX_H

#include <iostream>
#include <cmath> // For pow

using namespace std;

const int RADIX = 10; // Base 10 for decimal numbers

class Node {
  friend class LL;
private:
  int el;
  Node* next;
public:
  Node(int s) { el = s; next = NULL; }
  int getElem() const { return el; }
};

class LL {
private:
  Node* front;
  Node* rear;
  int num;
public:
  LL() { front = rear = NULL; num = 0; }
  ~LL();
  bool empty() const { return (front == NULL && rear == NULL && num == 0); }
  void addRear(int s);
  void addRear(Node* p);
  void append(const LL& other);
  Node* pop();
  void clear();
  Node* begin() const { return front; }
  Node* goToNext(Node* curr) const { return curr->next; }
  int size() const { return num; }

  class Underflow {}; // empty exception class
};

// Destructor implementation
LL::~LL() {
  while (!empty()) {
    delete pop();
  }
}

// Add an element to the rear of the list
void LL::addRear(int s) {
  Node* newNode = new Node(s);
  if (empty()) {
    front = rear = newNode;
  } else {
    rear->next = newNode;
    rear = newNode;
  }
  num++;
}

// Add a node to the rear of the list
void LL::addRear(Node* p) {
  if (empty()) {
    front = rear = p;
  } else {
    rear->next = p;
    rear = p;
  }
  num++;
}

// Append another list to this list
void LL::append(const LL& other) {
  Node* curr = other.front;
  while (curr != NULL) {
    addRear(curr->el);
    curr = curr->next;
  }
}

// Pop an element from the front of the list
Node* LL::pop() {
  if (empty()) {
    throw Underflow();
  }
  Node* temp = front;
  front = front->next;
  if (front == NULL) {
    rear = NULL;
  }
  num--;
  return temp;
}

// Clear the list
void LL::clear() {
  while (!empty()) {
    delete pop();
  }
}

// Radix sort implementation for integers
void radixSort(LL& list) {
  if (list.empty()) return;

  // Find the maximum number to determine the number of digits
  int maxNum = 0;
  Node* curr = list.begin();
  while (curr != NULL) {
    if (curr->getElem() > maxNum) {
      maxNum = curr->getElem();
    }
    curr = list.goToNext(curr);
  }

  int maxDigits = 0;
  while (maxNum > 0) {
    maxDigits++;
    maxNum /= RADIX;
  }

  // Perform radix sort
  for (int digit = 0; digit < maxDigits; digit++) {
    LL buckets[RADIX];

    // Distribute elements into buckets
    curr = list.begin();
    while (curr != NULL) {
      int digitValue = (curr->getElem() / static_cast<int>(pow(RADIX, digit))) % RADIX;
      buckets[digitValue].addRear(curr->getElem());
      curr = list.goToNext(curr);
    }

    // Collect elements from buckets
    list.clear();
    for (int i = 0; i < RADIX; i++) {
      list.append(buckets[i]);
    }
  }
}

#endif // RADIX_H