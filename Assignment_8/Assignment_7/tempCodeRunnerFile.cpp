#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
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

// Function to find the multiplicative inverse of e under mod phi
int mod_inverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

// Function to check if a number is prime
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
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
        e = rand() % phi;
    } while (gcd(e, phi) != 1);

    // Step 5: Compute d such that (d * e) % phi = 1 (d is the modular inverse of e)
    int d = mod_inverse(e, phi);

    // Display public and private keys
    cout << "Public Key: {" << e << ", " << n << "}\n";
    cout << "Private Key: {" << d << ", " << n << "}\n";

    // Step 6: Encryption
    int message;
    cout << "Enter the message (an integer): ";
    cin >> message;
    long long encrypted_message = mod_exp(message, e, n);
    cout << "Encrypted Message: " << encrypted_message << "\n";

    // Step 7: Decryption
    long long decrypted_message = mod_exp(encrypted_message, d, n);
    cout << "Decrypted Message: " << decrypted_message << "\n";

    return 0;
}
