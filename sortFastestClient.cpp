/**************************************************
Implemented by Kazumi Slott
CS311

This client tests quick sort and radix sort with the same string array.
**************************************************/
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "sort.h"
#include "radix.h"
using namespace std;

int main() {
  
  
  const int MAX = 250000; // Maximum array size allowed

  clock_t start, end;
  ifstream fin;

  cout << "How many numbers do you want to put into the array?: ";
  
  int s = -1;
  while (s < 1 || s > 250000) {
    cout << "Please enter a number between 1 and 250000: ";
    cin >> s;
  }

  int* ar = new int[s];
  int* arCopy = new int[s];
  
  fin.open("/cs/slott/cs311/sort.in");
  if (!fin) {
    cout << "The input file doesn't open" << endl;
    delete[] ar;
    delete[] arCopy;
    return 0; // Program ends here
  }

  // Fill the array and create a copy for radix sort
  for (int i = 0; i < s; i++) {
    fin >> ar[i];
    arCopy[i] = ar[i];
  }
  fin.close();

  // Test Quick Sort
  cout << "\n============ Testing Quick Sort";
  start = clock();
  quickSort(ar, 0, s - 1);
  end = clock();
  cout << " with " << s << " numbers" << endl;
  cout << "Elapsed time: " << (end - start) / double(CLOCKS_PER_SEC) * 1000 << " milliseconds" << endl;

  // Test Radix Sort
  cout << "\n============ Testing Radix Sort";
  LL all;
  for (int i = 0; i < s; i++) {
      all.addRear(arCopy[i]);
  }
  start = clock();
  radixSort(all);
  end = clock();
  cout << " with " << s << " numbers" << endl;
  cout << "Elapsed time: " << (end - start) / double(CLOCKS_PER_SEC) * 1000 << " milliseconds" << endl;
  return 0;
}