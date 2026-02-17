#include "Hasher.h"
#include "picosha2.h" 


using namespace std;

// 1. The Main Function: Hashes text
string Hasher::sha256(string data) {
    string hash_hex_str;

    // Use PicoSHA2 to calculate the hash.
    // It reads from the start to the end of your string 
    // and saves the result into 'hash_hex_str'.
    picosha2::hash256_hex_string(data.begin(), data.end(), hash_hex_str);

    return hash_hex_str;
}

// 2. The Helper: Glues two hashes together
string Hasher::hashPair(string left, string right) {
    // Combine them (Left + Right)
    string combined = left + right;

    // Hash the combined string
    return sha256(combined);
}