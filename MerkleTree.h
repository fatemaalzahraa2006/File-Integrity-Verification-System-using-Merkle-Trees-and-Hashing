#pragma once
#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <string>
#include "MerkleNode.h"
#include "MerkleLevelBuilder.h"

class MerkleNode;

class MerkleTree {
private:
    string* leavesData;
    int leafCount;
    MerkleNode* root;

    void deleteTree(MerkleNode* node);
    MerkleNode* buildFromLeaves(std::string* data, int count); 

public:
    MerkleTree();
	MerkleTree(std::string* data, int count); //takes block data and count
    ~MerkleTree();

    void build(std::string* data, int count);
    std::string getRootHash() const;
    void printDataTree() const;
    void printHashTree() const;

};

#endif

