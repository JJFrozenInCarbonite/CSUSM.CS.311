/**********************************
Templated created by Kazumi Slott
CS311

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent: 1.5
Any difficulties: Using ar instead of arr only drove me slightly insane.
***********************************/
#include <iostream>
#include "swap.h"
using namespace std;

/**
 * Prints the elements of an array.
 * 
 * @param ar[] The array to be printed.
 * @param s The size of the array.
 */
void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

// Template function from swap.h
/**
 * Prints the elements of an array.
 * 
 * @param ar[] The array to be printed.
 * @param s The size of the array.
 *
template <class T>
void mySwap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}
*/

/**
 * Partitions the array around a pivot.
 * 
 * This implementation moves the pivot to the end of the array then partitions the array.
 * 
 * @param ar[] The array to be partitioned.
 * @param start The starting index of the partition to be sorted.
 * @param end The ending index of the partition to be sorted.
 * 
 * @return The index where the pivot is placed after partitioning.
 */
int partition(int ar[], int start, int end) {
    int mid = (start + end) / 2;
    mySwap(ar[mid], ar[end]);  // Swap middle element with the last

    int pivot = ar[end];       // Pivot is now the last element
    int red = start;           // Red starts at the beginning

    for (int green = start; green < end; green++) {
        if (ar[green] < pivot) {
            mySwap(ar[red], ar[green]);
            red++;             // Move red pointer to the right
        }
    }
    mySwap(ar[red], ar[end]);   // Swap the pivot with the red pointer
    return red;                // Return the index of the pivot
}

/**
 * Sorts an array using the quicksort algorithm.
 *  
 * @param ar[] The array to be sorted.
 * @param start The starting index of the portion of the array to be sorted.
 * @param end The ending index of the portion of the array to be sorted.
 */
void quickSort(int ar[], int start, int end) {
    if (start >= end) 
        return;                // If the partition has 0 or 1 element, return
    else {
        int pivot = partition(ar, start, end);  // Partition and get pivot index
        quickSort(ar, start, pivot - 1);        // Sort left partition
        quickSort(ar, pivot + 1, end);          // Sort right partition
    }
}

int main() {
  int ar[] = {15, 10, 5, 7, 1, 4, 12, 8, 6};
  quickSort(ar, 0, 8);
  printAr(ar, 9); //1 4 5 6 7 8 10 12 15

  int ar1[] = {1, 7, 5, 3, 9, 4};
  quickSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quickSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
