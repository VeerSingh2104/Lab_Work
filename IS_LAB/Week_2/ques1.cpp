#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
string encrypt(const string& plaintext, int key){
    int length = plaintext.length();
    vector<string> grid((length + key - 1)/key,string(key,' '));

    int index = 0;
    for(int r=0;r<grid.size();++r){
        for(int c=0;c<key && index<length;++c){
            grid[r][c]=plaintext[index++];
        }
    }

    string ciphertext;
    for(int c=0;c<key;++c){
        for(int r=0;r<grid.size();++r){
            if(grid[r][c]!=' '){
                ciphertext += grid[r][c];
            }
        }
    }
    return ciphertext;
}

string decrypt(const string& ciphertext, int key){
    int length = ciphertext.length();
    int rows = (length+key-1)/key;
    vector<string> grid(rows,string(key,' '));

    int index=0;
    for(int c=0;c<key;c++){
        for(int r=0;r<rows && index<length;r++){
            grid[r][c]=ciphertext[index++];
        }
    }

    string plaintext;
    for(int r=0;r<rows;++r){
        for(int c=0;c<key;c++){
            if(grid[r][c]!=' '){
                plaintext+=grid[r][c];
            }
        }
    }
    return plaintext;
}



int main(){
    string plaintext;
    int key;
    cout<<"Enter plaintext: ";
    getline(cin,plaintext);
    cout<<"Enter key (number of columns): ";
    cin>>key;

    plaintext.erase(remove(plaintext.begin(),plaintext.end(), ' '),plaintext.end());

    string ciphertext=encrypt(plaintext,key);
    cout<<"Cipher Text: "<<ciphertext<<endl;

    string decryptedtext = decrypt(ciphertext,key);
    cout<<"Decrypted Text: "<<decryptedtext<<endl;

    return 0;
}

