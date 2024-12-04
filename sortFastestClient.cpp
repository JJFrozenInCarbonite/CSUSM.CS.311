/**************************************************
Implemented by Kazumi Slott
CS311

This client tests quick sort and radix sort with the same string array.
**************************************************/

#include <fstream>
#include <ctime>
#include "/cs/slott/cs211/checkInput.h"
#include "sort.h"
#include "radix.h"

int main() {
  const int MAX = 250000; // Maximum array size allowed
  string ar[MAX];
  string arCopy[MAX]; // Copy of the array for radix sort

  clock_t start, end;
  ifstream fin;

  cout << "How many numbers do you want to put into the array?: ";
  int s = getData(1, 250000, "Please enter a number between 1 and 250000: ");

  fin.open("sortString1mil.in");
  if (!fin) {
    cout << "The input file doesn't open" << endl;
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
  makeLL(all, arCopy, s);
  start = clock();
  radixSort(all);
  end = clock();
  cout << " with " << s << " numbers" << endl;
  cout << "Elapsed time: " << (end - start) / double(CLOCKS_PER_SEC) * 1000 << " milliseconds" << endl;

  return 0;
}