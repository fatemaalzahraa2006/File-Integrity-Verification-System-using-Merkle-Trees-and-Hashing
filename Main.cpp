#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "MerkleTree.h"
#include "FileSelector.h"
#include "HashStorage.h"

using namespace std;
namespace fs = std::filesystem;


string* readFileBlocks(const string& filepath, size_t& blockCount, size_t blockSize=1024) {
	ifstream file(filepath, ios::binary); //open in binary mode
    if (!file.is_open()) {
        cout << "[ERROR] Cannot open file: " << filepath << endl;
        blockCount = 0;
        return nullptr;
    }

    // First pass: count blocks
	file.seekg(0, ios::end); // moves the cursor to the end of the file's content
	size_t fileSize = file.tellg(); //retrieves the current position of the cursor = file size in bytes
    file.seekg(0, ios::beg);

	blockCount = (fileSize + blockSize - 1) / blockSize; // or simply ceil(fileSize / blockSize)

    // Allocate array of strings
    string* blocks = new string[blockCount];

	char buffer[1024]; //buffer to read blocks and carry each block data
    size_t index = 0;

    while (file.read(buffer, blockSize) || file.gcount() > 0) {
        blocks[index++] = string(buffer, file.gcount());
    }

    file.close();
    return blocks;
}



int main() {
    // Step 1: Read user input path
    string filepath;
    cout << "Enter file path: ";
    getline(cin, filepath);

    // Validate path and print file info
    
    // Step 2: Ask user for actio
    cout << "Do you want to (S)ave hash or (V)erify files? ";
    char choice;
    cin >> choice;

    string indexFile = "hash_index.txt";
    //string indexFile = "C:/Users/Zainab Mohamed/Desktop/hash_index.txt";


    string merkleRootHash;

    if (choice == 'S' || choice == 's') {
        if (!fs::is_regular_file(filepath)) {
            cout << "[ERROR] Saving hashes is only supported for files." << endl;
            return 0;
        }

        size_t blockCount = 0;
        string* blocks = readFileBlocks(filepath, blockCount); 

        if (blocks == nullptr || blockCount == 0) {
            cout << "[ERROR] Failed to read file blocks." << endl;
            return 0;
        }

        MerkleTree tree(blocks, blockCount);


        // Step 5: Print the tree structures
        //cout << "\n=== Data Tree ===\n";
        //tree.printDataTree();

        cout << "\n=== Hash Tree ===\n";
        tree.printHashTree();

        // Step 6: Get Merkle root hash
        merkleRootHash = tree.getRootHash();
        //cout << "\nRoot hash: " << merkleRootHash << endl;
        processPath(filepath, merkleRootHash);

        // Step 7: Save the root hash to index file
        if (HashStorage::saveHash(indexFile, filepath, merkleRootHash)) {
            cout << "[SUCCESS] Merkle root saved for file: " << filepath << endl;
        }
        else {
            cout << "[ERROR] Failed to save Merkle root to index file." << endl;
        }
	delete[] blocks;    

    }


   /* else if (choice == 'V' || choice == 'v') {

        cout << "Verifying files using Merkle roots..." << endl;
        HashStorage::verifyFromIndex(indexFile, merkleRootHash);
    }
    */

    else if (choice == 'V' || choice == 'v') {
        // Read file blocks and build Merkle tree
        if (!fs::is_regular_file(filepath)) {
            cout << "[ERROR] File does not exist: " << filepath << endl;
            return 0;
        }

        size_t blockCount = 0;
        string* blocks = readFileBlocks(filepath, blockCount);
        if (!blocks || blockCount == 0) {
            cout << "[ERROR] Failed to read file blocks." << endl;
            return 0;
        }

        MerkleTree tree(blocks, blockCount);
        merkleRootHash = tree.getRootHash();
        delete[] blocks;

        cout << "Verifying files using Merkle roots..." << endl;
        HashStorage::verifyFromIndex(indexFile, merkleRootHash);
    }
    else {
        cout << "Invalid choice. Exiting." << endl;
    }
    return 0;
}
