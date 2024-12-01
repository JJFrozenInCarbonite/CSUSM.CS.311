#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "minHeap.h"
#include "graph.h"

struct Vertex {
    int vertexIndex;        // The index of the vertex in the graph
    int currentDistance;    // The current shortest distance from start to the vertex
    int previousVertexIndex; // The predecessor along the shortest path to the vertex

    bool operator<(const Vertex& other) const {
        return currentDistance < other.currentDistance;
    }

    bool operator>(const Vertex& other) const {
        return currentDistance > other.currentDistance;
    }
};

/**********************************************************************************
What does the function do? Swaps two elements and their locations in the locator array
What does it return? N/A

Parameter 1: First element to swap
Parameter 2: Second element to swap
Parameter 3: Locator array
**********************************************************************************/
template <typename T>
void swap(T& v1, T& v2, int* locatorArray) {
    T temp = v1;    // Store v1 in a temporary variable
    v1 = v2;        // Copy v2 into v1
    v2 = temp;      // Copy the temporary value into v2

    // Swap their locations in the locator array
    int tempLocator = locatorArray[v1.vertexIndex];             // Store the locator of v1 in a temporary variable
    locatorArray[v1.vertexIndex] = locatorArray[v2.vertexIndex];// Copy the locator of v2 into the locator of v1
    locatorArray[v2.vertexIndex] = tempLocator;                 // Copy the temporary locator into the locator of v2
}

class Dijkstra {
public:

    /**********************************************************************************
    What does the function do? Dijkstra's algorithm to find the shortest path from a start 
    node to all other nodes in the graph.
    What does it return? N/A

    Parameter 1: Graph object
    Parameter 2: Start node index
    Parameter 3: Array to store the distances
    Parameter 4: Array to store the previous nodes
    **********************************************************************************/
    static void shortestPath(const Graph& graph, int start, int* distances, int* previous) {
        const int nodeCount = graph.getNodeCount(); // Get the number of nodes in the graph

        int* locatorArray = new int[nodeCount]; // Locator array for the heap
        bool* visited = new bool[nodeCount](); // Visited array to keep track of visited nodes
        MinHeap<Vertex> heap(nodeCount);  // Min-heap to store vertices

        // Initialize distances and heap
        for (int i = 0; i < nodeCount; ++i) {
            distances[i] = 999; // Infinity
            previous[i] = -1; // No predecessor
            locatorArray[i] = -1; // Not in heap
        }
        distances[start] = 0; // Start vertex has a distance of 0
        heap.insert(Vertex{start, 0, -1}, locatorArray); // Insert the start vertex into the heap

        // Dijkstra's algorithm
        while (!heap.isEmpty()) {
            Vertex current = heap.extractMin(locatorArray); // Extract the vertex with the smallest distance

            if (visited[current.vertexIndex]) continue; // Skip already-visited nodes
            visited[current.vertexIndex] = true; // Mark the current node as visited

            // Update distances for neighbors
            for (const Edge& edge : graph.getAdjacencyList()[current.vertexIndex]) {
                int neighborIndex = edge.destination; // Get the neighbor index
                int weight = edge.weight; // Get the edge weight
               
                if (visited[neighborIndex]) continue; // Skip nodes that have already been visited

                int newDistance = current.currentDistance + weight; // Calculate the new distance

                // Update the distance if the new distance is shorter
                if (newDistance < distances[neighborIndex]) {
                    distances[neighborIndex] = newDistance; // Update the distance
                    previous[neighborIndex] = current.vertexIndex; // Update the predecessor

                    // Insert or update the neighbor in the heap
                    if (locatorArray[neighborIndex] == -1) {

                        // Insert the neighbor into the heap
                        heap.insert(Vertex{neighborIndex, newDistance, current.vertexIndex}, locatorArray);
                    } else {

                        // Update the neighbor in the heap
                        heap.heapifyUp(locatorArray[neighborIndex], locatorArray);
                    }
                }
            }
        }

        // Clean up
        delete[] locatorArray;
        delete[] visited;
    }
};

#endif // DIJKSTRA_H