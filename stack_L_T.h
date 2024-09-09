/***********************************
Template created by Kazumi Slott
CS311
Stack implemented with a LL

Your name here: JJ Hoffmann
Your programmer number here: 16
Hours spent: .75
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

/*
//Complexity of this operation: O(?????)
template <class T>
void Stack<T>::push(const T& val)
{
   //FYI, I have 3 lines of code here. You may have less or more.
   //To make a new Node when the Node class is a template class, check insertNode() in /cs/slott/cs211/BST_T.h 
}
*/

/*
//Complexity of this operation: O(?????)
template <class T>
void Stack<T>::pop()
{
  //throw an exception if the stack is empty. (You shouldn't call pop if the stack is empty.)

}
*/

/*
//Complexity of this operation: O(?????)
template <class T>
T& Stack<T>::getTop()
{
  //thrown an exception if the stack is empty. You shouldn't call getTop if empty.
  return ?????? //return the top element. Since the return type is T&, the client can change the top element.
}
*/

/*
//Complexity of this operation: O(?????)
template <class T>
const T& Stack<T>::getTop() const
{
  //thrown an exception if the stack is empty. You shouldn't call getTop if empty.
  return ?????? // same as the getTop() above. We need to provide this so a const object can call getTop(). Recall a const object can only call const member functions.
}
*/


/*
//This function will show all the elements in the stack in the following format.
//cout << stackObj; <== This cout is calling the following function. same as operator<<(cout, stackObj); 
//Recall operator<< cannot be a member function because the LHS of the operator (<<) is not a stack object (it's cout, an ostream object). 
//     --- Top ---
//     2
//     1
//     --- Bottom ---

//Complexity of this operation: O(?????)
template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //print from top to bottom.

  o << "--- Top ---" << endl;


  o << "--- Bottom ---" << endl;
 
}
*/


template <class T>
Stack<T>::~Stack()
{
  destroy(); 
}

//helper function - called from destructor and operator=
//Complexity of this operation: O(?????)
template<class T>
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  //destroy all nodes
  //?????????????? 
}

/*
//Complexity of this operation: O(?????)
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  //good reading from cal tech
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
  //Notice that the returned reference is not declared const (Stack<T>&). 
  //This can be a bit confusing, because it allows you to write crazy stuff like this: (s1 = s2) = s3;


  //deep copy
  if(???????) //Check the addresses of the left and right objects. If they are the same, you are trying to assign the same object   s = s;
              //You copy only if the left object is not the same as the right object.
    {
      //destroy any memory space "this" is using. "this" may have elements already. call destroy
      //call copy
    }
  return ???????; //return the "this" object (not the address of the "this" object). Notice the return type is not void. 
                  //By returning the this object, we can use multiple assignment operators. 
                  //s1 = s2 = s3; same as s1 = s2.operator=(s3);  Now you can see why operator=() needs to return the this object (s2). 
}
*/

/*
//Complexity of this operation: O(?????)
//helper fuction. called from operator= and copy constructor
template <class T>
void Stack<T>::copy(const Stack& source) //source is the stack object copied from. 
{
  //"this" object ends up having the same values from source
  //Make sure this function won't crush when the source stack is empty. If the source stack is empty, "this" stack is also empty 
  //The complexity of this function should be O(n). If you implement this function by calling push(), the complexity will probably be O(n^2).
  //Make this function without calling push().
}
*/

/*
//Complexity of this operation: O(?????)
//copy constructor
template <class T>
Stack<T>::Stack(const Stack& other)
{
  //This is a copy constructor. This new object will get the same values as the other object. 
  //You still need to initialize the data member, top.
  ???????

  //Then you can call the copy function
}
*/

/*
//Complexity of this operation: O(?????)
template <class T>
??? Stack<T>::operator==(??????)
{
  //This function will return true if the two linked lists have the same values. Otherwise, it returns false.
}
*/

#endif // end the definition here
