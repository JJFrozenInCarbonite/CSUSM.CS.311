/**************************************
Template created by Kazumi Slott
CS311

Your name:
Your programmer number:
Hours spent:
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

void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}


//https://www.youtube.com/watch?v=ROalU379l3U
//Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.
void insertionSort(int ar[], int n)
{
  //call swap
}


//The following function sorts the array in ascending order by moving the largest value to the end.
//Change the code so the array gets sorted in ascending order by moving the smallest value to the beginning.
//Make sure you change varibale names and comments to suit your new code.
//<REQUIREMENT> don't change the structure.
//You can find more information in my homework document
void selectionSort(int array[], int N)
{
  int lrgIndx; //the index of the largest value

  //last is the last index in unsorted part
  for(int last = N-1; last >= 1; last--)
    {
      lrgIndx = 0; //assume the first item is the largest
      //find the largest in unsorted part ([0..last])
      for(int i = 1; i <= last; i++)
	{
	  if(array[i] > array[lrgIndx]) //The current item is larger
	    lrgIndx = i;
	}

      //swap the largest with the last item in the unsorted part
      swap(array[lrgIndx],array[last]);
    }
}


//Replace the ????s.
//For more info on bubble sort, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum" 
void bubbleSort(int ar[], int s)
{
  /*
  bool swapped = ?????; //true if there was swapping in the current iteration, false otherwise                                   
  int last = ????; //last is the index of the left element of the last pair to be checked in the current iteration.

  while(????) //swapping required in the previous iteration or the first iteration starts                        
    {
      swapped = ????; //no swapping has happened yet when a new iteration starts.                                         

      for(????; i <= last; ???????) //check each adjacent pair of items in the unsorted part                     
        {
	  if(?????????????) //the pair is out of order                                                          
	    {
	      swap(?????????????);
	      ????????? //swapping required - meaning we need to proceed to the next iteration.                            
	    }
        }
      ??????? //the area to be checked shrinks down after each iteration                                         
    }//end of while                                                                                               
  */
}


int partition(int a[], int start, int end)
{
  //copy and paste partition() from your quickSort.cpp
}

void quickSort(int ar[], int start, int end)
{
  //copy and paste quickSort() from your quickSort.cpp   
}


void merge(int ar[], int first, int last)
{
  //copy and paste merge() from your mergeSort.cpp   
}

void mergeSort(int ar[], int first, int last)

{
  //copy and paste mergeSort()from your mergeSort.cpp   
}


