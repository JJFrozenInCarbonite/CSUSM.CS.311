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
#include <stack>
#include "minHeap.h"
#include "graph.h"
using namespace std;

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
void mySwap(vertex& v1, vertex& v2)
{
  //swap 2 vertices
  vertex temp = v1; // Store v1 in a temporary variable
  v1 = v2;          // Copy v2 into v1
  v2 = temp;        // Copy the temporary value into v2
  
  // Swap their locations in the locator array
  int tempLocator = locator[v1.vertexNum];
  locator[v1.vertexNum] = locator[v2.vertexNum];
  locator[v2.vertexNum] = tempLocator;
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
void showShortestDistance(const vector<vertex>& finalState, int start) {
    int dest;

    cout << "Enter the destination: ";
    cin >> dest;

    if (dest < 0 || dest >= finalState.size()) {
        cout << "Error: Invalid destination vertex." << endl;
        return;
    }

    const vertex& destVertex = finalState[dest];
    if (destVertex.curDist == 999) {
        cout << "Error: Destination vertex is not reachable from start." << endl;
        return;
    }

    // Trace the path from the destination to the start
    stack<int> path;
    int current = dest;

    while (current != -1) {
        path.push(current);
        current = finalState[current].predecessor;
    }

    // Display the path
    cout << "The shortest path from " << start << " to " << dest << " is: ";
    while (!path.empty()) {
        cout << path.top() << " ";
        path.pop();
    }
    cout << "\nThe distance is " << destVertex.curDist << endl;
}

//Dijkstra's shortest path algorithm - generating a table that contains the shortest distance from start to every other vertex and the predecessor of each vertex.
//g is a graph. We will pass the graph created in our client file.
//start is the start vertex.
void DijkstraShortestPath(const graph& g, int start) {
    int num_ver = g.getNumVer();

    if (start < 0 || start >= num_ver) {
        cerr << "Error: Invalid start vertex." << endl;
        return;
    }

    // Initialize the min-heap and locator array
    minHeap<vertex> heap(num_ver);
    vertex ver;

    locator = new int[num_ver];
    vector<vertex> finalState(num_ver); // Store the final state of each vertex

    for (int i = 0; i < num_ver; ++i) {
        ver.vertexNum = i;
        ver.curDist = 999;
        ver.predecessor = -1;

        heap.insert(ver);
        locator[i] = i;
    }

    // Initialize the start vertex
    ver.vertexNum = start;
    ver.curDist = 0;
    heap.updateElem(locator[start], ver);

    // Main loop of Dijkstra's algorithm
    while (!heap.isEmpty()) {
        vertex u = heap.getMin(); // Extract the vertex with the smallest distance

        // Save the vertex state
        finalState[u.vertexNum] = u;

        list<edge*> adjList = g.getVerAr()[u.vertexNum];
        for (const auto& edgePtr : adjList) {
            int v = edgePtr->getNeighbor();
            int weight = edgePtr->getWt();

            if (locator[v] != -1) { // Ensure the vertex is still in the heap
                vertex v_vertex = heap.getElem(locator[v]);

                // Relax the edge
                if (u.curDist + weight < v_vertex.curDist) {
                    v_vertex.curDist = u.curDist + weight;
                    v_vertex.predecessor = u.vertexNum;

                    heap.updateElem(locator[v], v_vertex);
                }
            }
        }

        // Mark vertex as processed
        locator[u.vertexNum] = -1;
    }

    // Use the saved state to display the shortest distance
    showShortestDistance(finalState, start);

    // Clean up the locator array
    delete[] locator;
    locator = nullptr;
}
