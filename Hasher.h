// Hasher header file comments

#ifndef HASHER_H  // "ifndef" checks if file has been read before
#define HASHER_H  // mark it as read

#include <string>

using namespace std;

class Hasher {
public:
    // =============================================================
    // 1. THE CORE PROMISES (Defined in Hasher.cpp)
    // =============================================================

    static string sha256(string data); //static was used to avoid the need of initializing an object first to use the function sha256


    static string hashPair(string left, string right); // The helper specifically for your Merkle Tree (Left + Right)























    /*
    // =============================================================
    // 2. THE CONVENIENCE WRAPPERS (Defined right here)
    // =============================================================

    // WRAPPER 1: For Numbers (int, float, etc.)
    // It converts them to text using 'to_string' before hashing.
    template <typename T>
    static string hash(T data) {
        return sha256(to_string(data));
    }

    // WRAPPER 2: For Strings (std::string)
    // Prevents the template above from breaking when you pass a string.
    static string hash(string data) {
        return sha256(data);
    }

    // WRAPPER 3: For Raw Text (const char*)
    // Handles cases like: Hasher::hash("hello");
    static string hash(const char* data) {
        return sha256(string(data));
    }
    */
};

#endif