 #include "MerkleLevelBuilder.h"
#include <iostream>
using namespace std;

MerkleNode* MerkleLevelBuilder::buildTree(MerkleNode* leaves[], int n) {
    if (n == 1) return leaves[0];

    int nextLevelSize = (n + 1) / 2;
	MerkleNode** parents = new MerkleNode * [nextLevelSize]; // pointer to array of merkleNode pointers

    int index = 0;
    for (int i = 0; i < n; i += 2) {
        if (i + 1 < n)
            parents[index++] = new MerkleNode(leaves[i], leaves[i + 1]);
        else
            parents[index++] = new MerkleNode(leaves[i], leaves[i]); // duplicate if odd
    }

    MerkleNode* root = buildTree(parents, nextLevelSize);
    delete[] parents;
    return root;
}

void MerkleLevelBuilder::printDataTree(MerkleNode* node, int level) {
    if (!node) return;
    printDataTree(node->right, level + 1);
    for (int i = 0; i < level; ++i) cout << "        ";
    cout << node->data << endl;
    printDataTree(node->left, level + 1);
}

void MerkleLevelBuilder::printHashTree(MerkleNode* node, int level) { //inorder traversal
	if (!node) return; // stop recursion if node is null
    printHashTree(node->right, level + 1);
    for (int i = 0; i < level; ++i) cout << "        ";
    cout << node->hash << endl;
    printHashTree(node->left, level + 1);
}

