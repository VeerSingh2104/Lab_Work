#include <bits/stdc++.h>
using namespace std;

string monoalphabeticEncode(const std::string &plaintext, const std::string &key) {
    string ciphertext = "";
    unordered_map<char, char> charMap;

    for (char i = 'A'; i <= 'Z'; ++i) {
        charMap[i] = key[i - 'A'];
    }

    for (char ch : plaintext) {
        if (isalpha(ch)) {
            char upperCh = toupper(ch);
            ciphertext += charMap[upperCh];
        } else {
            ciphertext += ch;
        }
    }

    return ciphertext;
}

string monoalphabeticDecode(const std::string &ciphertext, const std::string &key) {
    string plaintext = "";
    unordered_map<char, char> reverseCharMap;

    for (char i = 'A'; i <= 'Z'; ++i) {
        reverseCharMap[key[i - 'A']] = i;
    }

    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            char upperCh = toupper(ch);
            plaintext += reverseCharMap[upperCh];
        } else {
            plaintext += ch;
        }
    }

    return plaintext;
}

int main() {
    string plaintext = "HELLO WORLD";
    string key = "QWERTYUIOPASDFGHJKLZXCVBNM";

    string encoded = monoalphabeticEncode(plaintext, key);
    string decoded = monoalphabeticDecode(encoded, key);

    cout << "Plaintext: " << plaintext << std::endl;
    cout << "Encoded: " << encoded << std::endl;
    cout << "Decoded: " << decoded << std::endl;

    return 0;
}

