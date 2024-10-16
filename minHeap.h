/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: ????
Your programmer number: ????
Hours spent making and testing your min heap class: ????
An y difficulties?: ????
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


//You need to implement all the memeber functions above.  Don't forget operator<<().

//insert()
//{
//  if(/* array is full */)
//    throw Overflow(); //"The array is full"; 
//}

template <class T>
int minHeap<T>::find(const T& key) const
{
  for(int i = 0; i < num; i++) 
    if(ar[i] == key)
      return i;

  //The element doesn't exist 
  throw NotFound();// "The element doesn't exist";                                                                                             
}

//remove(int i)
//{
//  if(i is invalid)
//    throw BadIndex(); //"The element doesn't exist";                                                                       
//}

/*
getMin()
{
  if(the heap is empty)
      throw Underflow();
  //This function removes the top element and returns it.
  //You should be calling remove()
}
*/

#endif
