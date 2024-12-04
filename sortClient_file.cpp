/********************************************************************************
CS311
Kazumi Slott

This program tells how long it takes for each of your sorting algorithms to sort an 
array with a different number of elements.
*********************************************************************************/
#define TN 400
#include <iostream>
#include <fstream>
#include <ctime> // for clock()
#include <cstdlib> //for exit()
#include <vector>
using namespace std;
#include "sort.h"
#include "heapSort2.h"
#include "/cs/slott/cs211/checkInput.h" //for getData()

vector<double> times(TN);

void runSort(char sort, int ar[])
{
  clock_t start, end;
  ifstream fin;

  cout << "How many numbers do you want to put into the array?: ";
  //the number of elements we can accept is 1 to 1 million. The input file has 1 million numbers. You might want to open it to see.
  int s = getData(1, 1000000, "Please enter a number between 1 and 1000000: ");//getData() is in /cs/slott/cs211/checkInput.h

  fin.open("/cs/slott/cs311/sort.in"); //sort.in has 1000000 numbers
  if(!fin)
    {
      cout << "The input file doesn't open" << endl;
      exit(1); //ending the program
    }

  //fill the array
  for(int i = 0; i < s; i++)
    fin >> ar[i]; 
  fin.close();

  cout << "\n============ Testing ";
  switch(sort)
    {
    case 'S':  
    case 's':  cout << " selection sort ";
              times.clear(FN);
              for (int i = 0; i < times.size(); i++) {
                cout << "Test: " << (i + 1) << endl;
                start = clock();
                selectionSort(ar, s);
                end = clock();
                double time = (end - start) / double(CLOCKS_PER_SEC) * 1000;
                cout << "Elapsed time: " << time << " milliseconds" << endl;
                times[i] = time;
              }
              break;
    case 'B':  
    case 'b':  cout << " bubble sort ";
              times.clear(FN);
              for (int i = 0; i < times.size(); i++) {
              cout << "Test: " << (i + 1) << endl;
                start = clock();
                bubbleSort(ar, s);
                end = clock();
                double time = (end - start) / double(CLOCKS_PER_SEC) * 1000;
                cout << "Elapsed time: " << time << " milliseconds" << endl;
                times[i] = time;
              }
              break;
    case 'I':  
    case 'i':  cout << " insertion sort ";
              times.clear(FN);
              for (int i = 0; i < times.size(); i++) {
              cout << "Test: " << (i + 1) << endl;
                start = clock();
                insertionSort(ar, s);
                end = clock();
                double time = (end - start) / double(CLOCKS_PER_SEC) * 1000;
                cout << "Elapsed time: " << time << " milliseconds" << endl;
                times[i] = time;
              }
               break;
    case 'Q':  
    case 'q':  cout << " quick sort ";
              times.clear(FN);
              for (int i = 0; i < times.size(); i++) {
              cout << "Test: " << (i + 1) << endl;
                start = clock();
                quickSort(ar, 0, s - 1);
                end = clock();
                double time = (end - start) / double(CLOCKS_PER_SEC) * 1000;
                cout << "Elapsed time: " << time << " milliseconds" << endl;
                times[i] = time;
              }
               break;
    case 'M':  
    case 'm':  cout << " merge sort ";
              times.clear(FN);
              for (int i = 0; i < times.size(); i++) {
              cout << "Test: " << (i + 1) << endl;
                start = clock();
                mergeSort(ar, 0, s - 1);
                end = clock();
                double time = (end - start) / double(CLOCKS_PER_SEC) * 1000;
                cout << "Elapsed time: " << time << " milliseconds" << endl;
                times[i] = time;
              }
               break;

    case 'H':  cout << " heap sort ";
              times.clear(FN);
              for (int i = 0; i < times.size(); i++) {
              cout << "Test: " << (i + 1) << endl;
                start = clock();
                heapSort(ar, s);
                end = clock();
                double time = (end - start) / double(CLOCKS_PER_SEC) * 1000;
                cout << "Elapsed time: " << time << " milliseconds" << endl;
                times[i] = time;
              }
               break;
    }

  cout << " with " << s << " numbers" << endl;
  double average_time;
  for(int i = 0; i < times.size(); i++)
    average_time += times[i];
  average_time /= (double)times.size();
  cout << "Elapsed time: " << average_time << " milliseconds" << endl;
}  

int main()
{
  const int MAX = 1000000; //the input file has 1000000 numbers
  int ar[MAX]; //Make an array here instead of runSort() so it won't get destroyed after each call to runSort()
  char choice;//choice of sorting type

  do
    {
      cout << "---------------------------------------------" << endl;
      cout << "Enter S for selection sort: " << endl;
      cout << "      B for bubble sort: " << endl;
      cout << "      I for insertion sort: " << endl;
      cout << "      Q for quick sort: " << endl;
      cout << "      M for merge sort: " << endl;
      cout << "      E for end the program: " << endl;
      cout << "      H for heap sort: " << endl;
      cout << "Please enter your choice: ";
      cin >> choice; 

      choice = toupper(choice); //making a lowercase letter to upper case by calling the library's toupper()
      if(choice == 'S' || choice == 'B' || choice == 'I' || choice == 'Q' || choice == 'M' || choice == 'H')
	runSort(choice, ar);     
      else if(choice != 'E')
	cout << "!!!!!!!!!!!!!!!!!!!! " << choice << " is INVALID !!!!!!!!!!!!!!!!!!" << endl;
    }while(choice != 'E');
     
  return 0;
}

