#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

class PlayfairCipher {
private:
    char matrix[5][5];
    string key;

    // Function to remove duplicates from the key
    string removeDuplicates(string s) {
        string result = "";
        vector<bool> seen(26, false);
        for (char c : s) {
            if (!seen[c - 'A']) {
                seen[c - 'A'] = true;
                result += c;
            }
        }
        return result;
    }

    // Function to preprocess the text (remove non-letters, convert to uppercase, replace J with I)
    string preprocessText(string text) {
        text.erase(remove_if(text.begin(), text.end(), [](char c) { return !isalpha(c); }), text.end());
        transform(text.begin(), text.end(), text.begin(), ::toupper);
        replace(text.begin(), text.end(), 'J', 'I');
        return text;
    }

    // Function to create the 5x5 matrix using the key
    void generateMatrix() {
        string matrixKey = removeDuplicates(key + "ABCDEFGHIKLMNOPQRSTUVWXYZ");
        vector<bool> seen(26, false);
        seen['J' - 'A'] = true; // J is omitted

        int k = 0;
        for (char c : matrixKey) {
            if (!seen[c - 'A']) {
                seen[c - 'A'] = true;
                matrix[k / 5][k % 5] = c;
                k++;
            }
        }
    }

    // Function to find the position of a character in the matrix
    void findPosition(char c, int &row, int &col) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (matrix[i][j] == c) {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }

    // Function to encrypt a pair of characters
    string encryptPair(char a, char b) {
        int row1, col1, row2, col2;
        findPosition(a, row1, col1);
        findPosition(b, row2, col2);

        if (row1 == row2) {
            // Same row: move to the right
            return string(1, matrix[row1][(col1 + 1) % 5]) + string(1, matrix[row2][(col2 + 1) % 5]);
        } else if (col1 == col2) {
            // Same column: move down
            return string(1, matrix[(row1 + 1) % 5][col1]) + string(1, matrix[(row2 + 1) % 5][col2]);
        } else {
            // Rectangle: swap columns
            return string(1, matrix[row1][col2]) + string(1, matrix[row2][col1]);
        }
    }

    // Function to decrypt a pair of characters
    string decryptPair(char a, char b) {
        int row1, col1, row2, col2;
        findPosition(a, row1, col1);
        findPosition(b, row2, col2);

        if (row1 == row2) {
            // Same row: move to the left
            return string(1, matrix[row1][(col1 + 4) % 5]) + string(1, matrix[row2][(col2 + 4) % 5]);
        } else if (col1 == col2) {
            // Same column: move up
            return string(1, matrix[(row1 + 4) % 5][col1]) + string(1, matrix[(row2 + 4) % 5][col2]);
        } else {
            // Rectangle: swap columns
            return string(1, matrix[row1][col2]) + string(1, matrix[row2][col1]);
        }
    }

public:
    PlayfairCipher(string key) {
        this->key = preprocessText(key);
        generateMatrix();
    }

    // Function to encrypt the plaintext
    string encrypt(string plaintext) {
        plaintext = preprocessText(plaintext);

        // Adjust plaintext to form pairs (inserting 'X' between identical letters and at the end if needed)
        for (int i = 0; i < plaintext.length(); i += 2) {
            if (i + 1 == plaintext.length() || plaintext[i] == plaintext[i + 1]) {
                plaintext.insert(i + 1, "X");
            }
        }

        string ciphertext = "";
        for (int i = 0; i < plaintext.length(); i += 2) {
            ciphertext += encryptPair(plaintext[i], plaintext[i + 1]);
        }
        return ciphertext;
    }

    // Function to decrypt the ciphertext
    string decrypt(string ciphertext) {
        ciphertext = preprocessText(ciphertext);
        string plaintext = "";

        for (int i = 0; i < ciphertext.length(); i += 2) {
            plaintext += decryptPair(ciphertext[i], ciphertext[i + 1]);
        }

        // Optionally remove padding character 'X' (if inserted during encryption)
        for (int i = 0; i < plaintext.length(); i++) {
            if (i + 1 < plaintext.length() && plaintext[i] == 'X' && plaintext[i - 1] == plaintext[i + 1]) {
                plaintext.erase(i, 1);
            }
        }
        return plaintext;
    }

    // Function to display the matrix (for debugging)
    void displayMatrix() {
        cout << "\nPlayfair Cipher Matrix:" << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << matrix[i][j] << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    string key, plaintext, ciphertext;

    cout << "Enter the key: ";
    getline(cin, key);

    PlayfairCipher playfair(key);

    // Display the matrix
    playfair.displayMatrix();

    cout << "\nEnter the plaintext: ";
    getline(cin, plaintext);

    ciphertext = playfair.encrypt(plaintext);
    cout << "Encrypted Text: " << ciphertext << endl;

    string decryptedText = playfair.decrypt(ciphertext);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
