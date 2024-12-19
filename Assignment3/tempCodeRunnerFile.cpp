#include <iostream>
#include <string>
using namespace std;

// Function to decrypt a single shift in Caesar Cipher
string decryptWithKey(const string &cipherText, int key) {
    string result = "";
    for (char c : cipherText) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char(int(base + (c - base - key + 26) % 26));
        } else {
            result += c; // Non-alphabet characters remain unchanged
        }
    }
    return result;
}

// Function to brute-force all possible keys in Caesar Cipher
void bruteForceCaesarCipher(const string &cipherText) {
    for (int key = 0; key < 26; key++) {
        string decryptedText = decryptWithKey(cipherText, key);
        cout << "Key " << key << ": " << decryptedText << endl;
    }
}

int main() {
    string cipherText;

    cout << "Enter the cipher text: ";
    getline(cin, cipherText);

    cout << "Brute-force results:" << endl;
    bruteForceCaesarCipher(cipherText);

    return 0;
}
