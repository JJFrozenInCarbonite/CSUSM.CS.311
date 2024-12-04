#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm> 
#include "sort.h"
#include "heapSort2.h"


using namespace std;

vector<double> times;

void measureExecutionTime(void (*sortFunction)(int[], int), int ar[], int original[], int size, int numTests) {
    times.resize(numTests);
    clock_t start, end;
    for (int i = 0; i < numTests; i++) {
        cout << "Test: " << (i + 1) << endl;
        std::copy(original, original + size, ar);
        start = clock();
        sortFunction(ar, size);
        end = clock();
        double time = (end - start) / double(CLOCKS_PER_SEC) * 1000;
        cout << "Elapsed time: " << time << " milliseconds" << endl;
        times[i] = time;
    }

    double average_time = 0;
    for (double time : times)
        average_time += time;
    average_time /= times.size();
    cout << "Average elapsed time: " << average_time << " milliseconds" << endl;
}

void runSelectionSort(int ar[], int original[], int size, int numTests) {
    measureExecutionTime(selectionSort, ar, original, size, numTests);
}

void runBubbleSort(int ar[], int original[], int size, int numTests) {
    measureExecutionTime(bubbleSort, ar, original, size, numTests);
}

void runInsertionSort(int ar[], int original[], int size, int numTests) {
    measureExecutionTime(insertionSort, ar, original, size, numTests);
}

void runQuickSort(int ar[], int original[], int size, int numTests) {
    measureExecutionTime([](int ar[], int size) { quickSort(ar, 0, size - 1); }, ar, original, size, numTests);
}

void runMergeSort(int ar[], int original[], int size, int numTests) {
    measureExecutionTime([](int ar[], int size) { mergeSort(ar, 0, size - 1); }, ar, original, size, numTests);
}

void runHeapSort(int ar[], int original[], int size, int numTests) {
    measureExecutionTime(heapSort, ar, original, size, numTests);
}

void runRadixSort(int ar[], int original[], int size, int numTests) {
    measureExecutionTime(heapSort, ar, original, size, numTests);
}

void runSort(char sort, int ar[], int original[]) {
    ifstream fin;

    cout << "How many numbers do you want to put into the array?: ";
    cout << "Please enter a number between 1 and 1000000: ";
    int s;
    cin >> s;

    cout << "How many times do you want to run the test?: ";
    "Please enter a number between 1 and 1000: ";
    cin >> s;

    fin.open("/cs/slott/cs311/sort.in");
    if (!fin) {
        cerr << "The input file doesn't open" << endl;
        exit(1);
    }

    for (int i = 0; i < s; i++)
        fin >> original[i];
    fin.close();

    cout << "\n============ Testing ";
    switch (sort) {
    case 'S':
        cout << "selection sort with " << s << " numbers" << endl;
        runSelectionSort(ar, original, s, numTests);
        break;
    case 'B':
        cout << "bubble sort with " << s << " numbers" << endl;
        runBubbleSort(ar, original, s, numTests);
        break;
    case 'I':
        cout << "insertion sort with " << s << " numbers" << endl;
        runInsertionSort(ar, original, s, numTests);
        break;
    case 'Q':
        cout << "quick sort with " << s << " numbers" << endl;
        runQuickSort(ar, original, s, numTests);
        break;
    case 'M':
        cout << "merge sort with " << s << " numbers" << endl;
        runMergeSort(ar, original, s, numTests);
        break;
    case 'H':
        cout << "heap sort with " << s << " numbers" << endl;
        runHeapSort(ar, original, s, numTests);
        break;
    default:
        cerr << "Invalid sorting option" << endl;
        break;
    }
}

int main() {
    const int MAX = 1000000;
    int ar[MAX];
    int original[MAX];
    char choice;

    do {
        cout << "---------------------------------------------" << endl;
        cout << "Enter S for selection sort: " << endl;
        cout << "      B for bubble sort: " << endl;
        cout << "      I for insertion sort: " << endl;
        cout << "      Q for quick sort: " << endl;
        cout << "      M for merge sort: " << endl;
        cout << "      H for heap sort: " << endl;
        cout << "      E to end the program: " << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        choice = toupper(choice);
        if (choice == 'S' || choice == 'B' || choice == 'I' || choice == 'Q' || choice == 'M' || choice == 'H')
            runSort(choice, ar, original);
        else if (choice != 'E')
            cout << "!!!!!!!!!!!!!!!!!!!! " << choice << " is INVALID !!!!!!!!!!!!!!!!!!" << endl;
    } while (choice != 'E');

    return 0;
}