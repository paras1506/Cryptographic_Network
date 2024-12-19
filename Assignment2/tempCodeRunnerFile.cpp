#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Function to generate the key sequence based on the keyword
vector<int> generateKeySequence(string keyword) {
    int len = keyword.length();
    vector<pair<char, int>> keyMap(len);

    // Store characters of the keyword with their positions
    for (int i = 0; i < len; i++) {
        keyMap[i] = { keyword[i], i };
    }

    // Sort the characters alphabetically along with their positions
    sort(keyMap.begin(), keyMap.end());

    // Extract the positions in the sorted order
    vector<int> keySequence(len);
    for (int i = 0; i < len; i++) {
        keySequence[i] = keyMap[i].second;
    }

    return keySequence;
}

// Function to encrypt the plaintext using Columnar Transposition Cipher
string encryptColumnarCipher(string plaintext, string keyword) {
    int numRows = (plaintext.length() + keyword.length() - 1) / keyword.length();
    int numCols = keyword.length();
    vector<int> keySequence = generateKeySequence(keyword);

    // Fill the matrix row-wise
    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));
    for (int i = 0; i < plaintext.length(); i++) {
        grid[i / numCols][i % numCols] = plaintext[i];
    }

    // Read the grid column-wise based on the key sequence
    string ciphertext = "";
    for (int col : keySequence) {
        for (int row = 0; row < numRows; row++) {
            ciphertext += grid[row][col];
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using Columnar Transposition Cipher
string decryptColumnarCipher(string ciphertext, string keyword) {
    int numRows = (ciphertext.length() + keyword.length() - 1) / keyword.length();
    int numCols = keyword.length();
    vector<int> keySequence = generateKeySequence(keyword);

    // Fill the grid column-wise based on the key sequence
    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));
    int index = 0;
    for (int col : keySequence) {
        for (int row = 0; row < numRows; row++) {
            if (index < ciphertext.length()) {
                grid[row][col] = ciphertext[index++];
            }
        }
    }

    // Read the grid row-wise to get the plaintext
    string plaintext = "";
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            plaintext += grid[row][col];
        }
    }

    return plaintext;
}

int main() {
    string plaintext, keyword, ciphertext;

    // Input plaintext and keyword
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter keyword: ";
    cin >> keyword;

    // Encrypt the plaintext
    ciphertext = encryptColumnarCipher(plaintext, keyword);
    cout << "Encrypted Text: " << ciphertext << endl;

    // Decrypt the ciphertext
    string decryptedText = decryptColumnarCipher(ciphertext, keyword);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
