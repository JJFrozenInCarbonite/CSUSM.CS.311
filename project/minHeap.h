#ifndef MINHEAP_H
#define MINHEAP_H

template <typename T>
void swap(T &v1, T &v2, int* locatorArray);  // Forward declaration

template <class T>
class MinHeap {
    private:
        T* arr;         // Dynamic array to hold heap elements
        int arrCount;   // Number of elements in the heap
        int arrSize;    // Size of the heap array
        
    public:
        MinHeap();                                      // Default constructor
        MinHeap(int size);                              // Constructor with size
        ~MinHeap();                                     // Destructor
        void insert(const T& value, int* locatorArray); // Insert an element into the heap
        T extractMin(int* locatorArray);                // Extract the minimum element from the heap
        T getMin();                                     // Get the minimum element from the heap
        void heapifyDown(int index, int* locatorArray); // Restore the heap property from a specific index
        void heapifyUp(int index, int* locatorArray);   // Restore the heap property from a specific index
        bool isEmpty();                                 // Check if the heap is empty
        int getSize();                                  // Get the number of elements in the heap
        void remove(int index, int* locatorArray);      // Remove an element at a specific index

        class Underflow {};     // Exception for underflow
        class Overflow {};      // Exception for overflow
        class BadIndex {};      // Exception for bad index
        class NotFound {};      // Exception for not found

};

/**********************************************************************************
What does the function do? Default constructor
What does it return? MinHeap object

Parameter 1: N/A
**********************************************************************************/
template <class T>
MinHeap<T>::MinHeap() {
    arr = nullptr;  // Initialize the array to null
    arrCount = 0;   // Initialize the number of elements to 0
    arrSize = 0;    // Initialize the size of the array to 0
}

/**********************************************************************************
What does the function do? Constructor with size
What does it return? MinHeap object

Parameter 1: Size of the heap array
**********************************************************************************/
template <class T>
MinHeap<T>::MinHeap(int size) {
    arr = new T[size];  // Create a new array of size s
    arrCount = 0;       // Initialize the number of elements to 0
    arrSize = size;     // Set the size of the array to s
}

/**********************************************************************************
What does the function do? Destructor
What does it return? N/A

Parameter 1: N/A
**********************************************************************************/
template <class T>
MinHeap<T>::~MinHeap() {
    delete[] arr;   // Delete the array
    arr = nullptr;  // Set the array to nullptr
}

/**********************************************************************************
What does the function do? Insert an element into the heap
What does it return? N/A

Parameter 1: Value to be inserted
Parameter 2: Locator array
**********************************************************************************/
template <class T>
void MinHeap<T>::insert(const T& value, int* locatorArray) {
    if (arrCount == arrSize) {
        throw Overflow();               // Throw an overflow exception if the array is full
    }
    arr[arrCount] = value;              // Insert the value at the end of the array
    heapifyUp(arrCount, locatorArray);  // Restore the heap property
    arrCount++;                         // Increment the number of elements
}

/**********************************************************************************
What does the function do? Extract the minimum element from the heap
What does it return? Minimum element T

Parameter 1: Locator array
**********************************************************************************/
template <class T>
T MinHeap<T>::extractMin(int* locatorArray) {
    if (arrCount == 0) {
        throw Underflow();                  // Throw an underflow exception if the array is empty
    }
    T min = arr[0];                         // Get the minimum element
    locatorArray[arr[0].vertexIndex] = -1;  // Mark the element as removed in the locator array
    arr[0] = arr[arrCount - 1];             // Move the last element to the root
    locatorArray[arr[0].vertexIndex] = 0;   // Update the locator for the moved element
    arrCount--;                             // Decrement the number of elements
    heapifyDown(0, locatorArray);           // Restore the heap property
    return min;                             // Return the minimum element
}

/**********************************************************************************
What does the function do? Get the minimum element from the heap
What does it return? Minimum element T

Parameter 1: N/A
**********************************************************************************/
template <class T>
T MinHeap<T>::getMin() {
    if (arrCount == 0) {
        throw Underflow();  // Throw an underflow exception if the array is empty
    }
    return arr[0];  // Return the minimum element
}

/**********************************************************************************
What does the function do? Restore the heap property from a specific index downwards
What does it return? N/A

Parameter 1: Index to start heapifying
Parameter 2: Locator array
**********************************************************************************/
template <class T>
void MinHeap<T>::heapifyDown(int index, int* locatorArray) {
    int left = 2 * index + 1;   // Calculate the left child index
    int right = 2 * index + 2;  // Calculate the right child index
    int smallest = index;       // Initialize the smallest index to the current index

    if (left < arrCount && arr[left] < arr[smallest]) {
        smallest = left;    // Update the smallest index if the left child is smaller
    }
    if (right < arrCount && arr[right] < arr[smallest]) {
        smallest = right;   // Update the smallest index if the right child is smaller
    }
    if (smallest != index) {
        swap(arr[index], arr[smallest], locatorArray); // Swap the elements
        heapifyDown(smallest, locatorArray);           // Recursively heapify down
    }
}

/**********************************************************************************
What does the function do? Restore the heap property from a specific index upwards
What does it return? N/A

Parameter 1: Index to start heapifying
Parameter 2: Locator array
**********************************************************************************/
template <class T>
void MinHeap<T>::heapifyUp(int index, int* locatorArray) {
    int parent = (index - 1) / 2;   // Calculate the parent index

    if (index > 0 && arr[index] < arr[parent]) {
        swap(arr[index], arr[parent], locatorArray);   // Swap the elements
        heapifyUp(parent, locatorArray);               // Recursively heapify up
    }
}

/**********************************************************************************
What does the function do? Check if the heap is empty
What does it return? True if the heap is empty, false otherwise

Parameter 1: N/A
**********************************************************************************/
template <class T>
bool MinHeap<T>::isEmpty() {
    return arrCount == 0;   // Return true if the number of elements is 0
}

/**********************************************************************************
What does the function do? Get the number of elements in the heap
What does it return? Number of elements

Parameter 1: N/A
**********************************************************************************/
template <class T>
int MinHeap<T>::getSize() {
    return arrCount;    // Return the number of elements
}

/**********************************************************************************
What does the function do? Remove an element at a specific index
What does it return? N/A

Parameter 1: Index of the element to be removed
Parameter 2: Locator array
**********************************************************************************/
template <class T>
void MinHeap<T>::remove(int index, int* locatorArray) {
    if (index < 0 || index >= arrCount) {
        throw BadIndex();   // Throw a bad index exception if the index is out of bounds
    }

    locatorArray[arr[index].vertexIndex] = -1;      // Mark the element as removed in the locator array
    arr[index] = arr[arrCount - 1];                 // Move the last element to the index
    locatorArray[arr[index].vertexIndex] = index;   // Update the locator for the moved element
    arrCount--;                                     // Decrement the number of elements
    
    // Restore the heap property
    if (index > 0 && arr[index] < arr[(index - 1) / 2]) {
        heapifyUp(index, locatorArray);             
    } else {
        heapifyDown(index, locatorArray);           
    }
}

#endif // MINHEAP_H