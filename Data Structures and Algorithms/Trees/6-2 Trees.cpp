//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Ken Rodriguez
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Read a document and process its information as bids in an
//               array of nodes. After processing the dataset, allow the user
//               to search for a specific bid, and remove a specific bid via
//               BST algorithms.
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// FIXME (1): Internal structure for tree node
struct Node {
    Bid bid;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        //Set the LEFT and RIGHT node pointers to null
        left = nullptr;
        right = nullptr;
    }

    // Initialize a Node with a bid
    Node(Bid newBid) : Node(){
        this->bid = newBid;
    }

};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    
    // Set the root node to null
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // Start at the root of the tree.
    this->inOrder(root);
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) Implement inserting a bid into the tree

    // If there is no existing Node, add a node and assign that node the root position.
    if (root == nullptr) {
        // Assign the new Node the bid "bid"
        root = new Node(bid);
    }
    // If there is an existing Node, append that node.
    else {
        this->addNode(root, bid);
    }

}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (4a) Implement removing a bid from the tree
    this->removeNode(root, bidId);

}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) Implement searching the tree for a bid

    // Initialize bid early to prevent errors.
    Bid bid;

    // If there is no root node, return.
    if (root == nullptr) {
        return bid;
    }
    
    // Start the search at the root node.
    Node* current = root;

    // Keep looping downward until the bottom of the tree is reached or the bid is found.
    while (current != nullptr) {

        // If the current node is the node being searched for, return current node.
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;
        }
        // If the bid is LESS THAN the current node, traverse left.
        else if (bidId.compare(current->bid.bidId) < 0) {
            current = current->left;
        }
        // If the bid is GREATER THAN the current node, traverse right.
        else {
            current = current->right;
        }
    }

    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) Implement inserting a bid into the tree

    // If the new node is LESS THAN the existing node, place it in the left subtree.
    if (node->bid.bidId.compare(bid.bidId) > 0) {

        // If the left node returns null, add the new Node to the left subtree.
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        // If the left node does NOT return null, check the next node.
        else {
            this->addNode(node->left, bid);
        }
    }
    // If the new node is GREATER THAN than the existing node, place it in the right subtree.
    else {

        // If the right node returns null, add the new node to the right subtree.
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        // IF the right node does NOT return null, check the next node on the tree.
        else {
            this->addNode(node->right, bid);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    
    // If the current node does not return nullptr, print the bid's contents.
    if (node != nullptr) {
        inOrder(node->left);

        cout << node->bid.bidId << ": " << node->bid.title << " | " 
             << node->bid.amount << " | "<< node->bid.fund << endl;

        inOrder(node->right);
    }
}

// FIXME (4b) Remove Node function.
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    
    // If this node is null, return to avoid a crash.
    if (node == nullptr) {
        return node;
    }
    
    // If bidId is less than that of the node's, continue down the left subtree via recursion.
    // Incidentally, the concept of recursion has finally just "clicked" for me. What a cool concept.
    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = removeNode(node->left, bidId);
    }
    // If bidId is greater than that of the node's, contine down the right subtree via recursion.
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->right = removeNode(node->right, bidId);
    }
    // If bidId is equal to that of the node's, remove it.
    else {

        // If the node has no children, it's a leaf node. Remove it, easy.
        if (node->left == nullptr && node->right == nullptr) {

            delete node;
            node = nullptr;
        }
        // If the node has one child to the left
        else if (node->left != nullptr && node->right == nullptr) {

            // Create a temporary node pointer to hold data.
            Node* temp = node;

            // Set the current node to the node on the left.
            node = node->left;

            // Delete the temporary node.
            delete temp;
        }
        // If the node has one child to the right
        else if (node->right != nullptr && node->left == nullptr) {

            // Create a temporary node pointer to hold data.
            Node* temp = node;

            // Set the current node to the node on the right.
            node = node->right;

            // Delete the temporary node.
            delete temp;
        }
        // If the node has two children (left and right)
        else {

            // Temporarily point to the RIGHT side.
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            // Set the inputted node's bid to the bid held in temp.
            node->bid = temp->bid;

            // Remove the "old" right bid.
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }

    return node;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst{};

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
