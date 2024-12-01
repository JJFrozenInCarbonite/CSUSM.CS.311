#define GF 2.0
#define LF 0.75

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "hashTable.h"
#include "dijkstra.h"
using namespace std;

struct city {
    int id;
    string code;
    string name;
    int population;
    int elevation;
};

struct road {
    int fromCity;
    int toCity;
    int distance;
};


/**********************************************************************************
What does the function do? Reads the data from the city.txt file into a hash table.
What does it return? Count of all the cities/nodes

Parameter 1: Reference to string that holds the file name
Parameter 2: Reference to a string vector to hold the city codes
Parameter 3: Reference to a hash table with the key being the city code and value being the ID
**********************************************************************************/
int readCityTxt(const string &filename, vector<string>& cc, HashTable<city> &cht) {

    int cityCount = 0; // Initialize the city count

    // Open the file
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file) {
        cout << filename << " not found" << endl;
        cout << "Program aborted." << endl;
        exit(1);
    }

    string line; // Create a string to hold each line of the file

    // Read the city data from the file
    while (getline(file, line)) {
        stringstream ss(line); // Create a stringstream from the line
        city c; // Create a city struct
        ss >> c.id >> c.code >> c.name >> c.population >> c.elevation; // Read the city data
        cht.put(c.code, c); // Add the city to the hash table
        cc.resize(cc.size() + 1); // Resize the vector to hold the city code
        cc[cityCount] = c.code; // Add the city code to the vector
        cityCount++; // Increment the city count
    }
    file.close(); // Close the file

    return cityCount; // Return the city count
}

/**********************************************************************************
What does the function do? Reads the data from the road.txt file into a graph.
What does it return? Count of all the roads/edges

Parameter 1: Reference to string that holds the file name
Parameter 2: Reference to a graph
**********************************************************************************/
int readRoadTxt(const string &filename, Graph& graph) {

    int roadCount = 0; // Initialize the road count 

    // Open the file
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file) {
        cout << filename << " not found" << endl;
        cout << "Program aborted." << endl;
        exit(1);
    }

    string line; // Create a string to hold each line of the file

    // Read the road data from the file
    while (getline(file, line)) {
        stringstream ss(line); // Create a stringstream from the line
        road r; // Create a road struct
        ss >> r.fromCity >> r.toCity >> r.distance; // Read the road data
        graph.addEdge(r.fromCity, r.toCity, r.distance); // Add the road to the graph
        roadCount++; // Increment the road count
    }
    file.close(); // Close the file

    return roadCount; // Return the road count
}

/**********************************************************************************
What does the function do? Converts the city code to city ID.
What does it return? City ID as an integer

Parameter 1: Reference to a hash table
Parameter 2: City code as a string
**********************************************************************************/
int getCityID(HashTable<city> &cht, string code) {

    // int to store the city ID
    int cityID;

    // Convert city code to city ID
    try {
        cityID = cht.get(code).id;
    } 
    // Catch exception if city code is not found
    catch (const std::out_of_range& e) {
        cout << "Invalid city code: " << code << endl;
        exit(1);
    } 
    
    return cityID;
}

/**********************************************************************************
What does the function do? Prints the city data.
What does it return? N/A

Parameter 1: Reference to a hash table
Parameter 2: City code as a string
**********************************************************************************/
void printCityData(HashTable<city> &cht, string cityCode) {
    city c = cht.get(cityCode);
    cout << c.name << ", population " << c.population << ", elevation " << c.elevation << endl;
}

/**********************************************************************************
What does the function do? Prints the program start information.
What does it return? N/A

Parameter 1: Reference to a hash table
Parameter 2: From city code as a string
Parameter 3: To city code as a string
**********************************************************************************/
void printProgramStart(HashTable<city> &cht, string from, string to) {
    
    string filename = "author.txt";

    // Read author.txt
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file) {
        cout << filename << " not found" << endl;
        cout << "Program aborted." << endl;
        exit(1);
    }

    string line; // Create a string to hold each line of the file

    // Print the author information
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close(); // Close the file

    // Print the from and to city data
    cout << "From City: ";
    printCityData(cht, from);
    cout << "To City: ";
    printCityData(cht, to);
}

/**********************************************************************************
What does the function do? Prints the shortest path information.
What does it return? N/A

Parameter 1: From city ID as an integer
Parameter 2: To city ID as an integer
Parameter 3: Reference to an integer array of distances
Parameter 4: Reference to an integer array of previous nodes
Parameter 5: Reference to a string vector of city codes
Parameter 6: Reference to a hash table
**********************************************************************************/
void printShortestPath(int fromID, int toID, int* distances, int* previous, vector<string> cc, HashTable<city> &cht) {

    // Print the shortest path information
    cout << "The shortest distance from " << cht.get(cc[fromID]).name << " to " << cht.get(cc[toID]).name << " is " << distances[toID] << endl;
    cout << "through the route: ";

    // Create a vector to store the route
    vector<int> route; 
    
    // Store the route in the vector
    int current = toID;
    while (current != -1) {
        route.push_back(current);
        current = previous[current];
    }
    // Print the route
    for (auto it = route.rbegin(); it != route.rend(); ++it) {
        cout << cht.get(cc[*it]).name;
        if (it + 1 != route.rend()) {
            cout << "->";
        }
    }
    cout << endl;
}

/**********************************************************************************
What does the function do? Main function
What does it return? 0

Parameter 1: Number of arguments
Parameter 2: Array of arguments
**********************************************************************************/
int main(int argc, char* argv[]) {

    if(argc != 3) {
        cout << "Run as follows:    ./a.out XX XX" << endl;
        cout << "XX is the two digit lettercode that represents a city" << endl;
        exit(1);
    }

    // Assign the arguments to variables
    string fromCityCode = argv[1];
    string toCityCode = argv[2];

    // Convert the city codes to uppercase
    transform(fromCityCode.begin(), fromCityCode.end(), fromCityCode.begin(), ::toupper);
    transform(toCityCode.begin(), toCityCode.end(), toCityCode.begin(), ::toupper);

    vector<string> cityCode;

    int nodeCount; // Initialize the city count
    int edgeCount; // Initialize the road count
    
    // Initialize hash table to store city data
    HashTable<city> cityHashTable(29, GF, LF); 

    // Read city data from city.txt and store the number of cities
    nodeCount = readCityTxt("city.txt", cityCode, cityHashTable);

    // Initialize graph to store road data using the number of cities
    Graph graph(nodeCount); 

    // Read road data from road.txt and store the number of roads
    edgeCount = readRoadTxt("road.txt", graph);

    // Convert city codes to city IDs
    int fromID = getCityID(cityHashTable, fromCityCode); 
    int toID = getCityID(cityHashTable, toCityCode);

    // Print the program start information
    printProgramStart(cityHashTable, fromCityCode, toCityCode);

    // Array to store distances and predecessors
    int* distances = new int[nodeCount];
    int* previous = new int[nodeCount];

    // Dijkstra!!!
    Dijkstra::shortestPath(graph, fromID, distances, previous);

    // If there is no route
    if (distances[toID] == 999) {
        cout << "No route from " << cityHashTable.get(fromCityCode).name << " to " << cityHashTable.get(toCityCode).name << endl;
        exit(1);
    }

    // Print the shortest path
    printShortestPath(fromID, toID, distances, previous, cityCode, cityHashTable);

    // Clean up
    delete[] distances;
    delete[] previous;

    return 0;
}