/****************************
Templated created by Kazumi Slott
CS311

Your name: ???
Your programmer number: ???
Hours spent: ???
Any difficulties?:
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
using namespace std;

class edge
{
  //????????????;  //What do you need here if you want to access the private members of edge class from graph class
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) {/* set data members */};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       //Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, queue<string>& q);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  //make a dynamic array with num slots where each slot holds a list object. 
  //The element of a node in the linked list is a pointer to an edge object 
}

graph::~graph()
{
  //destroy all the edge objects created in heap                                                                                                        
  //For each vertex in ver_ar
  //    go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.  

  //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
  //https://www.cplusplus.com/reference/list/list/~list/

  //destroy the ver_ar dynamic array
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  //I have one line of code in this function.
}

//I decided to make this function a stand alone function. It doesn't have anything to do with the graph class.                                
template<class T>
void displayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
}

//start Traversal at start
void graph::DFT(int start)
{
  //The algorithm is in my lecture notes.
  //I made dynamic array called "num"
  //I created a queue object of string data type from the library's queue class to save all the paths.

  //I used do-while
  //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.


  //You could call displayQueue() implemented above to display all the paths. 

  //Don't forget to destroy the dynamic array
}

//I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertext we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.                                                                                            
//num is the array of vertices                                                                                                          
//start is the start vertex                                                                      
//s is the vertext right after the vertex we started last time                                                                          
int graph::nextUnvisitedNodes(int* num, int start, int s)
{
  //go through the num array from s to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
  //don't start from index 0!
  //Althought this function may be called multiple times because there may be multiple disconnected graphs, we are checking each vertex only once.
}

void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
  //The algorithm is in my lecture notes

  //The following shows how to iterate the library's linked list. You use an iterator.
  //https://www.cplusplus.com/reference/list/list/end/ 
  //iterator class is nested inside list class
  for (list<??????>::iterator u = ???????.begin(); u != ??????.end(); u++)
    {
      //From the example on https://www.cplusplus.com/reference/list/list/end/
      //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
      //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.  

      //push each path e.g. 0->1 into q. to_string(int) converts int to string. 
      //to_string() is in c++11, so compile with the option. g++ -std=c++11 graphClient.cpp 
      q.push(to_string(v) + "->" + to_string((*u)->neighbor));
      
    }

  /***********************************************************************************************
   **********************************************************************************************
    Compile with a c++11 option if you are using to_string()
        g++ -std=c++11 graphClient.cpp 
   **********************************************************************************************
   ***********************************************************************************************/
}

//start is the index for the start vertex
void graph::BFT(int start)
{
  //The algorithm is in my lecture notes

  //Use the queue class from the library
  queue<int> q;
  //I used another queue of strings to save all the paths. 

  //I used do-while to visit all unconnected graphs. Call nextUnvisitedNodes() to check to see if there are more unvisited vertices.

  //Check the specification to figure out what member functions of the queue class you need to use.
  // https://www.cplusplus.com/reference/queue/queue/

  //You could call show all paths by calling displayQueue()                                                                     

  //Don't forget to destroy the dynamic array if you used one
}

#endif
