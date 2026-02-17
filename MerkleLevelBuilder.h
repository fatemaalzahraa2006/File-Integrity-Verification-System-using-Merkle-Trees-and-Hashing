#ifndef MERKLELEVELBUILDER_H
#define MERKLELEVELBUILDER_H

#include "MerkleNode.h"

class MerkleLevelBuilder {
public:
    MerkleLevelBuilder() {}
    ~MerkleLevelBuilder() {}

    MerkleNode* buildTree(MerkleNode* leaves[], int n);
    void printDataTree(MerkleNode* node, int level = 0);
    void printHashTree(MerkleNode* node, int level = 0);
};

#endif
