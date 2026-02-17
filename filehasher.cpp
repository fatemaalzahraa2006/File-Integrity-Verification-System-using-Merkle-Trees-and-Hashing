#include "FileHasher.h" // Include your own header first
#include "Hasher.h"     // Include the tool to do the math
#include <iostream>
#include <fstream>      // Needed for ifstream

using namespace std;

// 1. Default constructor
FileHasher::FileHasher() {
    // Nothing needed here
}

// 2. Function to compute SHA-256 hash file
string FileHasher::hashFile(const string& filePath) {

    // Open file as text
    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filePath << endl;
        return "";  // Return empty string if file cannot be opened
    }

    string fileContent;       // to store file content
    char part[1024];          // variable to read parts(blocks) of the file

    // Read file in blocks of 1024 characters
    // This logic is GREAT. It is much faster than reading char-by-char.
    while (file.read(part, sizeof(part)) || file.gcount() > 0) {
        fileContent += string(part, file.gcount());  // Add the read part to the file content
    }

    file.close();  // Close the file

    // Compute and return SHA-256 hash using the Static function
    return Hasher::sha256(fileContent);
}