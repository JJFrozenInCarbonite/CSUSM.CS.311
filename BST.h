/****************
Template created by Kazumi Slott
CS311

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent?: 2.5 hours
Any difficulties?: ??????
*****************/

#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
template <class T>
class BST;

// Node class for the binary search tree (BST)
template <class T>
class Node {
    friend class BST<T>;  / Grant BST access to private members of Node
private:
    T el;               // Element stored in the node
    Node* right;        // Pointer to the right child
    Node* left;         // Pointer to the left child
public:
    Node() : right(nullptr), left(nullptr) {} // Default constructor
    Node(const T& e) : el(e), right(nullptr), left(nullptr) {} // Constructor with element
    T getEl() const { return el; } // Returns the element
};

// Binary Search Tree (BST) class
template <class T>
class BST 
{
private:
  Node<T>* root; // Root of the tree

  void destroy(Node<T>* node);
  void insertNodeR(Node<T>*& node, const T& e);
  void inOrderPrint(Node<T>* node);
  void preOrderPrint(Node<T>* node);
  void postOrderPrint(Node<T>* node);
  int getMaxLength(Node<T>* node);
  int getMinLength(Node<T>* node);
  int getNumNodes(Node<T>* node);
  int getEvenNodes(Node<T>* node);
  Node<T>* searchR(Node<T>* node, const T& e);

 public:
  BST() { root = nullptr; }  //implement constructor here
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
  Node<T>* searchR(const T& e) { return searchR(root, e); }
  void BFTprint();
  void DFTprint();
};

// Destructor for the BST class
/**
 * Cleans up the binary search tree by deallocating all nodes.
 * Calls the private destroy function starting from the root.
 */
template <class T>
BST<T>::~BST()
{
  destroy(root);
}


/**
 * Recursively destroys all nodes in the binary search tree.
 * @param p The current node to start the destruction process from.
 */
template <class T>
void BST<T>::destroy(Node<T>* p)
{
  if (p == nullptr) return;   // Base case: empty node
  destroy(p->left);           // Destroy left subtree
  destroy(p->right);          // Destroy right subtree
  delete p;                   // Delete the current node
}

/**
 * Inserts a new node into the binary search tree using recursion.
 * @param e The element to be inserted into the tree.
 */
template <class T>
void BST<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

/**
 * Recursively inserts a new node into the binary search tree.
 * @param p A reference to the current node being considered.
 * @param e The element to be inserted into the tree.
 */
template <class T>
void BST<T>::insertNodeR(Node<T>*& p, const T& e) {
    if (p == nullptr) {
      p = new Node<T>(e); // Create a new node
    } else if (e < p->el) {
      insertNodeR(p->left, e); // Insert into the left subtree
    } else {
      insertNodeR(p->right, e); // Insert into the right subtree
    }
}


/**
 * Inserts a new node into the binary search tree using iteration.
 * @param e The element to be inserted into the tree.
 */
template <class T>
void BST<T>::insertNodeI(const T& e) {
    Node<T>* newNode = new Node<T>(e); // Create a new node to insert
    Node<T>* p = root; // Current node
    Node<T>* parent = nullptr; // Parent of the current node

    while (p != nullptr) {
      parent = p; // Update the parent node
      if (e < p->el) 
          p = p->left; // Move to the left child
      else 
          p = p->right; // Move to the right child
    }

    // Insert the new node as a child of the parent
    if (parent == nullptr)
      root = newNode; // Insert as the root
    else if (e < parent->el)
      parent->left = newNode; // Insert as the left child
    else
      parent->right = newNode; // Insert as the right child
}

/**
 * Prints the elements of the binary search tree in in-order traversal.
 */
template <class T>
void BST<T>::inOrderPrint()
{
  inOrderPrint(root);
}

/**
 * Recursively prints the elements of the binary search tree in in-order traversal.
 * @param p The current node to start the in-order traversal from.
 */
template <class T>
void BST<T>::inOrderPrint(Node<T>* p) {
  if (p == nullptr) return; // Base case: empty tree
  inOrderPrint(p->left);    // Traverse left subtree
  cout << p->el << " ";     // Print the element
  inOrderPrint(p->right);   // Traverse right subtree
}

/**
 * Prints the elements of the binary search tree in pre-order traversal.
 */
template <class T>
void BST<T>::preOrderPrint() {
  preOrderPrint(root);
}

/**
 * Recursively prints the elements of the binary search tree in pre-order traversal.
 * @param p The current node to start the pre-order traversal from.
 */
template <class T>
void BST<T>::preOrderPrint(Node<T>* p) {
  if (p == nullptr) return; // Base case: empty tree
  cout << p->el << " ";      // Print the element
  preOrderPrint(p->left);    // Traverse left subtree
  preOrderPrint(p->right);   // Traverse right subtree
}

/**
 * Prints the elements of the binary search tree in post-order traversal.
 */
template <class T>
void BST<T>::postOrderPrint() {
  postOrderPrint(root);
}

/**
 * Recursively prints the elements of the binary search tree in post-order traversal.
 * @param p The current node to start the post-order traversal from.
 */
template <class T>
void BST<T>::postOrderPrint(Node<T>* p) {
  if (p == nullptr) return; // Base case: empty tree
  postOrderPrint(p->left);  // Traverse left subtree
  postOrderPrint(p->right); // Traverse right subtree
  cout << p->el << " ";      // Print the element
}

/**
 * Returns the number of nodes in the binary search tree.
 * @return The number of nodes in the binary search tree.
 */
template <class T>
int BST<T>::getNumNodes() {
  return getNumNodes(root);
}

/**
 * Recursively counts the number of nodes in the binary search tree.
 * @param p The current node to start the counting process from.
 * @return The number of nodes in the binary search tree.
 */
template <class T>
int BST<T>::getNumNodes(Node<T>* p) {
  if (p == nullptr) return 0; // Base case: empty tree
  return 1 + getNumNodes(p->left) + getNumNodes(p->right); // Count nodes
}


/**
 * Returns the maximum length from the root of the binary search tree.
 * @return The maximum length from the root of the binary search tree.
 */
template <class T>
int BST<T>::getMaxLength() {
  return getMaxLength(root);
}

/**
 * Recursively calculates the maximum length from the given node.
 * @param p The current node to start the calculation process from.
 * @return The maximum length from the given node.
 */
template <class T>
int BST<T>::getMaxLength(Node<T>* p) {
  if (p == nullptr) return 0; // Base case: empty tree
  int leftLength = getMaxLength(p->left); // Length of left subtree
  int rightLength = getMaxLength(p->right); // Length of right subtree
  return 1 + max(leftLength, rightLength); // Return max length
}

/**
 * Returns the minimum length from the root of the binary search tree.
 * @return The minimum length from the root of the binary search tree to the nearest leaf node.
 */
template <class T>
int BST<T>::getMinLength() {
  return getMinLength(root);
}

/**
 * Recursively calculates the minimum length from the given node.
 * @param p The current node to start the calculation process from.
 * @return The minimum length from the given node to the nearest leaf node.
 */
template <class T>
int BST<T>::getMinLength(Node<T>* p) {
  if (p == nullptr) return 0; // Base case: empty tree
  if (p->left == nullptr) return 1 + getMinLength(p->right);
  if (p->right == nullptr) return 1 + getMinLength(p->left);
  int leftLength = getMinLength(p->left);
  int rightLength = getMinLength(p->right);
  return 1 + std::min(leftLength, rightLength);
}

/**
 * Returns the number of even elements in the binary search tree.
 * @return The number of even elements in the binary search tree.
 */
template <class T>
int BST<T>::getEvenNodes() {
    return getEvenNodes(root);
}

/**
 * Recursively counts the number of even elements in the binary search tree.
 * @param p The current node to start the counting process from.
 * @return The number of even elements in the binary search tree.
 */
template <class T>
int BST<T>::getEvenNodes(Node<T>* p) {
    if (p == nullptr) return 0; // Base case: empty tree
    int count = (p->el % 2 == 0) ? 1 : 0; // Increment count if even
    return count + getEvenNodes(p->left) + getEvenNodes(p->right); // Count evens
}

/**
 * Searches for a specific element in the binary search tree using iteration.
 * @param e The element to search for in the tree.
 * @return A pointer to the node containing the element if found, nullptr otherwise.
 */
template <class T>
Node<T>* BST<T>::searchI(const T& e) {
    Node<T>* p = root; // Start at the root
    while (p != nullptr) {
        if (e == p->el) return p; // Element found
        p = (e < p->el) ? p->left : p->right; // Move to the appropriate child
    }
    return nullptr; // Element not found
}


/**
 * Searches for a specific element in the binary search tree using recursion.
 * @param e The element to search for in the tree.
 * @return A pointer to the node containing the element if found, nullptr otherwise.
 */
template <class T>
Node<T>* BST<T>::searchR(const T& e) {
    return searchR(root, e);
}

/**
 * Recursively searches for a specific element in the binary search tree.
 * @param p The current node to search from.
 * @param e The element to search for in the tree.
 * @return A pointer to the node containing the element if found, nullptr otherwise.
 */
template <class T>
Node<T>* BST<T>::searchR(Node<T>* p, const T& e) {
    if (p == nullptr || p->el == e) return p; // Base case: empty tree or element found
    return (e < p->el) ? searchR(p->left, e) : searchR(p->right, e); // Recursively search
}

/**
 * Prints the elements of the binary search tree in breadth-first traversal.
 */
template <class T>
void BST<T>::BFTprint() {
    if (root == nullptr) return; // If the tree is empty, return immediately
    std::queue<Node<T>*> q; // Create a queue for traversal
    q.push(root); // Start with the root node

    while (!q.empty()) {
        Node<T>* current = q.front(); // Get the front element
        q.pop(); // Remove the front element
        std::cout << current->el << " "; // Print the current node's element
        if (current->left != nullptr) q.push(current->left); // Push left child to the queue
        if (current->right != nullptr) q.push(current->right); // Push right child to the queue
    }
}

/**
 * Prints the elements of the binary search tree in depth-first traversal.
 */
template <class T>
void BST<T>::DFTprint() {
    if (root == nullptr) return; // If the tree is empty, return immediately
    std::stack<Node<T>*> stack; // Create a stack for traversal
    stack.push(root); // Start with the root node

    while (!stack.empty()) {
        Node<T>* current = stack.top(); // Get the top element
        stack.pop(); // Remove the top element
        std::cout << current->el << " "; // Print the current node's element
        if (current->right != nullptr) stack.push(current->right); // Push right child to the stack
        if (current->left != nullptr) stack.push(current->left); // Push left child to the stack
    }
}

#endif