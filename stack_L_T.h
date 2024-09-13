/***********************************
Template created by Kazumi Slott
CS311
Stack implemented with a LL

Your name here: JJ Hoffmann
Your programmer number here: 16
Hours spent: 1.5, I can't really say how long I spent on one section versus another since I did it all in a single shot
Any problems you had? Explain here: 
###### Don't forget to specify the complexity above each function. ######
******************************************************************************************************************/
#ifndef STACK_L_T_H
#define STACK_L_T_H

#include <iostream> 
using namespace std;

template < class T > //forward declaration needed so we can make stack class a friend of node
class Stack;

template < class T > //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const Stack<T>& s);


template < class T >
class Node{
  friend class Stack<T>; //Stack class accesses the private members of Node
  friend ostream& operator<< <T>(ostream& o, const Stack<T>& s); //operator<< accesses the private members of Node

 private:
  T elem; // elem is the value of the node and is of type T
  Node* next; // next is a pointer to the next node in the linked list

 public:
  Node(){
    next = NULL; // default constructor sets next to NULL
  } //default constructor

  Node(const T& e){
    elem = e; // constructor sets elem to e
    next = NULL; // constructor sets next to NULL
  } //You should set next to NULL too.
};

template <class T>
class Stack
{
  friend ostream& operator<< <T>(ostream& o, const Stack& s); //operator<< accesses the private members of Stack

  private:
    Node<T>* top; // top is a pointer to the top of the stack
 
 //helper functions - private because they won't be called from client
    // destroy() is a helper function that deletes all the nodes in the stack
    void destroy();

    // copy() is a helper function that makes a deep copy of the source stack
    void copy(const Stack& source);

 public:

    // default constructor
    Stack() {
      top = NULL; // default constructor sets top to NULL
    }
    // copy constructor
    Stack(const Stack& other);

    // destructor
    ~Stack();

    // operator=() is the assignment operator. It makes a deep copy of the right hand side object and assigns it to the left hand side object.
    Stack& operator=(const Stack& rhs); //rhs = right hand side of the operator   LHS_obj = RHS_obj
    
    // empty() returns true if the stack is empty, false otherwise
    bool empty() const{
      return top == NULL; // returns true if top is NULL, false otherwise
    } 

    // push() adds a new element to the top of the stack
    void push (const T& val);

    // pop() removes the top element from the stack
    void pop();

    // getTop() returns the top element of the stack
    T& getTop(); //Return type is T& so client can change the top value

    // getTop() returns the top element of the stack
    const T& getTop() const; //A const object needs to call a const member function

    // operator==() returns true if the two stacks have the same values, false otherwise
    bool operator==(const Stack& rhs); //rhs = right hand side of the operator
  
    // Exception class for underflow
    class Underflow{};
};

//-----------------------------------------------------------------------------------------------

//Complexity of this operation: O(1)
template <class T>

// push() adds a new element to the top of the stack
void Stack<T>::push(const T& val)
{
  Node<T>* newNode = new Node<T>(val); //create a new node
  newNode->next = top; //set the new node's next to the current top
  top = newNode; //set the top to the new node
}

//-----------------------------------------------------------------------------------------------

//Complexity of this operation: O(1)
template <class T>

// pop() removes the top element from the stack
void Stack<T>::pop()
{
  if(empty()) //check if the stack is empty
    throw Underflow(); //throw an exception if the stack is empty

  Node<T>* temp = top; //create a temporary node to hold the top
  top = top->next; //set the top to the next node
  delete temp; //delete the temporary node
}

//-----------------------------------------------------------------------------------------------

//Complexity of this operation: O(1)
template <class T>

// getTop() returns the top element of the stack (non-const version)
T& Stack<T>::getTop()
{
  if(empty()) //check if the stack is empty
    throw Underflow();

  return top->elem; //return the top element. Since the return type is T&, the client can change the top element.
}

//-----------------------------------------------------------------------------------------------

//Complexity of this operation: O(1)
template <class T>

// getTop() returns the top element of the stack (const version)
const T& Stack<T>::getTop() const
{
  if(empty()) //check if the stack is empty
    throw Underflow();

  return top->elem; //return the top element. Since the return type is const T&, the client cannot change the top element.
}

//-----------------------------------------------------------------------------------------------

//This function will show all the elements in the stack in the following format.
//cout << stackObj; <== This cout is calling the following function. same as operator<<(cout, stackObj); 
//Recall operator<< cannot be a member function because the LHS of the operator (<<) is not a stack object (it's cout, an ostream object). 
//     --- Top ---
//     2
//     1
//     --- Bottom ---

//Complexity of this operation: O(n)
template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //print from top to bottom.

  o << "--- Top ---" << endl;
  
  Node<T>* temp = s.top; //create a temporary node to hold the top
  while(temp != NULL) //loop through the stack
    {
      o << temp->elem << endl; //print the element
      temp = temp->next; //move to the next node
    }

  o << "--- Bottom ---" << endl;

  return o;
 
}

//-----------------------------------------------------------------------------------------------

template <class T>

// destructor
Stack<T>::~Stack()
{
  destroy(); 
}

//helper function - called from destructor and operator=
//Complexity of this operation: O(n)
template<class T>

// destroy() is a helper function that deletes all the nodes in the stack
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  while (!empty()) //loop through the stack
    {
      pop(); //pop the top element
    }
}

//-----------------------------------------------------------------------------------------------

//Complexity of this operation: O(n)
template <class T>

// Create a deep copy of a stack
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  // If this stack is not the same as rhs, then copy the elements from rhs to this stack, else return this stack
  if(this != &rhs) {
    destroy(); // Destroy any existing elemenets in the stack before copying the new elements
    copy(rhs); // Copy elements from rhs to this stack
  }
  return *this; //return the object 
}

//-----------------------------------------------------------------------------------------------

//Complexity of this operation: O(n)
//helper fuction. called from operator= and copy constructor
template <class T>

// copy() is a helper function that makes a deep copy of the source stack
void Stack<T>::copy(const Stack& source) //source is the stack object copied from. 
{
  Node<T>* temp = source.top; //create a temporary node to hold the top of the source stack
  Node<T>* last = NULL; //create a temporary node to hold the last node of the new stack

  while(temp != NULL) //loop through the source stack
    {
      Node<T>* newNode = new Node<T>(temp->elem); //create a new node with the same element as the source stack
      if(last == NULL) //check if the last node is NULL
        top = newNode; //set the top to the new node
      else
        last->next = newNode; //set the last node's next to the new node
      last = newNode; //set the last node to the new node
      temp = temp->next; //move to the next node
    }
}

//-----------------------------------------------------------------------------------------------


//Complexity of this operation: O(1)
//copy constructor
template <class T>
Stack<T>::Stack(const Stack& other)
{
  top = NULL; //initialize top to NULL
  copy(other); //copy the elements from the other stack
}

//-----------------------------------------------------------------------------------------------

//Complexity of this operation: O(1)
template <class T>
bool Stack<T>::operator==(const Stack& rhs) //rhs = right hand side of the operator
{
  //This function will return true if the two stacks have the same values. Otherwise, it returns false.
  Node<T>* temp1 = top; //create a temporary node to hold the top of the first stack
  Node<T>* temp2 = rhs.top; //create a temporary node to hold the top of the second stack

  while(temp1 != NULL && temp2 != NULL) //loop through the stacks
    {
      if(temp1->elem != temp2->elem) //check if the elements are not equal
        return false; //return false
      temp1 = temp1->next; //move to the next node
      temp2 = temp2->next; //move to the next node
    }

  if(temp1 == NULL && temp2 == NULL) //check if both stacks are empty
    return true; //return true
  else
    return false; //return false
}


#endif // end the definition here
