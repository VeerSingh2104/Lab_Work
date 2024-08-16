#include <iostream>
#include <string>

using namespace std;

string generateKey(const string &plaintext, const string &key) {
    string keyExtended = key;
    while (keyExtended.length() < plaintext.length()) {
        keyExtended += key;
    }
    return keyExtended.substr(0, plaintext.length());
}

string vignereEncode(const string &plaintext, const string &key) {
    string ciphertext = "";
    string keyExtended = generateKey(plaintext, key);
    for (size_t i = 0; i < plaintext.length(); ++i) {
        char encodedChar = (toupper(plaintext[i]) + toupper(keyExtended[i]) - 2 * 'A') % 26 + 'A';
        ciphertext += encodedChar;
    }
    return ciphertext;
}

string vignereDecode(const string &ciphertext, const string &key) {
    string plaintext = "";
    string keyExtended = generateKey(ciphertext, key);
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char decodedChar = (toupper(ciphertext[i]) - toupper(keyExtended[i]) + 26) % 26 + 'A';
        plaintext += decodedChar;
    }
    return plaintext;
}

int main() {
    string plaintext = "computers";
    string key = "occurence";

    string encoded = vignereEncode(plaintext, key);
    string decoded = vignereDecode(encoded, key);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}

