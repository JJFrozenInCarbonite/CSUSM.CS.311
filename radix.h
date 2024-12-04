#ifndef RADIX_H
#define RADIX_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const int LEN = 3; // the length of words
const int ALPHABET = 26; // total number of letters

class Node {
  friend class LL;
private:
  string el;
  Node* next;
public:
  Node(const string& s) { el = s; next = NULL; }
  string getElem() const { return el; }
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
  void addRear(const string& s);
  void addRear(Node* p);
  void append(const LL& other);
  Node* pop();
  void clear() { front = rear = NULL; num = 0; }
  Node* begin() const { return front; }
  Node* goToNext(Node* curr) const { return curr->next; }
  int size() const { return num; }

  class Underflow {}; // empty exception class

};

LL::~LL() {
  Node* p = front;
  while (!empty()) {
    front = front->next;
    delete p;
    p = front;
    if (front == NULL) rear = NULL;
    num--;
  }
}

void LL::addRear(const string& s) {
  Node* p = new Node(s);
  if (empty())
    front = rear = p;
  else {
    rear->next = p;
    rear = rear->next;
  }
  num++;
}

void LL::addRear(Node* p) {
  if (empty()) {
    front = rear = p;
  } else {
    rear->next = p;
    rear = p;
  }
  num++;
  rear->next = NULL;
}

void LL::append(const LL& other) {
  if (other.empty()) {
    return;
  }
  if (empty()) {
    front = other.front;
    rear = other.rear;
  } else {
    rear->next = other.front;
    rear = other.rear;
  }
  num += other.num;
}

Node* LL::pop() {
  if (empty()) {
    throw Underflow();
  }
  Node* temp = front;
  front = front->next;
  num--;
  if (front == NULL) {
    rear = NULL;
  }
  return temp;
}

void radixSort(LL& all) {
  LL buckets[ALPHABET];
  for (int pos = LEN - 1; pos >= 0; --pos) {
    while (!all.empty()) {
      Node* node = all.pop();
      char ch = node->getElem()[pos];
      int bucketIndex = ch - 'a';
      buckets[bucketIndex].addRear(node);
    }
    combineLists(all, buckets);
  }
}

void combineLists(LL& all, LL buckets[]) {
  for (int i = 0; i < ALPHABET; ++i) {
    all.append(buckets[i]);
    buckets[i].clear();
  }
}

void makeLL(LL& all, const string arr[], int size) {
  for (int i = 0; i < size; ++i) {
    all.addRear(arr[i]);
  }
}

void checkBuckets(const LL buckets[], int n) {
  for (int i = 0; i < n; i++) {
    cout << i << ": ";
    printLL(buckets[i]);
    cout << endl;
  }
}

void printLL(const LL& l) {
  for (Node* p = l.begin(); p != NULL; p = l.goToNext(p)) {
    cout << p->getElem() << ' ';
  }
}

#endif
