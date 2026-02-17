#include <iostream>
#include "MerkleTree.h"
#include "MerkleNode.h"
#include "MerkleLevelBuilder.h"
using namespace std;


MerkleTree::MerkleTree() {    //default constructor 
    leavesData = nullptr;
    leafCount = 0;
    root = nullptr;
}

MerkleTree::MerkleTree(string* data, int count) {   //parametarized constructor 
    leavesData = nullptr;
    leafCount = 0;
    root = nullptr;
    build(data, count);
}

MerkleTree::~MerkleTree() {    //destructor 
    deleteTree(root);
    delete[] leavesData;
}

void MerkleTree::deleteTree(MerkleNode* node) {
    if (!node) return;      // delete using recursion
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void MerkleTree::build(string* data, int count) {
    deleteTree(root);     // clear old data if rebuilding
    delete[] leavesData;

    leafCount = count;
    if (count <= 0) {
        root = nullptr;
        leavesData = nullptr;
        return;
    }

    leavesData = new string[count];
    for (int i = 0; i < count; i++) {
		leavesData[i] = data[i]; //thats an attribute in the class
    }
    root = buildFromLeaves(leavesData, count);
}

MerkleNode* MerkleTree::buildFromLeaves(string* data, int count) {
    if (count == 0) return nullptr;

    MerkleNode** leaves = new MerkleNode * [count];  //an array of pointers to leaf nodes
    for (int i = 0; i < count; i++) {
        leaves[i] = new MerkleNode(data[i]);
    }

    // Use builder to combine levels
    MerkleLevelBuilder builder; //mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
    MerkleNode* rootNode = builder.buildTree(leaves, count);

    delete[] leaves; //Delete only the array of pointers.This does not delete the nodes themselves
    return rootNode;
}

string MerkleTree::getRootHash() const {
    if (!root) return "";
    return root->hash;
}

void MerkleTree::printDataTree() const {
    if (!root) {
        cout << "Tree is empty.\n";
        return;
    }

    MerkleLevelBuilder printer;
    printer.printDataTree(root, 0);
}

void MerkleTree::printHashTree() const {
    if (!root) {
        cout << "Tree is empty.\n";
        return;
    }

    MerkleLevelBuilder printer;
    printer.printHashTree(root, 0);
}