#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <stdexcept>

class Edge {
    public:
        int destination;
        int weight;
        Edge(int destination, int weight);
};

/**********************************************************************************
What does the function do? Constructor for the Edge class.
What does it return? Edge object

Parameter 1: Destination node as an integer
Parameter 2: Weight of the edge as an integer
**********************************************************************************/
Edge::Edge(int destination, int weight) {
    this->destination = destination; 
    this->weight = weight;  
};

class Graph {
    private: 
        int nodeCount;                  // Number of nodes in the graph
        std::list<Edge>* adjacencyList; // Array of adjacency lists
    public:
        Graph(int nodes);                                       // Constructor
        ~Graph();                                               // Destructor
        void addEdge(int source, int destination, int weight);  // Add an edge to the graph
        int getNodeCount() const;                               // Return the number of nodes
        const std::list<Edge>* getAdjacencyList() const;              // Return the adjacency list
};

/**********************************************************************************
What does the function do? Constructor for the Graph class.
What does it return? Graph object

Parameter 1: Number of nodes as an integer
**********************************************************************************/
Graph::Graph(int nodes) : nodeCount(nodes) {
    adjacencyList = new std::list<Edge>[nodeCount]; // Create an array of adjacency lists
}

/**********************************************************************************
What does the function do? Destructor for the Graph class.
What does it return? N/A

Parameter 1: N/A
**********************************************************************************/
Graph::~Graph() {
    delete[] adjacencyList; // Free the memory allocated for the adjacency list
}

/**********************************************************************************
What does the function do? Add an edge to the graph.
What does it return? N/A

Parameter 1: ID of the source node as an integer
Parameter 2: ID of the destination node as an integer
Parameter 3: Weight of the edge as an integer
**********************************************************************************/
void Graph::addEdge(int source, int destination, int weight) {
    if (weight < 0) {
        throw std::invalid_argument("Graph contains negative weight edges.");
    }

    adjacencyList[source].push_back(Edge(destination, weight)); // Add an edge to the adjacency list
    //adjacencyList[destination].push_back(Edge(source, weight)); // Add the reverse edge (for undirected graph)
}

/**********************************************************************************
What does the function do? Get the number of nodes in the graph.
What does it return? Number of nodes as an integer

Parameter 1: N/A
**********************************************************************************/
int Graph::getNodeCount() const{
    return nodeCount; // Return the number of nodes
}

/**********************************************************************************
What does the function do? Get the adjacency list of the graph.
What does it return? Adjacency list as a list of edges

Parameter 1: N/A
**********************************************************************************/
const std::list<Edge>* Graph::getAdjacencyList() const {
    return adjacencyList; // Return the adjacency list
}

#endif // GRAPH_H