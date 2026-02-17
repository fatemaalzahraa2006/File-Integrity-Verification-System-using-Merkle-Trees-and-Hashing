#include "MerkleNode.h"

// Leaf node
MerkleNode::MerkleNode(std::string input) {
    data = input; //Raw file block (binary data not shown well)
    hash = Hasher::sha256(input);
    left = right = nullptr;
}

// Internal node
MerkleNode::MerkleNode(MerkleNode* l, MerkleNode* r) {
    left = l;
    right = r;
	data = l->data + "+" + r->data; // combine for visualization 
    hash = Hasher::hashPair(l->hash, r->hash);
}