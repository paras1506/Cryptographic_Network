#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to encrypt the plaintext using Rail Fence Cipher
string encryptRailFenceCipher(string plaintext, int key) {
    if (key == 1) {
        return plaintext;  // No change if key is 1
    }

    vector<string> rail(key);
    int row = 0;
    bool directionDown = true;

    // Place characters in a zigzag pattern across the rails
    for (char& ch : plaintext) {
        rail[row] += ch;

        if (row == 0) {
            directionDown = true;
        } else if (row == key - 1) {
            directionDown = false;
        }

        row += directionDown ? 1 : -1;
    }

    // Read the rails line by line to create the ciphertext
    string ciphertext = "";
    for (const string& line : rail) {
        ciphertext += line;
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using Rail Fence Cipher
string decryptRailFenceCipher(string ciphertext, int key) {
    if (key == 1) {
        return ciphertext;  // No change if key is 1
    }

    vector<string> rail(key);
    vector<int> index(key, 0);
    int length = ciphertext.length();
    int row = 0;
    bool directionDown = true;

    // Determine the length of each rail
    for (int i = 0; i < length; i++) {
        index[row]++;
        if (row == 0) {
            directionDown = true;
        } else if (row == key - 1) {
            directionDown = false;
        }
        row += directionDown ? 1 : -1;
    }

    // Fill the rails with the ciphertext
    int pos = 0;
    for (int r = 0; r < key; r++) {
        rail[r] = ciphertext.substr(pos, index[r]);
        pos += index[r];
    }

    // Read the rails in a zigzag pattern to decrypt the text
    string plaintext = "";
    row = 0;
    directionDown = true;

    for (int i = 0; i < length; i++) {
        plaintext += rail[row][0];
        rail[row].erase(rail[row].begin());

        if (row == 0) {
            directionDown = true;
        } else if (row == key - 1) {
            directionDown = false;
        }

        row += directionDown ? 1 : -1;
    }

    return plaintext;
}

int main() {
    string plaintext, ciphertext;
    int key;

    // Input plaintext and key
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter key (number of rails): ";
    cin >> key;

    // Encrypt the plaintext
    ciphertext = encryptRailFenceCipher(plaintext, key);
    cout << "Encrypted Text: " << ciphertext << endl;

    // Decrypt the ciphertext
    string decryptedText = decryptRailFenceCipher(ciphertext, key);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
