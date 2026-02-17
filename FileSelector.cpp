#include "FileSelector.h"
//#include "FileHasher.h"
#include <iostream>
#include <filesystem>
#include <string>

// Fallback for older C++ versions if the property fix doesn't work perfectly
#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

using namespace std;

// Helper to validate path
bool ValidateInputPath(const string& filePath) {
    if (!fs::exists(filePath)) {
        cout << "[ERROR] File path does not exist." << endl;
        return false;
    }
    return true;
}

// FIX 1: Function name matches the header (Capital 'P')
void processPath(const string& filepath, const string& hash) {

    // FIX 2: Check validation
    if (!ValidateInputPath(filepath)) {
        return; // FIX 3: Void functions return NOTHING (not 0)
    }

    // FIX 4: Create the FileHasher object so we can use it
    //FileHasher fh;

    // Handle Regular File
    if (fs::is_regular_file(filepath)) {
        // FIX 5: Call hashFile using the object 'fh'
        //string hash = fh.hashFile(filepath);
        cout << "File: " << fs::path(filepath).filename().string() << endl;
        cout << "Hash: " << hash << endl;
    }
    // Handle Directory
    else if (fs::is_directory(filepath)) {
        cout << "[INFO] Directory detected. Hashing handled externally." << endl;
    }
    else {
        cout << "The path is neither a file nor a directory." << endl;
    }
}