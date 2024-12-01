#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list>
#include <stdexcept> 
#include <string>

template<typename T>
struct entry {
    std::string key;
    T value;

    entry(const std::string& key, const T& value) : key(key), value(value) {}
};

template<typename T>
class HashTable {
    public:
        HashTable(size_t size, double growthFactor, double loadFactor); // Constructor
        ~HashTable(); // Destructor

        T get(const std::string& key) const; // Get the value of the key
        void put(const std::string& key, const T& value); // Insert a key-value pair
        
    private:
        size_t hash(const std::string& key, size_t size) const; // Hash function
        std::list<entry<T>>* table; // Dynamically allocated array of lists.
        double growthFactor; // Growth factor for resizing
        double loadFactor; // Load factor for resizing
        size_t keyCount; // Number of keys in the table
        size_t tableSize; // Size of the table
        void resize(); // Resize the table
};

/*********************************************************************************
What does the function do? hashTable constructor
What does it return? 
Paramenter 1: Initial size of the hash table
Parameter 2: Loadfactor threshold for resizing table
**********************************************************************************/
template<typename T>
HashTable<T>::HashTable(size_t size, double growthFactor, double loadFactor)
    : growthFactor(growthFactor), loadFactor(loadFactor), tableSize(size), keyCount(0) {
    table = new std::list<entry<T>>[tableSize];
}

/**********************************************************************************
What does the function do? Destructor
What does it return? N/A
Parameter 1: N/A
**********************************************************************************/
template<typename T>
HashTable<T>::~HashTable() {
    delete[] table;
}

/**********************************************************************************
What does the function do? Hash function to compute the index of the key
What does it return? Index of the key
Parameter 1: String to be hashed
**********************************************************************************/
template<typename T>
size_t HashTable<T>::hash(const std::string& key, size_t size) const {

    // Initialize the hash value
    size_t hash = 5381;
    
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    
    // Return the hash index
    return hash % size;
}

/**********************************************************************************
What does the function do? Put the key-value pair in the hash table
What does it return? N/A
Parameter 1: Key to be inserted
Parameter 2: Value to be inserted
**********************************************************************************/
template<typename T>
void HashTable<T>::put(const std::string& key, const T& value) {

    // Check if the table needs to be resized
    if (keyCount >= loadFactor * tableSize) {
        resize();
    }

    // Compute the hash index
    size_t index = hash(key, tableSize);

    // If key already exists, overwrite value and return
    for (auto& pair : table[index]) {
        if (pair.key == key) {
            pair.value = value;
            return;
        }
    }

    // Insert the key-value pair, if not overwritten

    table[index].push_back(entry{key, value});

    // Increase the table size
    ++keyCount;
}


/**********************************************************************************
What does the function do? Resizes the hash table
What does it return? N/A
Parameter 1: N/A
**********************************************************************************/
template<typename T>
void HashTable<T>::resize() {

    // Compute the new table size
    size_t newSize = tableSize * growthFactor;
    auto* newTable = new std::list<entry<T>>[newSize];

    // Rehash all the key-value pairs and insert into new table
    for (size_t i = 0; i < tableSize; ++i) {
        for (const auto& pair : table[i]) {
            size_t index = hash(pair.key, newSize);
            newTable[index].push_back(pair);
        }
    }

    // Delete the old table and update the table pointer
    delete[] table;
    table = newTable;
    tableSize = newSize;
}

/**********************************************************************************
What does the function do? Get the value of the key, throws an error if the key is not found
What does it return? Value of the key-value pair
Parameter 1: Key
**********************************************************************************/
template<typename T>
T HashTable<T>::get(const std::string& key) const {
    
    // Compute the hash index
    size_t index = hash(key, tableSize);

    // Search for the key in the list at the computed index
    for (const auto& pair : table[index]) {
        if (pair.key == key) {
            return pair.value;
        }
    }

    // Throw an error if the key is not found
    throw std::out_of_range("Key not found in hash table.");
}

#endif // HASHTABLE_H