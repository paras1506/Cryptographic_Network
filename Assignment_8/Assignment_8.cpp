#include <iostream>
#include <cmath>

using namespace std;

// Function to perform modular exponentiation (a^b % mod)
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Step 1: Publicly agree on a large prime number (p) and a primitive root (g)
    long long p = 23;  // Example prime number
    long long g = 5;   // Example primitive root

    cout << "Publicly Shared Prime (p): " << p << endl;
    cout << "Publicly Shared Primitive Root (g): " << g << endl;

    // Step 2: Each user chooses a private key
    long long a;  // Private key for User A
    long long b;  // Private key for User B

    cout << "Enter the private key for User A: ";
    cin >> a;

    cout << "Enter the private key for User B: ";
    cin >> b;

    // Step 3: Each user calculates their public value
    long long A = mod_exp(g, a, p);  // User A's public value
    long long B = mod_exp(g, b, p);  // User B's public value

    cout << "User A's Public Value (A): " << A << endl;
    cout << "User B's Public Value (B): " << B << endl;

    // Step 4: Each user computes the shared secret
    long long shared_secret_A = mod_exp(B, a, p);  // User A's computed shared secret
    long long shared_secret_B = mod_exp(A, b, p);  // User B's computed shared secret

    cout << "User A's Computed Shared Secret: " << shared_secret_A << endl;
    cout << "User B's Computed Shared Secret: " << shared_secret_B << endl;

    // If both computed shared secrets match, the exchange is successful
    if (shared_secret_A == shared_secret_B) {
        cout << "Shared secret successfully established: " << shared_secret_A << endl;
    } else {
        cout << "Error in establishing the shared secret." << endl;
    }

    return 0;
}
