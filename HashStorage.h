#ifndef HASHSTORAGE_H
#define HASHSTORAGE_H

#include <string>

using namespace std;

// =============================================================
// HashStorage
// -------------------------------------------------------------
// Handles saving and verifying file hashes.
// Relies on FileHasher to compute actual file hashes.
// =============================================================
class HashStorage {
public:
    // ---------------------------------------------------------
    // saveHash
    // - Saves a file hash to an index file
    // - Returns true if successful, false on error
    // - Uses tab '\t' as separator to support file names with spaces
    // ---------------------------------------------------------
    static bool saveHash(const string& indexFile,
        const string& fileName,
        const string& hash);

    // ---------------------------------------------------------
    // verifyFromIndex
    // - Reads the index file and verifies each file's hash
    // - Prints result directly:
    //     [MATCH]    -> file unchanged
    //     [TAMPERED] -> file modified
    //     [MISSING]  -> file not found
    // ---------------------------------------------------------
    static void verifyFromIndex(const string& indexFile, const string& currentHash);
};

#endif