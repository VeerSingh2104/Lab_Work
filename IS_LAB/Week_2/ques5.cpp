#include <iostream>
#include <string>
using namespace std;

string generateAutoKey(const string &plaintext, const string &key) {
    string autoKey = key + plaintext;
    return autoKey.substr(0, plaintext.length());
}

string vignereAutoKeyEncode(const string &plaintext, const string &key) {
    string ciphertext = "";
    string autoKey = generateAutoKey(plaintext, key);
    for (size_t i = 0; i < plaintext.length(); ++i) {
        char encodedChar = (toupper(plaintext[i]) + toupper(autoKey[i]) - 2 * 'A') % 26 + 'A';
        ciphertext += encodedChar;
    }
    return ciphertext;
}

string vignereAutoKeyDecode(const string &ciphertext, const string &key) {
    string plaintext = "";
    string autoKey = key;
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char decodedChar = (toupper(ciphertext[i]) - toupper(autoKey[i]) + 26) % 26 + 'A';
        plaintext += decodedChar;
        autoKey += decodedChar;
    }
    return plaintext;
}

int main() {
    string plaintext = "wearediscoveredsaveyourself";
    string key = "deceptive";

    string encoded = vignereAutoKeyEncode(plaintext, key);
    string decoded = vignereAutoKeyDecode(encoded, key);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}

