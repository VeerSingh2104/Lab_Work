#include <iostream>
#include <vector>
#include <string>
using namespace std;

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

vector<vector<int>> getMatrixInverse2x2(const vector<vector<int>> &matrix) {
    int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    det = (det % 26 + 26) % 26; 

    int invDet = modInverse(det, 26);

    vector<vector<int>> inverse(2, vector<int>(2));
    inverse[0][0] = (invDet * matrix[1][1]) % 26;
    inverse[0][1] = (invDet * -matrix[0][1]) % 26;
    inverse[1][0] = (invDet * -matrix[1][0]) % 26;
    inverse[1][1] = (invDet * matrix[0][0]) % 26;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverse[i][j] = (inverse[i][j] + 26) % 26;
        }
    }

    return inverse;
}

string hillCipher2x2(const string &text, const vector<vector<int>> &key) {
    string result = "";
    for (size_t i = 0; i < text.size(); i += 2) {
        vector<int> block = {text[i] - 'A', text[i + 1] - 'A'};
        vector<int> encryptedBlock(2);

        encryptedBlock[0] = (key[0][0] * block[0] + key[0][1] * block[1]) % 26;
        encryptedBlock[1] = (key[1][0] * block[0] + key[1][1] * block[1]) % 26;

        result += encryptedBlock[0] + 'A';
        result += encryptedBlock[1] + 'A';
    }
    return result;
}

int main() {
    string plaintext = "HELP";
    vector<vector<int>> key2x2 = {{3, 3}, {2, 5}};

    string ciphertext = hillCipher2x2(plaintext, key2x2);
    cout << "2x2 Hill Cipher:" << endl;
    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    vector<vector<int>> inverseKey2x2 = getMatrixInverse2x2(key2x2);
    string decryptedText = hillCipher2x2(ciphertext, inverseKey2x2);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}

