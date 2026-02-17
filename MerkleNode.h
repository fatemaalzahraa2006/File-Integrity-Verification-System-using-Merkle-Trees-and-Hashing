#ifndef MERKLENODE_H
#define MERKLENODE_H

#include <string>
#include "Hasher.h"

class MerkleNode {
public:
    std::string data;  // letters(visualization)
    std::string hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(std::string input);
    MerkleNode(MerkleNode* l, MerkleNode* r);
};

#endif


