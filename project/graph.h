/****************************
Templated created by Kazumi Slott
CS311

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent: 
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
  friend class graph;   // Allows graph to access private members
  int neighbor;         // Adjacent vertex
  int wt;               // Weight of the edge

 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) : neighbor(u), wt(w) {}
  int getNeighbor() const { return neighbor; }
  int getWt() const { return wt; }
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
  int getNumVer() const ;            //returns the number of vertices
  list<edge*>* getVerAr() const;     //returns the adjacency list
};

//constructor: num is the number of vertices
graph::graph(int num) : num_ver(num) {
  // Allocate a dynamic array where each element is a list of pointers to edge objects
  ver_ar = new list<edge*>[num_ver];
}

graph::~graph() {
  for (int i = 0; i < num_ver; i++) {
    for (auto edgePtr : ver_ar[i]) {
      delete edgePtr; // Free memory allocated for each edge
    }
  }
  delete[] ver_ar; // Free the dynamic array of lists
}

//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w) {
  ver_ar[v].push_back(new edge(u, w)); // Dynamically allocate edge and add to adjacency list
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
void graph::DFT(int start) {
  int* num = new int[num_ver]();  // Array to track visitation order, initialized to 0
  queue<string> paths;        // Queue to store paths as strings

  int i = 0; // Visitation counter
  do {
    DFT_helper(start, i, num, paths); // Traverse from start
    start = nextUnvisitedNodes(num, start, start + 1); // Find next unvisited node
  } while (start != -1);

  displayQueue(paths); // Display all paths
  delete[] num;            // Clean up dynamic array
}


//I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertext we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.                                                                                            
//num is the array of vertices                                                                                                          
//start is the start vertex                                                                      
//s is the vertext right after the vertex we started last time                                                                          
int graph::nextUnvisitedNodes(int* num, int start, int s) {
    for (int i = s; i < num_ver; i++) {
        if (num[i] == 0) {
            return i;
        }
    }
    for (int i = 0; i < s; i++) {
        if (num[i] == 0) {
            return i;
        }
    }
    return -1; // All vertices visited
}

void graph::DFT_helper(int v, int& i, int* num, queue<string>& q) {
    // Mark the current vertex as visited
    num[v] = ++i;

    // Print the visited vertex
    cout << v << " ";

    // Iterate through the adjacency list of vertex v using an iterator
    for (auto it = ver_ar[v].begin(); it != ver_ar[v].end(); ++it) {
        // Check if the neighbor vertex has been visited
        if (num[(*it)->neighbor] == 0) {
            // Record the path "v->neighbor" into the queue
            q.push(to_string(v) + "->" + to_string((*it)->neighbor));

            // Recursively visit the neighbor
            DFT_helper((*it)->neighbor, i, num, q);
        }
    }
}

//start is the index for the start vertex
void graph::BFT(int start) {
    int* num = new int[num_ver]();  // Array to track visited vertices, initialized to 0
    queue<int> q;                   // Queue for breadth-first traversal
    queue<string> paths;            // Queue to store paths for display

    int i = 0; // Visitation counter

    do {
        if (num[start] == 0) {  // If the starting vertex hasn't been visited
            num[start] = ++i;   // Mark it as visited
            q.push(start);

            // Print the start vertex
            cout << start << " ";
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            // Iterate through all adjacent vertices of v
            for (auto edge_ptr : ver_ar[v]) {
                int neighbor = edge_ptr->neighbor;

                // If the neighbor hasn't been visited, visit it
                if (num[neighbor] == 0) {
                    num[neighbor] = ++i;
                    q.push(neighbor);

                    // Print the visited vertex
                    cout << neighbor << " ";

                    // Record the path "v->neighbor" for display
                    paths.push(to_string(v) + "->" + to_string(neighbor));
                }
            }
        }

        // Move to the next unvisited vertex (if any)
        start = nextUnvisitedNodes(num, start, start + 1);

    } while (start != -1);

    // Display all recorded paths
    displayQueue(paths);

    // Clean up the dynamic array
    delete[] num;
}

int graph::getNumVer() const {
  return num_ver;
}

list<edge*>* graph::getVerAr() const {
  return ver_ar;
}

#endif