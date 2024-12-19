// Substitution Cipher
// (ceaser_cipher)
#include <iostream>
#include <string>
using namespace std;
// Function to encrypt the plaintext using Caesar Cipher
string encryptCaesarCipher(string plaintext, int shift) {
    string ciphertext = "";

    for (char& ch : plaintext) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = ((ch - base) + shift) % 26 + base;
        }
        ciphertext += ch;
    }

    return ciphertext;
}
// Function to decrypt the ciphertext using Caesar Cipher
string decryptCaesarCipher(string ciphertext, int shift) {
    return encryptCaesarCipher(ciphertext, 26 - shift);
}
int main() {
    string plaintext, ciphertext;
    int shift;
    // Input plaintext and shift value
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter shift: ";
    cin >> shift; // or key

    ciphertext = encryptCaesarCipher(plaintext, shift);
    cout << "Encrypted Text: " << ciphertext << endl;

    string decryptedText = decryptCaesarCipher(ciphertext, shift);
    cout << "Decrypted Text: " << decryptedText << endl;
    return 0;
}


// Plain Text: I am studying Data Encryption
// shift/key: 4
// Output: M eq wxyhCmrk Hexe IrgvCtxmsr