/**********************************
Templated created by Kazumi Slott
CS311

Your name:?????????
Your programmer number: ??????
Hours spent: ????
Any difficulties?:??????????
***********************************/
#include <iostream>
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

void merge(/*????????*/)
{
  //For implementation of this function, refer to my lecture notes "merge sort"
  //If you used a different technique, you would receive zero points.
  
  //Also make sure you are making a stable sorting algorithm.

  //Don't forget to destroy temp array, which is created dynamically
}

void mergeSort(int ar[], int first, int last)
{
  //For implementation of this function, refer to my lecture notes "merge sort"
}

int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
