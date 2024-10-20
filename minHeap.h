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
#include "swap.h" //for mySwap().  If you didn't create it, you can use the library's swap()

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
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c);
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int i);
  //void build_min_heap(); //no need to implement this. We won't use it for our application.
  void bubbleUp(int i);
  void insert(const T& el);
  int find(const T& key) const;
  void remove(int i);
  T getMin();

  class Underflow{};
  class Overflow{};
  class BadIndex{};
  class NotFound{};
};


/**
 * @brief Constructs a minHeap with a specified capacity.
 *
 * This constructor initializes a minHeap object with a given capacity.
 * It sets the initial number of elements in the heap to zero and allocates
 * memory for the heap array based on the specified capacity.
 *
 * @tparam T The type of elements stored in the heap.
 * @param c The maximum capacity of the heap.
 */
template <class T>
minHeap<T>::minHeap(int c)
{
  capacity = c;
  num = 0;
  ar = new T[capacity];
}

/**
 * @brief Maintains the min-heap property for the heap.
 *
 * This function ensures that the subtree rooted at index `i` satisfies the min-heap property.
 * It compares the element at index `i` with its left and right children and swaps it with the
 * smallest of the three if necessary. The function then recursively calls itself on the affected
 * subtree to ensure the entire subtree satisfies the min-heap property.
 *
 * @tparam T The type of elements stored in the heap.
 * @param i The index of the element to heapify.
 */
template <class T>
void minHeap<T>::min_heapify(int i)
{
  int left = 2*i + 1;
  int right = 2*i + 2;
  int smallest = i;

  if(left < num && ar[left] < ar[i])
    smallest = left;
  if(right < num && ar[right] < ar[smallest])
    smallest = right;

  if(smallest != i)
  {
    mySwap(ar[i], ar[smallest]);
    min_heapify(smallest);
  }
}

/**
 * @brief Ensures the min-heap property by moving an element up the heap.
 *
 * This function maintains the min-heap property by comparing the element at index `i`
 * with its parent. If the element is smaller than its parent, it swaps them and recursively
 * calls itself on the parent index. This process continues until the element is in the correct
 * position or it becomes the root of the heap.
 *
 * @tparam T The type of elements stored in the heap.
 * @param i The index of the element to bubble up.
 */
template <class T>
void minHeap<T>::bubbleUp(int i)
{
  int parent = (i-1)/2;

  if(i > 0 && ar[i] < ar[parent])
  {
    mySwap(ar[i], ar[parent]);
    bubbleUp(parent);
  }
}

/**
 * @brief Inserts an element into the min-heap.
 *
 * This function inserts a new element into the min-heap. If the heap is at full capacity,
 * it throws an `Overflow` exception. The new element is added to the end of the heap array,
 * and the `bubbleUp` function is called to maintain the min-heap property. The number of
 * elements in the heap is then incremented.
 *
 * @tparam T The type of elements stored in the heap.
 * @param el The element to be inserted into the heap.
 * @throws Overflow if the heap is at full capacity.
 */
template <class T>
void minHeap<T>::insert(const T& el)
{
  if(num == capacity)
    throw Overflow();

  ar[num] = el;
  bubbleUp(num);
  num++;
}

/**
 * @brief Finds the index of a given element in the min-heap.
 *
 * This function searches for the specified element in the heap array. It iterates through
 * the elements in the heap and returns the index of the first occurrence of the element
 * that matches the given key. If the element is not found, it throws a `NotFound` exception.
 *
 * @tparam T The type of elements stored in the heap.
 * @param key The element to be found in the heap.
 * @return int The index of the element if found.
 * @throws NotFound if the element is not found in the heap.
 */
template <class T>
int minHeap<T>::find(const T& key) const
{
  for(int i = 0; i < num; i++)
    if(ar[i] == key)
      return i;

  throw NotFound();
}

/**
 * @brief Removes an element from the min-heap.
 *
 * This function removes the element at the specified index from the heap. If the heap is empty,
 * it throws an `Underflow` exception. If the index is out of bounds, it throws a `BadIndex` exception.
 * The element at the specified index is replaced with the last element in the heap, and the `min_heapify`
 * function is called to maintain the min-heap property. The number of elements in the heap is then decremented.
 *
 * @tparam T The type of elements stored in the heap.
 * @param i The index of the element to be removed.
 * @throws Underflow if the heap is empty.
 * @throws BadIndex if the index is out of bounds.
 */
template <class T>
void minHeap<T>::remove(int i) {
  if (num <= 0) {
    throw Underflow();
  }
  if (i < 0 || i >= num) {
    throw BadIndex();
  }
  ar[i] = ar[num - 1];
  num--;
  min_heapify(i);
}

/**
 * @brief Retrieves the minimum element from the min-heap.
 * 
 * This function returns the minimum element from the min-heap. If the heap is empty, it throws an `Underflow` exception.
 * The minimum element is stored at the root of the heap, so it is removed from the heap using the `remove` function.
 * The minimum element is then returned to the caller.
 * 
 * @tparam T The type of elements stored in the heap.
 * @return T The minimum element in the heap.
 * @throws Underflow if the heap is empty.
 */
template <class T>
T minHeap<T>::getMin()
{
  if(num == 0)
    throw Underflow();

  T min = ar[0];
  remove(0);
  return min;
}

/**
 * @brief Overloads the output stream operator to print the min-heap.
 * 
 * This function overloads the output stream operator to print the elements of the min-heap.
 * It iterates through the elements in the heap and prints them to the output stream separated by spaces.
 * 
 * @tparam T The type of elements stored in the heap.
 * @param o The output stream to write the heap elements to.
 * @param h The min-heap object to be printed.
 * @return ostream& The output stream containing the printed heap elements.
 * 
 */
template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h)
{
  if (h.num == 0) {
    o << "none";
  } 
  else {
    for(int i = 0; i < h.num; i++)
      o << h.ar[i] << " ";
  }
  return o;
}

#endif