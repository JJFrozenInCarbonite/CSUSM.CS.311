/*****************************************************
Kazumi Slott
CS311
Homework on Dijkstra's algorithm

4-19-2024

This file contains code used for Dijkstra's algorithm.
This implementation is least invasive to the graph and min heap classes.

Min heap has a struct. In min heap class, maintain the property
using distance by operator overloaded func.
******************************************************/
#include <iostream>
using namespace std;
#include "minHeap.h"  // include your min heap class. It will be used in Dijkstra's algorithm
#include "graph.h"    // include  your graph class. You will pass a graph to Dijkstra's algorithm
#include <stack>      //for stack

//Each vertex has a vertex number, current shortest distance and predecessor
struct vertex
{
  int vertexNum; //the vertex number
  int curDist; //the current shortest distance from start to the vertex 
  int predecessor; //the predecessor along the shortest path to the vertex
};

int* locator; ///tells where each vertex exists within the heap. The dynamic array pointed to by this pointer will be created inside dijkstraSHortestPath() down below
//e.g. vertex numbers in heap[3, 1, 2, 4, 0] vertex 3 is at the root because its curDist is the smallest
//     locator should look like this [4, 1, 2, 0, 3] vertex 3 can be found at 0. vertex 0 can be found at 4 in heap
//This is a global variable (sounds terrible), but that is ok for this application. The reason why it is declared global is that it is accessed from mySwap() down below. mySwap() is called from the min heap class. We are not passing locator to the min heap class.


//this will be called from the min heap class. Each element in the heap is a vertex which consists of vertexNum, curDist and predecessor.
//The heap is maintained by curDist. 
bool operator<(const vertex& v1, const vertex& v2)
{
  //compare the curDistances of v1 and v2
  return v1.curDist < v2.curDist;
}

//this will be called from the min heap class
bool operator>(const vertex& v1, const vertex& v2)
{
  //compare the curDistances of v1 and v2
  return v1.curDist > v2.curDist;
}

//If you are comparing 2 elements using >= or <= in your min heap class, you will need to make those operator overloaded functions as well.

//this will be called from your min heap class.
template <typename T>
void mySwap(T& a, T& b, int* locator, int indexA, int indexB) {
    // Swap the elements
    T temp = a;
    a = b;
    b = temp;

    // Update their positions in the locator array
    int tempLoc = locator[indexA];
    locator[indexA] = locator[indexB];
    locator[indexB] = tempLoc;
}

//This will be called from printHeapArrays() down below. printHeapArrays() should be used for debugging your code. 
ostream& operator<<(ostream& o, const vertex& v)
{
  //output the 3 values of the vertex, v.  You could Output them in this format [vertexNum, curDist, predecessor]
  o << "[" << v.vertexNum << ", " << v.curDist << ", " << v.predecessor << "]";
  return o;
}

//print the min heap and locator array for debugging
//num_ver is the total number of vertces.
void printHeapArrays(const minHeap<vertex>& h, const int* locator, int num_ver)
{
  //This functions is complete. 
  cout << "----- heap ------" << endl;
  cout << h << endl; //operator<<() in min heap class is called here, which calls operator<<(ostream, vertex) above

  cout << "----- locator ------" << endl;
  for(int i = 0; i < num_ver; i++)                                                                                          
    cout << locator[i] << " ";                                                                                               
  cout << endl;
}

//This function will show the path from stat to destination
//MH is the min heap which contains the vertexNum, curDist and precessor of all the vertices created by Dijkstra's algorithm
//start is the start vertex. Dijkstra's algorithm calculated the shortest distance from start to every other vertex
//This function shows the shortest path from start to destination in the following format.
//  The shortest path from 3 to 5 is 3 0 4 5
//  The distance is 8
void showShortestDistance(const minHeap<vertex>& MH, int start)
{
  int dest;

  cout << "Enter the destination: ";
  cin >> dest;

  // Use a stack to trace back the shortest path
  stack<int> path;
  int current = dest;

  while (current != -1) { // Trace back to the start
      path.push(current);
      current = MH.getElem(locator[current]).predecessor;
  }

  cout << "The shortest path from " << start << " to " << dest << " is ";
  while (!path.empty()) {
      cout << path.top() << " ";
      path.pop();
  }

  // Display the distance to the destination
  cout << "\nThe distance is " << MH.getElem(locator[dest]).curDist << endl;
}

//Dijkstra's shortest path algorithm - generating a table that contains the shortest distance from start to every other vertex and the predecessor of each vertex.
//g is a graph. We will pass the graph created in our client file.
//start is the start vertex.
void DijkstraShortestPath(const graph& g, int start) {
  int numVer = g.getNumVer();
  if (numVer == 0) {
    cout << "Graph is empty." << endl;
    return;
  }

  // Create a minHeap of vertices
  minHeap<vertex> MH(numVer);

  // Populate the heap with all vertices
  vertex ver;
  for (int i = 0; i < numVer; i++) {
    ver.vertexNum = i;
    ver.curDist = 999; // Infinity
    ver.predecessor = -1;
    MH.insert(ver);
  }

  // Create and initialize the locator array
  locator = new int[numVer];
  for (int i = 0; i < numVer; i++) {
    locator[i] = i;
  }

  // Update the start vertex to have a distance of 0
  ver.vertexNum = start;
  ver.curDist = 0;
  ver.predecessor = -1;
  MH.updateElem(locator[start], ver);

  // Dijkstra's algorithm
  while (MH.getNum() > 0) {
    vertex current = MH.getMin();

    // Access the neighbors of the current vertex
    for (auto edge : *(g.getVerAr() + current.vertexNum)) {
      int neighbor = edge->getNeighbor();
      int weight = edge->getWt();

      // Calculate new distance
      int newDist = current.curDist + weight;

      // Relaxation step
      if (newDist < MH.getElem(locator[neighbor]).curDist) {
        vertex updated = MH.getElem(locator[neighbor]);
        updated.curDist = newDist;
        updated.predecessor = current.vertexNum;
        MH.updateElem(locator[neighbor], updated);
      }
      }

  // Display the shortest path from the start to a user-specified destination
  showShortestDistance(MH, start);

  // Cleanup
  delete[] locator;
  locator = nullptr;
}