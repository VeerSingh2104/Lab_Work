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

vector<vector<int>> getMatrixInverse3x3(const vector<vector<int>> &matrix) {
    int det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
              matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
              matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    det = (det % 26 + 26) % 26; // Ensure det is positive

    int invDet = modInverse(det, 26);

    vector<vector<int>> inverse(3, vector<int>(3));
    inverse[0][0] = (invDet * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])) % 26;
    inverse[0][1] = (invDet * -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1])) % 26;
    inverse[0][2] = (invDet * (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1])) % 26;
    inverse[1][0] = (invDet * -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])) % 26;
    inverse[1][1] = (invDet * (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0])) % 26;
    inverse[1][2] = (invDet * -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0])) % 26;
    inverse[2][0] = (invDet * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])) % 26;
    inverse[2][1] = (invDet * -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0])) % 26;
    inverse[2][2] = (invDet * (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0])) % 26;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverse[i][j] = (inverse[i][j] + 26) % 26;
        }
    }

    return inverse;
}

string hillCipher3x3(const string &text, const vector<vector<int>> &key) {
    string result = "";
    for (size_t i = 0; i < text.size(); i += 3) {
        vector<int> block = {text[i] - 'A', text[i + 1] - 'A', text[i + 2] - 'A'};
        vector<int> encryptedBlock(3);

        encryptedBlock[0] = (key[0][0] * block[0] + key[0][1] * block[1] + key[0][2] * block[2]) % 26;
        encryptedBlock[1] = (key[1][0] * block[0] + key[1][1] * block[1] + key[1][2] * block[2]) % 26;
        encryptedBlock[2] = (key[2][0] * block[0] + key[2][1] * block[1] + key[2][2] * block[2]) % 26;

        result += encryptedBlock[0] + 'A';
        result += encryptedBlock[1] + 'A';
        result += encryptedBlock[2] + 'A';
    }
    return result;
}

int main() {
    string plaintext = "ACT";
    vector<vector<int>> key3x3 = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};

    string ciphertext = hillCipher3x3(plaintext, key3x3);
    cout << "3x3 Hill Cipher:" << endl;
    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    vector<vector<int>> inverseKey3x3 = getMatrixInverse3x3(key3x3);
    string decryptedText = hillCipher3x3(ciphertext, inverseKey3x3);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}

