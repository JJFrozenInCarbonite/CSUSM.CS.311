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

class edge {
  friend class graph; // Allows the graph class to access private members of edge
  int neighbor;       // Adjacent vertex
  int wt;             // Weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) { neighbor = u; wt = w; };
  int getNeighbor() const { return neighbor; }
  int getWt() const { return wt; }
};

class graph {
  int num_ver; // Total number of vertices in the graph
  std::list<edge*>* ver_ar; // Pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       // Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, std::queue<std::string>& q);
  public:
    graph(int V);
    ~graph();
    void addEdge(int v, int u, int w = 1);  //If the weight is not given, 1 is used for wt.
    void BFT(int start);
    void DFT(int start);
    int getNumVer() const;                  // Returns the number of vertices
    std::list<edge*>* getVerAr() const;     // Returns the adjacency list
};

// Constructor: num is the number of vertices
graph::graph(int num) : num_ver(num){

  // Allocate a dynamic array of lists, each holding pointers to edge objects
  ver_ar = new list<edge*>[num_ver];
}

// Destructor for the graph class
graph::~graph() {

  // Iterate over each vertex's adjacency list
  for (int i = 0; i < num_ver; ++i) {

    // For each edge pointer in the list, delete the edge object
    for (auto edge_ptr : ver_ar[i]) {
      delete edge_ptr;
    }
  }

  // Delete the dynamic array of lists
  delete[] ver_ar;
}

// Add an edge between vertices v and u with weight w
void graph::addEdge(int v, int u, int w) {
  
  // Add a new edge to the adjacency list of vertex v
  ver_ar[v].push_back(new edge(u, w));
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

// Start is the index for the start vertex
void graph::DFT(int start) {

  // Dynamic array to track visited vertices
  int* num = new int[num_ver]();

  // Queue to store paths for display
  std::queue<string> paths;

  // Start the DFT traversal from the given start vertex
  int i = 0;
  DFT_helper(start, i, num, paths);

  // Visit any disconnected components using do-while
  int next;
  do {
    next = nextUnvisitedNodes(num, start, start + 1);
    if (next != -1) {
      DFT_helper(next, i, num, paths);
    }
  } while (next != -1);

  // Display all paths found during traversal
  displayQueue(paths);

  // Clean up the dynamic array
  delete[] num;
}

// Find the next unvisited vertex in the graph
int graph::nextUnvisitedNodes(int* num, int start, int s) {

  // Loop from s to the end of the vertices
  for (int i = s; i < num_ver; ++i) {
    if (num[i] == 0) { // If the vertex is unvisited
      return i; // Return the index of the first unvisited vertex
    }
  }

  // If no unvisited vertex is found from s to the end, loop from the beginning to start
  for (int i = 0; i < start; ++i) {
    if (num[i] == 0) { // If the vertex is unvisited
      return i; // Return the index of the first unvisited vertex
    }
  }

  // If all vertices are visited, return -1
  return -1;
}

// Recursive helper function for DFT traversal
void graph::DFT_helper(int v, int& i, int* num, queue<string>& q) {

  // Mark the current vertex as visited
  num[v] = ++i;

  // Print the vertex as it's visited
  cout << v << " ";

  // Iterate through the adjacency list of vertex v using an iterator
  for (list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); ++u) {
    
    // Check if the neighbor vertex has been visited
    if (num[(*u)->neighbor] == 0) {

      // Push the path "v->neighbor" into the queue
      q.push(std::to_string(v) + "->" + std::to_string((*u)->neighbor));

      // Recursively visit the neighbor
      DFT_helper((*u)->neighbor, i, num, q);
    }
  }
}

//start is the index for the start vertex
void graph::BFT(int start) {

  // Dynamic array to track visited vertices
  int* num = new int[num_ver]();

  // Queue for breadth-first traversal
  std::queue<int> q;

  // Queue to store paths for display
  std::queue<std::string> paths;

  // Initialize the traversal by marking the start vertex as visited and adding it to the queue
  int i = 1;
  num[start] = i;
  q.push(start);
  
  // Display the start vertex
  std::cout << start << " ";

  // Perform the BFS
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
            std::cout << neighbor << " ";

        // Record the path "v->neighbor" for display
        paths.push(to_string(v) + "->" + to_string(neighbor));
      }
    }
  }

  // Visit any remaining disconnected components using do-while loop
  int next;
  do {
    next = nextUnvisitedNodes(num, start, start + 1);
    if (next != -1) {
      num[next] = ++i;
      q.push(next);

      // Print the next component's start vertex
      std::cout << next << " ";

      // Continue BFS for the disconnected component
      while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto edge_ptr : ver_ar[v]) {
          int neighbor = edge_ptr->neighbor;

          if (num[neighbor] == 0) {
            num[neighbor] = ++i;
            q.push(neighbor);

            // Print the visited vertex
            std::cout << neighbor << " ";

            // Record the path "v->neighbor" for display
            paths.push(to_string(v) + "->" + to_string(neighbor));
          }
        }
      }
    }
  } while (next != -1);

  // Display all recorded paths
  displayQueue(paths);

  // Clean up the dynamic array
  delete[] num;
}

int graph::getNumVer() const {
    return num_ver;  // Returns the number of vertices
}

std::list<edge*>* graph::getVerAr() const {
    return ver_ar;  // Returns the adjacency list
}


#endif
