/******************************************************
Template prepared by Kazumi Slott
CS311
Emergency room program - application of priority queue

If you decide to use my getNum(), you need to compile your program as follows.
g++ -std=c++11 priorityQ.cpp //stoi requires to be compiled with c++11

Program description: This program simulates an emergency room management system using a priority queue. 
Patients are assigned a severity level upon check-in, with 1 being the most severe and 5 being the least severe. 
The program allows for adding patients to the queue and calling the next patient based on their severity. It 
uses a min-heap data structure to maintain the priority queue, ensuring that patients with higher severity are 
attended to first. The program also includes error handling to manage invalid inputs and underflow conditions 
when the queue is empty.

If you need any additional details or modifications, please let me know!
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
  while (true)
    {
      choice = getNum();
      switch (choice) {
        case 1:
          addPatient(patientCount, patientQueue);
          printQueue(patientQueue);
          showMenu();
          break;
        case 2:
          nextPatient(patientQueue);
          printQueue(patientQueue);
          showMenu();
          break;
        case 3:
          printQueue(patientQueue);
          return 0;
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
   string choice; //For example, when asking for 10, the user enters ab
   bool bad;
   int num;

   do {
    bad = false;
    cin >> choice;

    //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
    try {
      num = stoi(choice); 
    }
    //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer.
    catch(invalid_argument) {
      cout << "Your choice has to be a number. Enter a number: ";
      bad = true;
    }
  } while (bad == true);

  return num;
}
/**
 * @brief Adds a new patient to the queue.
 * 
 * This function prompts the user to enter the severity of the patient and adds the patient to the queue.
 * The severity is an integer between 1 and 5, where 1 is the most severe and 5 is the least severe.
 * The function generates a patient ID by concatenating the severity and the patient count and adds the patient
 * to the queue.
 * 
 * @param patientCount The monotonically increasing integer to be used as part of the patient ID.
 * @param patientQueue The minHeap to store the patient numbers.
 */
void addPatient(int& patientCount, minHeap<int>& patientQueue) {
  
  // patient severity
  int severity;

  while(true) {
    cout << "Enter a severity, 1 most severe, .. 5 least severe: ";
    severity = getNum();
    
    if (severity >= 1 && severity <= 5) {
     break;
    }
    else {
      cout << "Invalid choice. The choice should be 1, 2, 3, 4, or 5.";
    }
  }

  // create patient ID by concatenating severity and patient count and convert to int
  int patientId = stoi(to_string(severity) + to_string(patientCount++));
  patientQueue.insert(patientId);
}

/**
 * @brief Treats the next patient in the queue.
 * 
 * This function treats the next patient in the queue by removing the patient with the smallest ID from the queue.
 * If the queue is empty, the function prints a message indicating that the queue has no patients.
 * 
 * @param patientQueue The minHeap to store the patient numbers.
 */
void nextPatient(minHeap<int>& patientQueue) {
  try {
    int patientId = patientQueue.getMin();
    cout << patientId << " is going to be treated now" << endl;
  }
  catch (const minHeap<int>::Underflow&) {
    cout << "There are no patients waiting" << endl;
  }
}

/**
 * @brief Prints the current queue of patients.
 * 
 * This function prints the current queue of patients to the console.
 * 
 * @param patientQueue The minHeap to store the patient numbers.
 */
void printQueue(const minHeap<int>& patientQueue) {
  cout << "The queue has " << patientQueue << endl;
}