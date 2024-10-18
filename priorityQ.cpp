/******************************************************
Template prepared by Kazumi Slott
CS311
Emergency room program - application of priority queue

If you decide to use my getNum(), you need to compile your program as follows.
g++ -std=c++11 priorityQ.cpp //stoi requires to be compiled with c++11

Program description: ?????
Your name: JJ Hoffmann
Your programmer number: 16
Hours spent making this application: 2
Are you rejecting invalid inputs?: Yes
Any difficulties: Getting the outputs to match up provided a bit of re-work as I'm not used
to including the re-prompt at the end of the error message.
********************************************************/
#include <iostream>
#include <string> //for stoi()
using namespace std;
#include "minHeap.h"
//#include "/cs/slott/cs211/checkInput.h" //You might want to check this header to see if you could use getData(min, max, errorMessage). You don't have to use it.


void showMenu();
void addPatient(int& patientCount, minHeap<int>& patientQueue);
void nextPatient(minHeap<int>& patientQueue);
int getNum();
void printQueue(const minHeap<int>& patientQueue);


const int START = 1000; //assuming this number will not go over 9999

int main()
{
  int choice; // user choice
  int patientCount = START; // A monotonically increasing integer to be used as part of the patient ID
  minHeap<int> patientQueue(START); // array to store patient numbers

  showMenu();
  while (choice != 3)
    {
      choice = getNum();
      switch (choice) {
        case 1:
          addPatient(patientCount, patientQueue);
          showMenu();
          break;
        case 2:
          nextPatient(patientQueue);
          showMenu();
          break;
        case 3:
          printQueue(patientQueue);
          break;
        default:
          cout << "Invalid choice. The choice should be 1, 2, or 3. Enter a number: ";
      }
    }

  return 0;
}

/**
 * @brief Displays the main menu for the application.
 *
 * This function prints the main menu options to the console. The menu includes:
 * 1. Patient Check in
 * 2. Doctor takes a next patient
 * 3. End
 *
 * The menu is displayed with a separator line at the top for better readability.
 */
void showMenu()
{
  cout << "---------------------------------------------------" << endl;
  cout << "1: Patient Check in" << endl;
  cout << "2: Doctor takes a next patient" << endl;
  cout << "3: End" << endl;
  cout << "Enter a number: ";
}

/**
 * @brief Prompts the user to enter a number and validates the input.
 *
 * This function continuously prompts the user to enter a number until a valid integer is provided.
 * If the user enters an invalid input (non-integer), the function clears the error state and ignores
 * the remaining characters in the input buffer before prompting the user again.
 *
 * @return int The valid integer entered by the user.
 */
int getNum() 
{
  int num;  // user's choice
  while (true) {
      cin >> num;

      // Check if the input is a number
      if (cin.fail()) {
        
        // Clear the error state
        cout << "Your choice has to be a number. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
      }
      else {
        // Return the validated input
        return num;
      }
  }
}

void addPatient(int& patientCount, minHeap<int>& patientQueue) {
  
  // patient severity
  int severity;

  while(true) {
    cout << "Enter a severity, 1 most severe, .. 5 least severe: ";
    cin >> severity;

    if (cin.fail()) {
      cout << "Your choice has to be a number. ";
      cin.clear();
      cin.ignore(1000, '\n');
    }
    else if (severity < 1 || severity > 5) {
      cout << "Invalid choice. The choice should be 1, 2, 3, 4, or 5.";
      cin.clear();
      cin.ignore(1000, '\n');
      break;
    }
    else {
      break;
    }
  }

  // validate severity entered by user
  while (severity < 1 || severity > 5) {
    
    // get severity from user
    severity = getNum();
    if (severity < 1 || severity > 5) {
      cout << "Invalid choice. The choice should be 1, 2, 3, 4, or 5.";
    }
  }

  // create patient ID by concatenating severity and patient count and convert to int
  int patientId = stoi(to_string(severity) + to_string(patientCount++));
  patientQueue.insert(patientId);

  printQueue(patientQueue);
  
}

void nextPatient(minHeap<int>& patientQueue) {
  try {
    int patientId = patientQueue.getMin();
    cout << patientId << " is going to be treated now" << endl;
  }
  catch (const minHeap<int>::Underflow&) {
    cout << "The queue has none" << endl;
  }
}

void printQueue(const minHeap<int>& patientQueue) {
  cout << "The queue has " << patientQueue << endl;
}