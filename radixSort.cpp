/************************************
Template created by Kazumi Slott
CS311
Homework on radix sort

Description of this program: ?????
Your name: ?????
Your programmer number: ?????
Hours spent: ????
Any difficulties?: ?????
************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int LEN = 3; //the length of words
const int ALPHABET = 26; //total number of letters

class Node
{
  friend class LL;
private:
  string el;
  Node* next;
public:
  Node(const string& s){el = s; next = NULL;}
  string getElem() const {return el;}
};

class LL
{
private:
  Node* front;
  Node* rear;
  int num;
public:
  LL(){front = rear = NULL; num = 0;}
  ~LL();
  bool empty()const{return (front == NULL && rear == NULL && num == 0);}
  void addRear(const string& s);
  void addRear(Node* p);
  void append(const LL& other);
  Node* pop();
  void clear(){front = rear = NULL; num = 0;}
  Node* begin() const{return front;}
  Node* goToNext(Node* curr) const{return curr->next;}
  int size() const{return num;}

  class Underflow{}; //empty exception class 
};

LL::~LL()
{
  cout << "destructor is called" << endl;
  Node* p = front;
  while(!empty())
    {
      front = front->next;
      delete p;
      p = front;
      if(front == NULL)
	rear = NULL;
      num--;
    }
}

//add a new node at the end of this list. The element of the new node is s.
void LL::addRear(const string& s)
{
  //This function is just like what you made in LL class from CS211.
  Node* p = new Node(s); //the new node has NULL in the next field.

  if(empty())
    front = rear = p;
  else
    {
      rear->next = p;
      rear = rear->next;
    }    
  num++;
}

//Implement this function
//add the node pointed to by p (p points to the front node from the all list) at the end of this list
void LL::addRear(Node* p)
{
  //Don't make a new node.

  //You need a special case when the list is empty

  //don't forget to increment num

  //You should have NULL in the next field of the rear node of this list.

  //Note: this function should have complexity O(1). There is no loop required. 
}

//Implement this function
//appending another linked list (called "other" here) at the end of this linked list 
void LL::append(const LL& other)
{
  //Do you need to think about a special case?

  //Don't forget to update num of this list

  //Note: this function should have complexity O(1). There is no loop required. 
}

//removing the front node from the list and returning the pointer to it                                                          
Node* LL::pop()
{
  //If the list is empty, throw an exception                                                                            
 
  //remove the front node and return the pointer to it

  //Make sure front points to the new front node. 
  //Make sure you update num.
  //When the list becomes empty after the front node is popped, rear should become NULL.
}

void radixSort(LL& all);
void printLL(const LL& l);
void checkBuckets(const LL buckets[], int n);
void combineLists(/* ?????????? */);
void makeLL(LL& all);

int main()
{
  LL all; //holds all words
  makeLL(all); //all contains strings in the original order
  try
    {
      radixSort(all);//pop() could throw an exception
      cout << "Final result ----" << endl;
      printLL(all); //all contains strings in sorted sorter
      cout << endl;
    }
  catch(LL::Underflow)
    {
      cout << "Underflow" << endl;
    }
  return 0;
}

//Implement this function
//using the radix sort algorithm to sort strings that contain lowercase letters. 
void radixSort(LL& all)
{
  //Each slot of the buckets array is a LL object.
  //??? buckets[ALPHABET]; //bucket[0] is for 'a'. There are 26 buckets.   

  //checking each place
    //keep on popping the front node and add it to the end of the correct bucket depending on the letter at the current place
 
    //Once all the nodes of the all list are moved to the correct buckets, put them together by calling combineLists(). 


  //For debugging, checkBuckets() displays the contents of all the buckets
  //               printLL() displays all the elements in the list
}

//Implement this function
//combining the lists from the buckets into the all list
void combineLists(/* all list, buckets */)
{
  //populate the all list by combining the lists from the buckets by calling append()
  //reset each list object in buckets by calling clear(). All the nodes were moved to the all list already.
}

//Make a linked list of words from an input file  
void makeLL(LL& all)
{
  string s;  
  fstream fin;
  fin.open("radix.in");
  if(!fin)
    {
      cout << "The input file doesn't exist" << endl;
      exit(1); //quits the program if the input program doesn't exist.
    }

  fin >> s;
  while(fin)
    {
      all.addRear(s); //adding a new node with a new word
      fin >> s;
    }
}

//This function shows the contents of all the buckets
void checkBuckets(const LL buckets[], int n)
{
  for(int i = 0; i < n; i++)
    {
      cout << i << ": ";
      printLL(buckets[i]);
      cout << endl;
    }
}

//This function prints all the elements in l
void printLL(const LL& l)
{
  //iterate p from the first node to last node
  for (Node* p = l.begin(); p != NULL; p = l.goToNext(p))
    cout << p->getElem() << ' ';
}

