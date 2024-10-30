/****************
Template created by Kazumi Slott
CS311

Your name: ???????
Your programmer number: ?????
Hours spent?: ???
Any difficulties?: ??????
*****************/

#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
//?????
//?????

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

//???????????  //make it a templare class
class Node
{
  //??????? BST<T>; //BST wants to access private members of Node
private:
  //???? el;
  Node* right;
  Node* left;
public:
  Node() {right = left = NULL;}; //default constructor. set right and left to NULL
  Node(const T& e){/*????? What do you do here?*/}; 
  T getEl() const {return el;} //returns el
};

//Make it a template class
class BST
{
private:
  //???? root; //check stack_L_T.h to see how to declare top

  //You will need 10 private functions here.  WHY private?


 public:
  BST() {/* ????? */} //implement constructor here
  ~BST(); 
  void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  int getMaxLength();
  int getMinLength();
  int getNumNodes();
  int getEvenNodes();
  Node<T>* searchI(const T& e);
  //?????? searchR(const T& e);  //You need to make this function too.
  void BFTprint();
  void DFTprint();
};

//implement the member functions in the header if you are making a template class

/*
//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

???????? 
?????::~BST()
{
  destroy(?????);
}

???????
???? ????::destroy(?????) //private function. WHY?
{
  //destroy all nodes
}
*/

/*
//If you don't know how to make the insert function using recursion, check the following.
//CS211 Lecture Notes on BST – insertNode
//CS211 Lecture recording - Lecture 4/26(Mon) - DLL::deleteFront, BST::insert(), search()

??????
????  ?????::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

???????
void ?????::insertNodeR(?????? p, const T& e) //private function. WHY?
{

}
*/

/*
//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
//The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
template <class T>
void BST<T>::insertNodeI(const T& e)
{
  ???? newNode = make a new node.  Check stack_L_T.h to see how you made a new node.
  ???? p = root;
  ???? parent = NULL; //points to the parent of p. 

  //move p to NULL
  while(p != NULL)
    {
      //parent points to the parent node while p points to the left or right child.
      parent = p; 
      if(e < ?????) 
	p = ????? 
      else //p->el <= e
	p = ?????;
    }

  if(parent == NULL) //tree is empty
    root = newNode;
  else if(e < parent->el) //insert a child as the parent's left child
    ????->left = ????;
  else //parent->el <= e //insert a child as the parent's left child
    ????->right = ????;
}
*/

/*
//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void BST<T>::inOrderPrint()
{

}

template <class T> //private function. WHY?
void BST<T>::inOrderPrint(?????)
{

}
*/

/*
template <class T>
void BST<T>::preOrderPrint()
{
  //pre means print parent->left child ->right child
}

template <class T>
void BST<T>::preOrderPrint(??????) //private function. WHY?
{

}
*/

/*
template <class T>
void BST<T>::postOrderPrint()
{
  //post means left->right->parent last
}

template <class T>
void BST<T>::postOrderPrint(?????) //private function. WHY?
{

}
*/

/*
//If you don't know how to make this, check the following
//Lec Notes on BST :: Recursive Functions – getNumNodes
//CS211 Lecture recording - Lecture 4/30(Fri) - BST::getNumNodes, phase 3 of college

template <class T>
int BST<T>::getNumNodes()
{
  
}

template <class T>
int BST<T>::getNumNodes(??????) //private function WHY?
{

}
*/

/*
//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int BST<T>::getMaxLength()
{

}

template <class T>
int BST<T>::getMaxLength(???????) //private function. Why?
{

}
*/

/*
template <class T>
int BST<T>::getMinLength()
{
  
}

template <class T>
int BST<T>::getMinLength(?????) //private function. WHY?
{
   //Read the info in the homework document.
   If p is NULL, return 0
   If there is no right child
      use the min length in the left subtree + 1
   If there is no left child
      use the min length in the right subtree + 1
   If there are 2 children
      check the lengths from the left and right subtrees and use whichever smaller + 1
}
*/

/*                                                                                                    
//This function will return the number of even elements
template <class T>                                                                                    
int BST<T>::getEvenNodes()                                                                            
{                                                                                                     
                                                                                                      
}                                                                                                     
                                                                                                      
template <class T>                                                                                    
int BST<T>::getEvenNodes(?????) //private function. WHY?                                              
{                                                                                                     
                                                                                                      
}                                                                                                     
*/


/*
//Make a search function using iteration. Return the pointer to the node having e
//return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchI(??????)
{
  ???? p = root;

  while(p ??  ????)
    {
    ??????
    }

  Where do you return NULL?  

}
*/

/*
//Make a search function using recursion.
//Return the pointer to the node having e or return NULL if e is not found.
template <class T>
?????? BST<T>::searchR(??????)
{

}

template <class T>
????? BST<T>::searchR(????? p, const T& e) //private function. WHY?
{

}
*/

/*
template <class T>
void BST<T>::BFTprint()  //Breadth First Traversal Print
{
  //Use the library's queue. https://cplusplus.com/reference/queue/queue/

  //Make sure to include <queue> at the top
  //create a queue obj of POINTERS to Nodes

  //algorithm is discussed in lecture

  //NOTICE
  //front() gives you the front element but it doesn't remove it from the queue.
  //pop() removes the front element
}
*/

/*
template <class T>
void BST<T>::DFTprint()  //Depth First Traversal Print
{
  //Use the library's stack class. https://cplusplus.com/reference/stack/stack/

  //Make sure to include <stack> at the top
  //create a stack of POINTERS to Nodes

  //top() will give you the top element but it will not remove it from the stack.
  //pop() removes the top element.
}
*/

#endif
