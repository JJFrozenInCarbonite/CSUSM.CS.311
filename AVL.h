/****************
Template created by Kazumi Slott
CS311

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent?: 2.5 hours
Any difficulties?: To answer the "WHY private?"" questions throughout the code, that is because we are leveraging encapsulation. Meaning 
that any one else using our code will only have to use the public interface we've constructed and not directly interact/manipulate the 
underlying data structures. This has the benefit of simplifying the code and making it easier to use, but also makes it more difficult to
break the code by accident... or allow a bad actor to break the code on purpose.
*****************/

#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

//forward declaration of AVL class. We need this because AVL class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
template <class T>
class AVL;

// Node class for the binary search tree (AVL)
template <class T>
class Node {
    friend class AVL<T>;  // Grant AVL access to private members of Node
private:
    T el;               // Element stored in the node
    Node* right;        // Pointer to the right child
    Node* left;         // Pointer to the left child
    Node* up;           // Pointer to the parent node
    int bf;             // Balance factor
  
public:
    Node() : right(nullptr), left(nullptr), up(nullptr), bf(0) {} // Default constructor
    Node(const T& e) : el(e), right(nullptr), left(nullptr), up(nullptr), bf(0) {} // Constructor with element
    T getEl() const { return el; } // Returns the element
};

// Binary Search Tree (AVL) class
template <class T>
class AVL 
{
private:
  Node<T>* root; // Root of the tree

  void destroy(Node<T>* p);
  void insertNodeR(Node<T>*& p, const T& e);
  void inOrderPrint(Node<T>* p);
  void preOrderPrint(Node<T>* p);
  void postOrderPrint(Node<T>* p);
  int getMaxLength(Node<T>* p);
  int getMinLength(Node<T>* p);
  int getNumNodes(Node<T>* p);
  int getEvenNodes(Node<T>* p);
  Node<T>* searchR(Node<T>* p, const T& e);
  void remove(Node<T>*& p);
  Node<T>* rightRotation(Node<T>* p);
  Node<T>* leftRotation(Node<T>* p);
  void balanceTree(Node<T>* p);
  Node<T>* updateBF(Node<T>* q);

 public:
  AVL() { root = nullptr; }  //implement constructor here
  ~AVL(); //need to have a private recursive function. Name it destroy.
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
  Node<T>* searchR(const T& e);
  bool remove(const T& e);
  void BFTprint();
  void DFTprint();
};

// Destructor for the AVL class
/**
 * Cleans up the binary search tree by deallocating all nodes.
 * Calls the private destroy function starting from the root.
 */
template <class T>
AVL<T>::~AVL()
{
  destroy(root);
}


/**
 * Recursively destroys all nodes in the binary search tree.
 * @param p The current node to start the destruction process from.
 */
template <class T>
void AVL<T>::destroy(Node<T>* p)
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
void AVL<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

/**
 * Recursively inserts a new node into the binary search tree.
 * @param p A reference to the current node being considered.
 * @param e The element to be inserted into the tree.
 */
template <class T>
void AVL<T>::insertNodeR(Node<T>*& p, const T& e) {
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
void AVL<T>::insertNodeI(const T& e) {
    Node<T>* newNode = new Node<T>(e); // Create a new node to insert
    if (root == nullptr) {
        root = newNode; // Insert as the root if the tree is empty
        return;
    }

    Node<T>* p = root; // Current node
    Node<T>* parent = nullptr; // Parent of the current node

    // Find the correct position to insert the new node
    while (p != nullptr) {
        parent = p; // Update the parent node
        if (e < p->el) {
            p = p->left; // Move to the left child
        } else {
            p = p->right; // Move to the right child
        }
    }

    // Insert the new node as a child of the parent
    if (e < parent->el) {
        parent->left = newNode; // Insert as the left child
    } else {
        parent->right = newNode; // Insert as the right child
    }
    newNode->up = parent; // Set the parent pointer of the new node

    // Balance the tree starting from the parent of the new node
    balanceTree(parent);
}

/**
 * Updates the balance factors of the nodes starting from the given node.
 * This function traverses up the tree from the given node, updating the
 * balance factors and checking for imbalances.
 *
 * @param p The starting node from which to update the balance factors.
 * @return The first unbalanced node encountered, or nullptr if the tree is balanced.
 */
templa
template <class T>
Node<T>* AVL<T>::updateBF(Node<T>* p) {
    while (p != nullptr) {
        int leftHeight = (p->left != nullptr) ? getMaxLength(p->left) : 0;
        int rightHeight = (p->right != nullptr) ? getMaxLength(p->right) : 0;

        p->bf = rightHeight - leftHeight;

        if (p->bf < -1 || p->bf > 1) {
            return p; // Return the unbalanced node
        }

        p = p->up; // Move up to the parent node
    }
    return nullptr; // Tree is balanced
}

/**
 * Balances the AVL tree starting from the given node.
 * This function updates the balance factors of the nodes and performs
 * the necessary rotations to maintain the AVL tree properties.
 *
 * @param p The starting node from which to balance the tree.
 */
template <class T>
void AVL<T>::balanceTree(Node<T>* p) {
    while (p != nullptr) {
        updateBF(p); // Update the balance factor of the current node

        if (p->bf == -2) { // Left heavy
            if (p->left->bf == 1) {
                leftRotation(p->left); // Left-right case
            }
            rightRotation(p); // Left-left case
        } else if (p->bf == 2) { // Right heavy
            if (p->right->bf == -1) {
                rightRotation(p->right); // Right-left case
            }
            leftRotation(p); // Right-right case
        }

        p = p->up; // Move up to the parent node
    }
}

/**
 * Performs a left rotation on the subtree rooted at the given node.
 * This operation is used to balance the AVL tree when the right subtree
 * is heavier than the left subtree.
 *
 * @param p The root of the subtree to be rotated.
 * @return The new root of the rotated subtree.
 */
template <class T>
Node<T>* AVL<T>::leftRotation(Node<T>* p) {
    Node<T>* newRoot = p->right; // The right child will become the new root
    p->right = newRoot->left; // The left child of the new root becomes the right child of the old root
    if (newRoot->left != nullptr) {
        newRoot->left->up = p; // Update the parent pointer of the new right child
    }
    newRoot->up = p->up; // The parent of the old root becomes the parent of the new root
    if (p->up == nullptr) {
        root = newRoot; // If the old root was the root of the entire tree, update the tree's root
    } else if (p == p->up->left) {
        p->up->left = newRoot; // If the old root was a left child, update the parent's left child
    } else {
        p->up->right = newRoot; // If the old root was a right child, update the parent's right child
    }
    newRoot->left = p; // The old root becomes the left child of the new root
    p->up = newRoot; // Update the parent pointer of the old root

    updateBF(p); // Update the balance factor of the old root
    updateBF(newRoot); // Update the balance factor of the new root

    return newRoot; // Return the new root of the rotated subtree
}

/**
 * Performs a right rotation on the subtree rooted at the given node.
 * This operation is used to balance the AVL tree when the left subtree
 * is heavier than the right subtree.
 *
 * @param p The root of the subtree to be rotated.
 * @return The new root of the rotated subtree.
 */
template <class T>
Node<T>* AVL<T>::rightRotation(Node<T>* p) {
    Node<T>* newRoot = p->left; // The left child will become the new root
    p->left = newRoot->right; // The right child of the new root becomes the left child of the old root
    if (newRoot->right != nullptr) {
        newRoot->right->up = p; // Update the parent pointer of the new left child
    }
    newRoot->up = p->up; // The parent becomes the parent of the new root
    if (p->up == nullptr) {
        root = newRoot; // If the old root was the root of the entire tree, update the tree's root
    } else if (p == p->up->left) {
        p->up->left = newRoot; // If the old root was a left child, update the parent's left child
    } else {
        p->up->right = newRoot; // If the old root was a right child, update the parent's right child
    }
    newRoot->right = p; // The old root becomes the right child of the new root
    p->up = newRoot; // Update the parent pointer

    updateBF(p); // Update the balance factor of the old root
    updateBF(newRoot); // Update the balance factor of the new root

    return newRoot; // Return the new root
}

/**
 * Prints the elements of the binary search tree in in-order traversal.
 */
template <class T>
void AVL<T>::inOrderPrint()
{
  inOrderPrint(root);
}

/**
 * Recursively prints the elements of the binary search tree in in-order traversal.
 * @param p The current node to start the in-order traversal from.
 */
template <class T>
void AVL<T>::inOrderPrint(Node<T>* p) {
  if (p == nullptr) return; // Base case: empty tree
  inOrderPrint(p->left);    // Traverse left subtree
  cout << p->el << "-->";   // Print the element
  inOrderPrint(p->right);   // Traverse right subtree
}

/**
 * Prints the elements of the binary search tree in pre-order traversal.
 */
template <class T>
void AVL<T>::preOrderPrint() {
  preOrderPrint(root);
}

/**
 * Recursively prints the elements of the binary search tree in pre-order traversal.
 * @param p The current node to start the pre-order traversal from.
 */
template <class T>
void AVL<T>::preOrderPrint(Node<T>* p) {
  if (p == nullptr) return; // Base case: empty tree
  cout << p->el << "-->";   // Print the element
  preOrderPrint(p->left);   // Traverse left subtree
  preOrderPrint(p->right);  // Traverse right subtree
}

/**
 * Prints the elements of the binary search tree in post-order traversal.
 */
template <class T>
void AVL<T>::postOrderPrint() {
  postOrderPrint(root);
}

/**
 * Recursively prints the elements of the binary search tree in post-order traversal.
 * @param p The current node to start the post-order traversal from.
 */
template <class T>
void AVL<T>::postOrderPrint(Node<T>* p) {
  if (p == nullptr) return; // Base case: empty tree
  postOrderPrint(p->left);  // Traverse left subtree
  postOrderPrint(p->right); // Traverse right subtree
  cout << p->el << "-->";   // Print the element
}

/**
 * Returns the number of nodes in the binary search tree.
 * @return The number of nodes in the binary search tree.
 */
template <class T>
int AVL<T>::getNumNodes() {
  return getNumNodes(root);
}

/**
 * Recursively counts the number of nodes in the binary search tree.
 * @param p The current node to start the counting process from.
 * @return The number of nodes in the binary search tree.
 */
template <class T>
int AVL<T>::getNumNodes(Node<T>* p) {
  if (p == nullptr) return 0; // Base case: empty tree
  return 1 + getNumNodes(p->left) + getNumNodes(p->right); // Count nodes
}


/**
 * Returns the maximum length from the root of the binary search tree.
 * @return The maximum length from the root of the binary search tree.
 */
template <class T>
int AVL<T>::getMaxLength() {
  return getMaxLength(root);
}

/**
 * Recursively calculates the maximum length from the given node.
 * @param p The current node to start the calculation process from.
 * @return The maximum length from the given node.
 */
template <class T>
int AVL<T>::getMaxLength(Node<T>* p) {
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
int AVL<T>::getMinLength() {
  return getMinLength(root);
}

/**
 * Recursively calculates the minimum length from the given node.
 * @param p The current node to start the calculation process from.
 * @return The minimum length from the given node to the nearest leaf node.
 */
template <class T>
int AVL<T>::getMinLength(Node<T>* p) {
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
int AVL<T>::getEvenNodes() {
    return getEvenNodes(root);
}

/**
 * Recursively counts the number of even elements in the binary search tree.
 * @param p The current node to start the counting process from.
 * @return The number of even elements in the binary search tree.
 */
template <class T>
int AVL<T>::getEvenNodes(Node<T>* p) {
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
Node<T>* AVL<T>::searchI(const T& e) {
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
Node<T>* AVL<T>::searchR(const T& e) {
    return searchR(root, e);
}

/**
 * Recursively searches for a specific element in the binary search tree.
 * @param p The current node to search from.
 * @param e The element to search for in the tree.
 * @return A pointer to the node containing the element if found, nullptr otherwise.
 */
template <class T>
Node<T>* AVL<T>::searchR(Node<T>* p, const T& e) {
    if (p == nullptr || p->el == e) return p; // Base case: empty tree or element found
    return (e < p->el) ? searchR(p->left, e) : searchR(p->right, e); // Recursively search
}

//This function returns true if e was removed or false if not because it doesn't exist.
template <class T>
bool AVL<T>::remove(const T& e) //public function
{
    Node<T>* del = root; // del will point to the node to be deleted
    Node<T>* parent = nullptr; // parent will point to the parent of the node to be deleted

    // look for e in the tree
    while (del != nullptr && del->el != e) // If root is NULL, del is NULL to start with. While won't be entered and return false down below.
    {
        parent = del; // parent follows del. In other words, del is ahead of parent.
        if (e < del->el)
            del = del->left; // move to the left child
        else
            del = del->right; // move to the right child
    }

    // e doesn't exist or tree is empty.
    if (del == nullptr)
        return false;

    // check to see if root should be removed
    if (del == root)
        remove(root); // root will change. call the other remove function down below
    // We are deleting a node other than the root node. Figure out if del's node is left or right child of parent's node
    else if (parent->left == del) // parent's left child to be removed
        remove(parent->left);
    else // parent's right child to be removed
        remove(parent->right);

    // deleted the node with e
    return true;
}


//p comes out of the parent node and points to the node to be deleted OR p points to root if root is the one to be deleted.
//p will point to the grandchild (child node of the node to be deleted) if the node to be deleted has only one child or will point to NULL if p is root or the node to be deleted has no children. p will change. That is why we need to use &.                  
template <class T>
void AVL<T>::remove(Node<T>*& p) //private function
{
    Node<T>* temp = p; // temp points to the node to be deleted initially
    Node<T>* t_parent; // t_parent will point to the parent node of temp's node

    // the node to be deleted has no right child
    if (p->right == nullptr) {
        p = p->left; // p now points to the root of the left subtree under del's node
    }
    // the node to be deleted has no left child
    else if (p->left == nullptr) {
        p = p->right; // p now points to the root of the right subtree under del's node
    }
    // If the node to be deleted has 2 children
    else {
        // we are going to replace e by the largest value in the left subtree
        temp = p->left; // temp points to the root of the left subtree under the node to be deleted to start with
        t_parent = p; // t_parent points to the node to be deleted to start with

        // go to the largest value in the left subtree under the node to be deleted by going all the way down to right
        while (temp->right != nullptr) {
            t_parent = temp; // temp is ahead of t_parent
            temp = temp->right; // temp will eventually point to the largest value
        }
        // copy the largest value into the node to be deleted
        p->el = temp->el;

        if (t_parent == p) // the largest value is the direct left child of the node whose value was replaced by the largest
            t_parent->left = temp->left; // connect the left of the node whose value was replaced by the largest value to the left child of the node that has the largest value
        else // the largest value is NOT the direct left child of the node whose value was replaced by the largest
            t_parent->right = temp->left; // If the node with the largest value doesn't have any children, t_parent->right is set to NULL.
    }
    // finally delete temp;
    delete temp;
}

/**
 * Prints the elements of the binary search tree in breadth-first traversal.
 */
template <class T>
void AVL<T>::BFTprint() {
    if (root == nullptr) return; // If the tree is empty, return immediately
    std::queue<Node<T>*> q; // Create a queue for traversal
    q.push(root); // Start with the root node

    while (!q.empty()) {
        Node<T>* current = q.front(); // Get the front element
        q.pop(); // Remove the front element
        std::cout << current->el << "-->"; // Print the current node's element
        if (current->left != nullptr) q.push(current->left); // Push left child to the queue
        if (current->right != nullptr) q.push(current->right); // Push right child to the queue
    }
}

/**
 * Prints the elements of the binary search tree in depth-first traversal.
 */
template <class T>
void AVL<T>::DFTprint() {
    if (root == nullptr) return; // If the tree is empty, return immediately
    std::stack<Node<T>*> stack; // Create a stack for traversal
    stack.push(root); // Start with the root node

    while (!stack.empty()) {
        Node<T>* current = stack.top(); // Get the top element
        stack.pop(); // Remove the top element
        std::cout << current->el << "-->"; // Print the current node's element
        if (current->right != nullptr) stack.push(current->right); // Push right child to the stack
        if (current->left != nullptr) stack.push(current->left); // Push left child to the stack
    }
}

#endif