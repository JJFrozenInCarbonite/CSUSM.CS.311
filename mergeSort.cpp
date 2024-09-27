/**********************************
Templated created by Kazumi Slott
CS311

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent: 1
Any difficulties?: I broke down and had to rename all the array references to arr instead of ar. I'm also struggling with CamelCase, 
I do a vast majority of my work in Python where only classes use CamelCase and variables/functions use snake_case.
***********************************/
#include <iostream>
using namespace std;

/**
 * @brief Prints the elements of an array.
 * 
 * @param arr The array to be printed.
 * @param s The size of the array.
 */
void printArr(const int arr[], int s)
{
 for(int i = 0; i < s; i++)
    cout << arr[i] << " ";
  cout << endl;
}

/**
 * @brief Merges two sorted subarrays into a single sorted subarray.
 * 
 * This function merges two sorted subarrays of arr[].
 * The first subarray is arr[first..mid]
 * The second subarray is arr[mid+1..last]
 * 
 * @param arr The array containing the subarrays to be merged.
 * @param first The starting index of the first subarray.
 * @param mid The ending index of the first subarray and the midpoint of the array.
 * @param last The ending index of the second subarray.
 */
void merge(int arr[], int first, int mid, int last)
{

  // Create a temp array to hold the merged elements
  int size = last - first + 1;
  int *temp = new int[size];

  int left = first;     // Pointer for left half
  int right = mid + 1;  // Pointer for right half
  int index = 0;        // Pointer for temp array

  // Merge the two halves into temp
  while (left <= mid && right <= last)
  {
      if (arr[left] <= arr[right])  // Stable sorting implementation
      {
          temp[index++] = arr[left++];
      }
      else
      {
          temp[index++] = arr[right++];
      }
  }

  // Copy remaining elements of the left half,if any
  while (left <= mid)
  {
      temp[index++] = arr[left];
      left++;
  }

  // Copy remaining elements of the right half, if any
  while (right <= last)
  {
      temp[index++] = arr[right];
      right++;
  }

  // Copy the sorted elements back into the original array
  for (int i = 0; i < size; i++)
  {
      arr[first + i] = temp[i];
  }

  // Delete the temp array
  delete[] temp;  
}

/**
 * @brief Sorts an array using the mergeSort algorithm.
 * 
 * This function sorts the array arr[] using the mergeSort algorithm.
 * It recursively divides the array into subarrays and sorts them.
 * 
 * @param arr The array to be sorted.
 * @param first The starting index of the array to be sorted.
 * @param last The ending index of the array to be sorted.
 */
void mergeSort(int arr[], int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        
        // Recursively sort the left and right halves
        mergeSort(arr, first, mid);
        mergeSort(arr, mid + 1, last);
        
        // Merge the two halves
        merge(arr, first, mid, last);
    }
}

int main()
{
  int arr[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(arr, 0, 8);
  printArr(arr, 9); //1 2 3 4 5 6 8 10 22

  int arr1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(arr1, 0, 5);
  printArr(arr1, 6); //1 3 4 5 7 9 

  int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(arr2, 0, 9);
  printArr(arr2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
