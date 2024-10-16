/******************************************************************************                                           
Template prepared by Kazumi Slott                                                  
CS311                                                                              
This program sorts an array of persons using a stable sorting algorithm.
You will also see what happens if you do the same using an unstable sorting algorithm.                                            
                                                                                   
Your name: JJ Hoffmann                                                                   
Your programmer number: 16                                                      
Hours spent: 2                                                                
Any difficulties?: A tiny bit of trouble with updating unstableSort                                                    
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "swap.h"

using namespace std;

const int SIZE = 13;

struct person
{
  string fN;
  string lN;
  int grade;
};

bool fillAr(person a[])
{
  ifstream fin;
  fin.open("/cs/slott/cs311/stableSort3.in");

  if(!fin)
    {
      cout << "You don't have the input file" << endl;
      return false;
    }
  string f, l;
  int g;
  int i = 0;

  fin >> f >> l >> g;
  while(fin)
    {
      a[i].fN = f;
      a[i].lN = l;
      a[i++].grade = g;
      fin >> f >> l >> g;
    }
  fin.close();
  return true;
}

void printAr(const person a[])
{
  for(int i = 0; i < SIZE; i++)
    cout << a[i].grade << "  " << left << setw(10) << a[i].lN << setw(10) << a[i].fN << endl;
}

//You need to create some functions here, which will be called from stableSort()

bool compareGrade(const person &a, const person &b)
{
    return a.grade < b.grade;  
}

bool compareLastName(const person &a, const person &b)
{
    return a.lN < b.lN;  
}

bool compareFirstName(const person &a, const person &b)
{
    return a.fN < b.fN;  
}

void merge(person a[], int left, int mid, int right, bool (*comp)(const person&, const person&))
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    person L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    // Initial indexes of first and second subarrays
    int i = 0, j = 0;
    // Initial index of merged subarray
    int k = left;

    // Merge the temp arrays back into a[]
    while (i < n1 && j < n2)
    {
        // To guarantee ascending order comparison, we might need to reverse the condition.
        if (!comp(R[j], L[i])) 
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
        a[k++] = L[i++];

    // Copy the remaining elements of R[], if any
    while (j < n2)
        a[k++] = R[j++];
}



void stableSort(person a[], int left, int right, bool (*comp)(const person&, const person&))
{
  //You can use a stable sorting algorithm of your choice                             
  //use the technique shown in my lecture notes "Lec on passing functions"         
  //Include your swap.h at the top so you can call your mySwap() to swap persons in this function.           
  //If you didn't make swap.h, you can make a swap function in this file or call the library's swap().        
  if (left < right)
  {
      int mid = left + (right - left) / 2;

      stableSort(a, left, mid, comp);
      stableSort(a, mid + 1, right, comp);

      merge(a, left, mid, right, comp);
  }
}
    
void unstableSort(person a[], int N, bool (*comp)(const person&, const person&))
{
  int lrgIndx; // the index of the largest value

  // last is the last index in unsorted part
  for (int last = N - 1; last >= 1; last--)
  {
    lrgIndx = 0; // assume the first item is the largest
    // find the largest in unsorted part ([0..last])
    for (int i = 1; i <= last; i++)
    {
      if (comp(a[lrgIndx], a[i])) // if the current item is larger
        lrgIndx = i;
    }

    // swap the largest with the last item in the unsorted part
    swap(a[lrgIndx], a[last]);
  }
}

int main()
{
  person ar[SIZE];
  
  cout << "+++++ stable sorting algo +++++" << endl;
  if(fillAr(ar))
    {
      cout << "--- original ---" << endl;
      printAr(ar);

      stableSort(ar, 0, SIZE - 1, compareFirstName);
      stableSort(ar, 0, SIZE - 1, compareLastName);
      stableSort(ar, 0, SIZE - 1, compareGrade);

      cout << "--- result ---" << endl;
      printAr(ar);
    }

  cout << "\n+++++ unstable sorting algo +++++" << endl;
  if(fillAr(ar))
    {
      cout << "--- original ---" << endl;
      printAr(ar);

      unstableSort(ar, SIZE, compareFirstName);
      unstableSort(ar, SIZE, compareLastName);
      unstableSort(ar, SIZE, compareGrade);

      cout << "--- result ---" << endl;
      printAr(ar);
    }
  
  return 0;
}