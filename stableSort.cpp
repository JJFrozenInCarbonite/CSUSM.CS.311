/******************************************************************************                                           
Template prepared by Kazumi Slott                                                  
CS311                                                                              
This program sorts an array of persons using a stable sorting algorithm.
You will also see what happens if you do the same using an unstable sorting algorithm.                                            
                                                                                   
Your name: ?????                                                                   
Your programmer number: ?????                                                      
Hours spent: ??????                                                                
Any difficulties?: ?????                                                           
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
//#include ?????????  //<=== include your swap.h if you made it so you can call your mySwap() in stableSort(). 
                      //     If you didn't make it, you can make a swap function in this file or call the library's swap(). 
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

void stableSort(/*????????????*/)
{
  //You can use a stable sorting algorithm of your choice                             
  //use the technique shown in my lecture notes "Lec on passing functions"         
  //Include your swap.h at the top so you can call your mySwap() to swap persons in this function.           
  //If you didn't make swap.h, you can make a swap function in this file or call the library's swap().                    
}

void unstableSort(/*????????????*/)
{
  //Use the unstable sorting algorithm that has the complexity O(n^2)
  //Copy the appropriate function from the *original* template for sort.h, not the function you modified.
}

int main()
{
  person ar[SIZE];
  
  cout << "+++++ stable sorting algo +++++" << endl;
  if(fillAr(ar))
    {
      cout << "--- original ---" << endl;
      printAr(ar);

      //You need to sort the array here using the stable sorting algorithm
      //HINT: call stableSort multiple times.

      cout << "--- result ---" << endl;
      printAr(ar);
    }

  cout << "\n+++++ unstable sorting algo +++++" << endl;
  if(fillAr(ar))
    {
      cout << "--- original ---" << endl;
      printAr(ar);

      //Try the same as above using the unstable sorting algorithm to see what happens

      cout << "--- result ---" << endl;
      printAr(ar);
    }
  
  return 0;
}


