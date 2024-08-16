#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void preparePlayfairMatrix(const std::string &key, char matrix[5][5]) {
    string keyString = "";
    unordered_map<char, bool> used;

    for (char ch : key) {
        char upperCh = toupper(ch);
        if (upperCh == 'J') upperCh = 'I';
        if (!used[upperCh]) {
            keyString += upperCh;
            used[upperCh] = true;
        }
    }

    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; 
    for (char ch : alphabet) {
        if (!used[ch]) {
            keyString += ch;
            used[ch] = true;
        }
    }

    int k = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            matrix[i][j] = keyString[k++];
        }
    }
}

void findPosition(char matrix[5][5], char ch, int &row, int &col) {
    if (ch == 'J') ch = 'I'; 
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string encodeDigraph(char matrix[5][5], char a, char b) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, row1, col1);
    findPosition(matrix, b, row2, col2);

    string encoded = "";
    if (row1 == row2) {
        encoded += matrix[row1][(col1 + 1) % 5];
        encoded += matrix[row2][(col2 + 1) % 5];
    } else if (col1 == col2) {
        encoded += matrix[(row1 + 1) % 5][col1];
        encoded += matrix[(row2 + 1) % 5][col2];
    } else {
        encoded += matrix[row1][col2];
        encoded += matrix[row2][col1];
    }

    return encoded;
}

vector<string> preparePlaintext(const std::string &plaintext) {
    vector<string> digraphs;
    string temp = "";
    int n = plaintext.size();

    for (int i = 0; i < n; ++i) {
        char ch = toupper(plaintext[i]);
        if (ch == 'J') ch = 'I'; 

        if (temp.empty()) {
            temp += ch;
        } else {
            if (temp[0] == ch) {
                temp += 'X'; 
                digraphs.push_back(temp);
                temp = ch;
            } else {
                temp += ch;
                digraphs.push_back(temp);
                temp = "";
            }
        }
    }

    if (!temp.empty()) {
        temp += 'X'; 
        digraphs.push_back(temp);
    }

    return digraphs;
}

string playfairEncode(const std::string &plaintext, const std::string &key) {
    char matrix[5][5];
    preparePlayfairMatrix(key, matrix);
    vector<string> digraphs = preparePlaintext(plaintext);
    string ciphertext = "";

    for (const auto &digraph : digraphs) {
        ciphertext += encodeDigraph(matrix, digraph[0], digraph[1]);
    }

    return ciphertext;
}

int main() {
    string plaintext = "computers";
    string key = "occurence";

    string encoded = playfairEncode(plaintext, key);
    cout << "Plaintext: " << plaintext << std::endl;
    cout << "Key: " << key << std::endl;
    cout << "Encoded: " << encoded << std::endl;

    return 0;
}

