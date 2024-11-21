/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent making and testing your min heap class: ????
Any difficulties?: ????
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;
//#include "swap.h" //for mySwap().  If you didn't create it, you can use the library's swap()

extern int* locator; // Declare the global locator array

struct vertex; // Forward declaration of vertex

void mySwap(vertex& v1, vertex& v2); // Forward declaration

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar


public:
  minHeap();       // Default constructor
  minHeap(int c);  // Constructor with capacity
  ~minHeap() ;     // Destructor
  void min_heapify(int i);
  void bubbleUp(int i);
  void insert(const T& el); // Insert an element into the heap
  int find(const T& key) const; // Find the index of an element
  void remove(int i); // Remove an element at a specific index
  T getMin(); // Get and remove the minimum element
  T& getElem(int i); // Access a modifiable element by index
  const T& getElem(int i) const; // Access a const element by index
  int getCap() const; // Get the heap capacity
  int getNum() const; // Get the number of elements in the heap
  void updateElem(int i, const T& newValue); // Update an element and restore heap property
  bool isEmpty() const; // Check if the heap is empty

  class Underflow{};
  class Overflow{};
  class BadIndex{};
  class NotFound{};
};

// Constructor
template <class T>
minHeap<T>::minHeap() : ar(nullptr), capacity(0), num(0) {}

// Constructor with capacity
template <class T>
minHeap<T>::minHeap(int c) : capacity(c), num(0) {
    ar = new T[capacity];
}

// Destructor
template <class T>
minHeap<T>::~minHeap() {
    delete[] ar;
    ar = nullptr;
}


// Overload operator<< to print the heap
template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h) {
    for (int i = 0; i < h.num; i++) {
        o << h.ar[i] << " ";
    }
    return o;
}

// Bubble up to maintain min-heap property
template <class T>
void minHeap<T>::bubbleUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (ar[i] < ar[parent]) {
            mySwap(ar[i], ar[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

// Min-heapify to maintain the min-heap property
template <class T>
void minHeap<T>::min_heapify(int i) {
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child
    int smallest = i;

    if (left < num && ar[left] < ar[smallest]) {
        smallest = left;
    }
    if (right < num && ar[right] < ar[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        mySwap(ar[i], ar[smallest]);
        min_heapify(smallest);
    }
}

// Insert a new element into the heap
template <class T>
void minHeap<T>::insert(const T& el) {
    if (num >= capacity) {
        throw Overflow(); // Heap is full
    }
    ar[num] = el;
    locator[el.vertexNum] = num; // Update locator
    bubbleUp(num);
    num++;
}

// Find the index of an element
template <class T>
int minHeap<T>::find(const T& key) const {
  for(int i = 0; i < num; i++) 
    if(ar[i] == key)
      return i;

  //The element doesn't exist 
  throw NotFound();// "The element doesn't exist";                                                                                             
}

// Remove an element by index
template <class T>
void minHeap<T>::remove(int i) {
    if (i < 0 || i >= num) {
        throw BadIndex(); // Invalid index
    }
    locator[ar[i].vertexNum] = -1; // Mark removed element
    ar[i] = ar[num - 1];
    locator[ar[i].vertexNum] = i; // Update locator for the moved element
    num--;
    if (i < num) {
        min_heapify(i);
        bubbleUp(i);
    }
}

// Extract the minimum element (root) from the heap
template <class T>
T minHeap<T>::getMin() {
    if (num <= 0) {
        throw Underflow(); // Heap is empty
    }
    T minElement = ar[0];
    remove(0); // Remove the root and restore heap property
    return minElement;
}

// Access a modifiable element by index
template <class T>
T& minHeap<T>::getElem(int i) {
    if (i < 0 || i >= num) {
        throw BadIndex(); // Invalid index
    }
    return ar[i];
}

// Access a const element by index
template <class T>
const T& minHeap<T>::getElem(int i) const {
    if (i < 0 || i >= num) {
        throw BadIndex(); // Invalid index
    }
    return ar[i];
}

// Get the heap capacity
template <class T>
int minHeap<T>::getCap() const {
    return capacity;
}

// Get the number of elements in the heap
template <class T>
int minHeap<T>::getNum() const {
    return num;
}

// Update an element and restore the heap property
template <class T>
void minHeap<T>::updateElem(int i, const T& newValue) {
    if (i < 0 || i >= num) {
        throw BadIndex(); // Invalid index
    }
    if (newValue < ar[i]) {
        ar[i] = newValue;
        bubbleUp(i);
    } else if (newValue > ar[i]) {
        ar[i] = newValue;
        min_heapify(i);
    }
}

template <class T>
bool minHeap<T>::isEmpty() const {
    return num == 0;
}

#endif
