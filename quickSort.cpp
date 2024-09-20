/**********************************
Templated created by Kazumi Slott
CS311

Your name:?????????
Your programmer number: ??????
Hours spent: ?????
Any difficulties?:??????????
***********************************/
#include <iostream>
using namespace std;
//?????????? include your swap.h for mySwap().  If you didn't make it for our first homework or it didn't work, you could implement it down below within this program.

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

/*
//Implement mySwap() here if you didn't make mySwap() in swap.h for our first homework.
//It is good to have the swap function so partition() won't get crowded. 
void mySwap(?????????????)
{
}
*/

int partition(/*????????*/)
{
  //I have 3 variables: pivot, i and swap_index. You may have any local variables.

  //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).

  //For implementation of this function, refer to my lecture notes "quick sort". 
  //If you used a different way, you would receive zero points.

  //This function returns the index where the pivot value went in. 
}

void quickSort(int ar[], int start, int end)
{
  /*
  if(????????) //If the partition has only one element or none, return. 
                   //In other words, if the partition has at least 2 elements, go inside the if.
                   //use start and end to figure out how many elements you have in the partition.
    {
      //call partition.
      //quickSort on the left partition
      //quickSort on the right partition
    }
  */
}

int main()
{
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
