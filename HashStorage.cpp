#include "HashStorage.h"
#include "FileHasher.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// =============================================================
// saveHash
// -------------------------------------------------------------
// Appends a file's hash to the index file.
// Each line format: filename<TAB>hash
// -------------------------------------------------------------
bool HashStorage::saveHash(const string& indexFile,
    const string& fileName,
    const string& hash) {
    // Open the index file in append mode
    ofstream out(indexFile, ios::app);
    if (!out.is_open()) {
        cerr << "[ERROR] Cannot open index file for writing: " << indexFile << endl;
        return false; // return false on failure
    }

    // Write the file name and hash separated by tab
    out << fileName << "\t" << hash << endl;

    // Close the file
    out.close();
    return true; // success
}

// =============================================================
// verifyFromIndex
// -------------------------------------------------------------
// Reads each line from the index file and verifies the hash.
// Prints [MATCH], [TAMPERED], or [MISSING] for each file.
// -------------------------------------------------------------
void HashStorage::verifyFromIndex(const string& indexFile, const string& currentHash) {
    // Open the index file for reading
    ifstream in(indexFile);
    if (!in.is_open()) {
        cerr << "[ERROR] Cannot open index file for reading: " << indexFile << endl;
        return;
    }

    string line;
    //FileHasher fh; // object to compute file hashes

    // Read the index file line by line
    while (getline(in, line)) {
        if (line.empty()) continue; // skip empty lines

        // Find the tab separator between filename and hash
        size_t sep = line.find('\t');
        if (sep == string::npos) {
            cerr << "[WARN] Invalid line in index: " << line << endl;
            continue; // skip malformed lines
        }

        // Extract file name and saved hash
        string fileName = line.substr(0, sep);
        string savedHash = line.substr(sep + 1);

        // Compute current hash of the file
        //string currentHash = fh.hashFile(fileName);

        // Compare the current hash with the saved hash
        if (currentHash.empty()) {
            // File not found
            cout << "[MISSING] " << fileName << endl;
        }
        else if (currentHash == savedHash) {
            // File is unchanged
            cout << "[MATCH] " << fileName << endl;
        }
        else {
            // File has been tampered
            cout << "[TAMPERED] " << fileName << endl;
        }
    }

    // Close the file stream
    in.close();
}