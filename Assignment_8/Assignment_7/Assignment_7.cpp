#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to calculate modular inverse of e under modulo phi
int extended_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Function to find the modular inverse using Extended Euclidean Algorithm
int mod_inverse(int e, int phi) {
    int x, y;
    int g = extended_gcd(e, phi, x, y);
    if (g != 1) {
        // No modular inverse exists
        return -1;
    } else {
        // Ensure x is positive
        return (x % phi + phi) % phi;
    }
}

// Function to perform modular exponentiation (x^y % p)
long long mod_exp(long long x, long long y, long long p) {
    long long result = 1;
    x = x % p;
    while (y > 0) {
        if (y % 2 == 1)
            result = (result * x) % p;
        y = y / 2;
        x = (x * x) % p;
    }
    return result;
}

// Function to check if a number is prime
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Function to convert an integer to hexadecimal string
string to_hex(int n) {
    stringstream ss;
    ss << hex << n;
    return ss.str();
}

// Function to convert a string to its ASCII integer representation
vector<int> string_to_ints(const string &str) {
    vector<int> intVec;
    for (char ch : str) {
        intVec.push_back(static_cast<int>(ch));
    }
    return intVec;
}

// Function to convert vector of integers back to a string
string ints_to_string(const vector<int> &intVec) {
    string str;
    for (int num : intVec) {
        str += static_cast<char>(num);
    }
    return str;
}

int main() {
    srand(time(0));

    // Step 1: Choose two large prime numbers p and q
    int p, q;
    do {
        p = rand() % 100 + 100; // Random number between 100 and 200
    } while (!is_prime(p));

    do {
        q = rand() % 100 + 100; // Random number between 100 and 200
    } while (!is_prime(q));

    // Step 2: Compute n = p * q
    int n = p * q;

    // Step 3: Compute the totient phi = (p - 1) * (q - 1)
    int phi = (p - 1) * (q - 1);

    // Step 4: Choose an integer e such that 1 < e < phi and gcd(e, phi) = 1
    int e;
    do {
        e = rand() % (phi - 2) + 2; // Ensure e is between 2 and phi-1
    } while (gcd(e, phi) != 1);

    // Step 5: Compute d such that (d * e) % phi = 1 (d is the modular inverse of e)
    int d = mod_inverse(e, phi);
    if (d == -1) {
        cout << "Failed to compute private key." << endl;
        return -1;
    }

    // Display public and private keys
    cout << "Public Key: {" << e << ", " << n << "}\n";
    cout << "Private Key: {" << d << ", " << n << "}\n";

    // Step 6: Encryption
    string message;
    cout << "Enter the message (a string): ";
    cin >> message;

    // Convert the string message to integers
    vector<int> messageInts = string_to_ints(message);
    vector<string> encryptedMessages;

    for (int m : messageInts) {
        long long encrypted_message = mod_exp(m, e, n);
        encryptedMessages.push_back(to_hex(encrypted_message)); // Convert to hex
    }

    // Display encrypted message in hexadecimal
    cout << "Encrypted Message (in hexadecimal): ";
    for (const string &hexMsg : encryptedMessages) {
        cout << hexMsg << " ";
    }
    cout << "\n";

    // Step 7: Decryption
    vector<int> decryptedMessages;
    for (const string &hexMsg : encryptedMessages) {
        long long enc_msg;
        stringstream ss;
        ss << hex << hexMsg;
        ss >> enc_msg;
        
        long long decrypted_message = mod_exp(enc_msg, d, n);
        decryptedMessages.push_back(static_cast<int>(decrypted_message)); // Store decrypted int
    }

    // Convert decrypted integers back to string
    string decryptedMessage = ints_to_string(decryptedMessages);
    cout << "Decrypted Message: " << decryptedMessage << "\n";

    return 0;
}
