/**************************************
Template created by Kazumi Slott
CS311

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent: 1
Any difficulties?:
**************************************/

#include <iostream>
using namespace std;

void swap(int& data1, int& data2)
{
  int temp = data1;
  data1 = data2;
  data2 = temp;
}
/*
void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}

*/

//https://www.youtube.com/watch?v=ROalU379l3U
//Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.
void insertionSort(int arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && arr[j - 1] > arr[j])
    {
      swap(arr[j], arr[j - 1]);
      j--;
    }
  }
}


//The following function sorts the array in ascending order by moving the largest value to the end.
//Change the code so the array gets sorted in ascending order by moving the smallest value to the beginning.
//Make sure you change varibale names and comments to suit your new code.
//<REQUIREMENT> don't change the structure.
//You can find more information in my homework document

//The following function sorts the array in ascending order by moving the smallest value to the beginning.
void selectionSort(int array[], int N)
{
  int smlIndx; //the index of the smallest value

  //first is the first index in unsorted part
  for(int first = 0; first < N - 1; first++)
    {
      smlIndx = first; //assume the first item is the smallest
      //find the smallest in unsorted part ([first..N-1])
      for(int i = first + 1; i < N; i++)
      {
        if(array[i] < array[smlIndx]) //The current item is smaller
          smlIndx = i;
      }

      //swap the smallest with the first item in the unsorted part
      swap(array[smlIndx], array[first]);
    }
}


//Replace the ????s.
//For more info on bubble sort, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum" 
void bubbleSort(int ar[], int s)
{
  bool swapped = true; //true if there was swapping in the current iteration, false otherwise                                   
  int last = s-2; //last is the index of the left element of the last pair to be checked in the current iteration.

  while(swapped) //swapping required in the previous iteration or the first iteration starts                        
  {
    swapped = false; //no swapping has happened yet when a new iteration starts.                                         

    for(int i = 0; i <= last; i++) //check each adjacent pair of items in the unsorted part                     
    {
      if(ar[i] > ar[i + 1]) //the pair is out of order                                                          
      {
        swap(ar[i], ar[i + 1]);
        swapped = true; //swapping required - meaning we need to proceed to the next iteration.                            
      }
    }
    last--; //the area to be checked shrinks down after each iteration                                         
  }//end of while                                                                                               
}

template <typename T>
int partition(T arr[], int start, int end)
{
    int mid = (start + end) / 2;
    swap(arr[mid], arr[end]);  // Swap middle element with the last

    T pivot = arr[end];        // Pivot is now the last element
    int red = start;           // Red starts at the beginning

    for (int green = start; green < end; green++) {
        if (arr[green] < pivot) {
            swap(arr[red], arr[green]);
            red++;             // Move red pointer to the right
        }
    }
    swap(arr[red], arr[end]);  // Swap the pivot with the red pointer
    return red;                // Return the index of the pivot
}

template <typename T>
void quickSort(T arr[], int start, int end)
{
    if (start >= end)
        return;                // If the partition has 0 or 1 element, return
    else {
        int pivot = partition(arr, start, end);  // Partition and get pivot index
        quickSort(arr, start, pivot - 1);        // Sort left partition
        quickSort(arr, pivot + 1, end);          // Sort right partition
    }  
}

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


