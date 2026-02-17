#ifndef FILEHASHER_H
#define FILEHASHER_H

#include <string>

using namespace std;

class FileHasher {
public:
    // 1. Default Constructor
    FileHasher();

    // 2. Function to compute SHA-256 hash of a file
    // Takes the file path as input and returns the hash string
    string hashFile(const string& filePath);
};

#endif