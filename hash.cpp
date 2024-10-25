/************************
Templated created by Kazumi Slott
CS311

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent: ???
Any difficulties?: ??????
*********************/
#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <cstdlib>  
using namespace std;

//unsigned for positive numbers or zero only. long takes up 4 bytes. 0-2^32(4294967295)
unsigned long hashNum(const string& key);

class entry {
  private:
    string ID;
    string name;
    int age;
    double GPA;
    entry* next; //points to the next entry

  public:
    entry() { ID = name = "", age = -999, GPA = -999.0, next = NULL; }
    entry(const string& ID, const string& name, int age, double GPA ) { this->ID = ID, this->name = name, this->age = age, this->GPA = GPA, next = NULL; }
    string getID() const { return ID; }  
    string getName() const { return name; } 
    int getAge() const { return age; } 
    double getGPA() const { return GPA; } 
    entry* getNext() const { return next; } 

    // Declare hashTbl as a friend class
    friend class hashTbl;
};

class hashTbl {
  
  entry** table;   //table points to a dynamic array. Each slot points to an entry, which points to the next entry, ...
  int size; //size of the array
  public:
    hashTbl(int size);
    ~hashTbl();
    void put(entry* e); //add a new entry to the table
    entry* get(const string& key) const; //look up a key   
    entry remove(const string& key); //remove an entry
    entry** getTbl() const {return table;} //return the pointer to the table  
    class underflow //exception class - used when key wasn't found
    {
      string message;
      public:
        underflow(const string& mes) { message = mes; }
        string getMessage() { return message; }
    };
};

//constructor
//s is the size of the table
hashTbl::hashTbl(int s) : size(s) {

  // Allocate a dynamic array with s slots
  table = new entry*[size];
  
  // Initialize each slot to nullptr
  for (int i = 0; i < size; ++i) {
    table[i] = nullptr;
  }
}

//destructor
hashTbl::~hashTbl() {

  // Iterate through each slot in the table
  for (int i = 0; i < size; ++i) {
    entry* current = table[i];
    
    // Delete all entries in the linked list at this slot
    while (current != nullptr) {
      entry* toDelete = current;
      current = current->getNext();
      delete toDelete;
    }
  }
  // Delete the dynamic array itself
  delete[] table;
  table = nullptr;
}

//insert an entry to the table
//e is a pointer to an entry
void hashTbl::put(entry* e) {
  // This function is like LL::addFront() from CS211

  // string key = use ID for key 
  string key = e->getID();

  // int index = (call hashNum with key) % (table size); 
  int index = hashNum(key) % size;

  // Pointer to traverse the linked list
  entry* cur = table[index];
  
  // If the list is empty, add the new entry directly
  if (cur == nullptr) {
    table[index] = e;
    return;
  }

  // Traverse the list to check for duplicates and reach the end of the list
  entry* prev = nullptr;
  while (cur != nullptr) {

    // If a duplicate is found, update the existing entry's data
    if (cur->getID() == key) {
      cur->name = e->name;
      cur->age = e->age;
      cur->GPA = e->GPA;

      // Delete the new entry since it’s a duplicate
      delete e;
      return;
    }
    prev = cur;
    cur = cur->next;
  }

  // If no duplicate was found, add the new entry at the end of the list
  prev->next = e;
}

//look up key and return the pointer to it. Assume keys are unique.
entry* hashTbl::get(const string& key) const {
  
  // Compute the hash index
  int index = hashNum(key) % size;

  // Get the head of the linked list at the computed index
  entry* cur = table[index];

  // Check if the slot is empty
  if (cur == nullptr) {
    throw underflow(key);
  }

  // Traverse the linked list to find the entry with the matching key
  while (cur != nullptr) {
    if (cur->getID() == key) {
      return cur; // Entry found
    }
    cur = cur->getNext();
  }

  // If key wasn't found, throw exception
  throw underflow(key);
}

//remove the entry with key. Assume keys are unique.
entry hashTbl::remove(const string& key) {

  // Compute the hash index
  int index = hashNum(key) % size;

  // Get the head of the linked list at the computed index
  entry* cur = table[index];
  entry* prev = nullptr;

  // Check if the slot is empty
  if (cur == nullptr)
    throw underflow(key); // Throw exception if the list is empty

  // Traverse the linked list to find the entry with the matching key
  while (cur != nullptr) {
    if (cur->getID() == key) {

      // If the entry is the head of the list
      if (prev == nullptr) {
        table[index] = cur->getNext(); // Update the head of the list
      } else {
        prev->next = cur->getNext(); // Skip over the current entry
      }

      // Copy the entry to be removed
      entry removedEntry = *cur;

      // Delete the entry from the linked list
      delete cur;

      // Return the copied entry
      return removedEntry;
    }
    prev = cur;
    cur = cur->getNext();
  }

  // If key wasn't found, throw exception
  throw underflow(key);
}

//well known hash function called djb2
//http://www.cse.yorku.ca/~oz/hash.html
//For explanation of bit shifting, http://www.cplusplus.com/forum/beginner/95670/
//unsigned for positive numbers or zero only. long takes up 8 bytes (8 bytes * 8 bits = 64 bits). The range in decimal is 0 through 2^64 - 1(18446744073709551615)
unsigned long hashNum(const string& key) {
  const char* cstr = key.c_str(); //converting C++ string to c-string. A c-string is a character array that is terminated by a '\0' (NULL terminator).
  
  unsigned long hash = 5381;
  int c;

  //checking each character until it reaches '\0'. When it reaches '\0', c gets the ascii number of '\0', which is 0. 0 means false -> getting out of while.
  while (c = *cstr++) {
      hash = ((hash << 5) + hash) + c;//;
  }

  return hash;
}

void showInfo(const entry& e);
void showTable(const int count[], const hashTbl& students);

const int SIZE = 1009; //For closed addressing, you don't need to worry about load factor.                                                                    
                       //The table size still should be at least the number of items and also a prime number.                                                 
                       //There are 1000 people in the input file.
int main() {
  //make a hash table object called students with SIZE slots 
  hashTbl students(SIZE);

  int count[SIZE] = {0}; //set all slots to 0. Used to see count in each index
  ifstream fin;
  fin.open("hash.in");
  string id;
  string name;
  int age;
  double gpa;

  if(!fin) {
    cout << "The input file doesn't exist" << endl;
    return 0;
  }

  //adding entries from the input file
  fin >> id >> name >> age >> gpa;
  while(fin) {
    count[hashNum(id)%SIZE]++;//trying to see how many entries go into each slot
    students.put(new entry(id, name, age, gpa));
    fin >> id >> name >> age >> gpa;
  }

  fin.close(); // Close the input file stream

  //show the statistic about the table
  showTable(count, students);

  //put entries into the table
  students.put(new entry("T1234567891", "Tom", 23, 4.0));
  students.put(new entry("F5432112345", "Fred", 45, 3.5));
  students.put(new entry("L1357915987", "Linsey", 48, 2.0));

  //searches and returns students in table without removing                                                                     
  try {
    cout << "trying to search" << endl;
    showInfo(*(students.get("H1477530273")));//middle at index 64
    showInfo(*(students.get("L1779564660"))); //last entry at index 64                                                        
    showInfo(*(students.get("A1198453026"))); //first entry at index 64                                                         
    showInfo(*(students.get("A1234567891"))); //probably doesn't exist                                                        
    //search for key and show their info               
  }
  catch (hashTbl::underflow obj) {
    cout << "Student with ID: " << obj.getMessage() << " could not be found" << endl;
  }

  //Try to remove a student from table                                                                                         
  try {
      cout << "trying to remove" << endl;
      showInfo((students.remove("H1477530273"))); //3rd entry at index 64                                                        
      showInfo((students.remove("A1198453026"))); //first entry(now 4th) at index 64
      showInfo((students.remove("L1779564660"))); //last entry at index 64
      showInfo((students.remove("A1234567891"))); //probably it doesn't exist                                                    
  }
  catch (hashTbl::underflow obj) {
      cout << "Student with ID: " << obj.getMessage() << " could not be removed" << endl;
  }

  return 0;
}

//Show the information about an entry
void showInfo(const entry& e) {
  cout << e.getID() << " " << e.getName() << " " << e.getAge() << " " << e.getGPA() <<  endl;
}

//Show the statistic about the hash table
void showTable(const int count[], const hashTbl& students) {
  //we want to know the highest, lowest and empty counts
  int lowest = 1001;
  int highest = -1;
  int empty = 0;
  int hi_i; //index of the highest count

  cout << "print table" << endl;
  for(int i = 0; i < SIZE; i++) {
    if(count[i] < lowest)
      lowest = count[i];
    if(count[i] > highest) {
      highest = count[i];
      hi_i = i;
    }
    if(count[i] == 0)
      empty++;

      cout << setw(3) << count[i];
      if((i+1)%50 == 0)//Show 50 numbers per line
        cout << endl;
  }
  cout << endl << endl << "lowest is " << lowest << " highest is " << highest << " empty is " << empty << endl;

  cout << "highest count is at " << hi_i << endl;

  //Show the entries at the index that has the highest count
  entry* p = students.getTbl()[hi_i];
  while(p != NULL) {
    showInfo(*p);
    p = p->getNext();
  }
  cout << endl;
}