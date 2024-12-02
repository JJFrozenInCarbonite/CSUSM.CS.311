#ifndef HEAP_SORT2_H
#define HEAP_SORT2_H


//called from max_heapify and heapSort
void exchange(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

//turns a heap rooted at i into a max-heap, assuming the left and right subtrees are already max-heaps.
//n is the number of elements in the heap
void max_heapify(int ar[], int n, int i)
{
  
  int l = 2 * i + 1; // the index of the left child of i
  int r = 2 * i + 2; // the index of the right child of i
  int largest = i;   // the index of the largest value among the values at i, l and r
  
  // Check if left child exists and is greater than root
  if (l < n && ar[l] > ar[largest])
    largest = l;

  // Check if right child exists and is greater than largest so far
  if (r < n && ar[r] > ar[largest])
    largest = r;

  // If largest is not root
  if(largest != i)
  {
      //exchange the 2 values
      exchange(ar[i], ar[largest]);
    
      // Recursively heapify the affected sub-tree
      max_heapify(ar, n, largest);
  }
}

//turns the entire array/tree into a max heap rooted at 0
//n is the number of elements we have in the array
void build_max_heap(int ar[], int n)
{
  // Start from the last non-leaf node and go up to the root node
  for (int i = n / 2 - 1; i >= 0; i--)
  {
    max_heapify(ar, n, i);
  }
}

//a is an unordered list to start with
//use max_heapify to sort a
//n is the number of elements in the array
void heapSort(int a[], int n)
{
  // Build max heap from an unordered list
  build_max_heap(a, n);

  int size = n; // size of the unsorted portion of the array

  // Repeat until heap has only 1 element
  while (size > 1)
  {
    // Swap max element with last element - max element is now the last element
    exchange(a[0], a[size - 1]);

    // Discard the last element from the heap
    size--;

    // Root may violate max-heap property, but children are max heaps. Run max_heapify to fix it.
    max_heapify(a, size, 0);
  }
}

//this function corrects a violiation at i by bubbling it up to the correct place                             
//a is a heap                                                                                                
void bubbleUp(int a[], int i)
{
  // Get the index of the parent
  int parent = (i - 1) / 2;

  // While the current node is not the root and the current node is greater than its parent
  while (i > 0 && a[i] > a[parent])
  {
    // Swap the current node with its parent
    exchange(a[i], a[parent]);

    // Move up to the parent
    i = parent;
    parent = (i - 1) / 2;
  }
}

//a is a max heap                                                                                            
//cap is the capacity of the heap                                                                            
//n is the number of elements the heap currently has before insertion                                        
//el is the new element to be inserted                                                                       
void insert(int a[], int cap, int& n, int el)
{
  // Check if the heap is full
  if (n >= cap)
  {
    throw "The array is full";
  }

  // Insert the new element at the end of the heap
  a[n] = el;

  // Increment the size of the heap
  n++;

  // Bubble up the new element to maintain the heap property
  bubbleUp(a, n - 1);
}

//This function returns the index where key was found or throws an exception if key is not found.                                   
//a is a max heap.                                                                                 
//n is the number of elements in the heap.                                                                                
//key is the element we are looking for.                                                                                             
int find(const int a[], int n, int key)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)                                                                                            
    if(a[i] == key)
      return i;

  throw "The element doesn't exist";
}

//a is a max heap                                                                                            
//n is the number of elements the heap currently has before deletion, then decrememted after deletion                                         
//i is the index of the element to be removed.                                             
void remove(int a[], int& n, int i)
{
  // Check if the index is valid
  if (i < 0 || i >= n)
  {
    throw "The index to be removed is invalid";
  }

  // Replace the element to be removed with the last element
  a[i] = a[n - 1];

  // Decrement the size of the heap
  n--;

  // If the replaced element is greater than its parent, bubble it up
  if (i > 0 && a[i] > a[(i - 1) / 2])
  {
    bubbleUp(a, i);
  }
  else
  {
    // Otherwise, heapify down
    max_heapify(a, n, i);
  }
}

#endif //HEAP_SORT2_H   