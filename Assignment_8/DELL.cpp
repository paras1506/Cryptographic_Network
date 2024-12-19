#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Function to perform modular exponentiation (a^b % mod)
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod; // Square the base
    }
    return result;
}

// Function to check if a number is prime
bool is_prime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to find the prime factors of a number
vector<long long> prime_factors(long long n) {
    vector<long long> factors;
    for (long long i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            if (find(factors.begin(), factors.end(), i) == factors.end()) {
                factors.push_back(i);
            }
            n /= i;
        }
    }
    if (n > 1) factors.push_back(n); // If n is prime
    return factors;
}

// Function to check if g is a primitive root modulo p
bool is_primitive_root(long long g, long long p) {
    long long p_minus_1 = p - 1;
    vector<long long> factors = prime_factors(p_minus_1);

    // Check g^((p-1)/q) mod p for each prime factor q
    for (long long factor : factors) {
        if (mod_exp(g, p_minus_1 / factor, p) == 1) {
            return false; // g is not a primitive root
        }
    }
    return true; // g is a primitive root
}

int main() {
    // Step 1: Publicly agree on a large prime number (p)
    long long p = 23;  // Example prime number

    cout << "Publicly Shared Prime (p): " << p << endl;

    // Define a pool of candidate primitive roots
    vector<long long> candidates = {5, 7, 10, 11, 12}; // Example primitive roots for p = 23

    // Display available primitive roots
    cout << "Available primitive roots: ";
    for (long long candidate : candidates) {
        cout << candidate << " ";
    }
    cout << endl;

    // Step 2: User chooses a primitive root from the pool
    long long g;
    cout << "Choose a primitive root from the above list: ";
    cin >> g;

    // Verify if g is a primitive root modulo p
    if (is_primitive_root(g, p)) {
        cout << g << " is a primitive root modulo " << p << endl;
    } else {
        cout << g << " is NOT a primitive root modulo " << p << endl;
        return 1; // Exit if g is not a primitive root
    }

    // Step 3: Each user chooses a private key
    long long a;  // Private key for User A
    long long b;  // Private key for User B

    cout << "Enter the private key for User A: ";
    cin >> a;

    cout << "Enter the private key for User B: ";
    cin >> b;

    // Step 4: Each user calculates their public value
    long long A = mod_exp(g, a, p);  // User A's public value
    long long B = mod_exp(g, b, p);  // User B's public value

    cout << "User A's Public Value (A): " << A << endl;
    cout << "User B's Public Value (B): " << B << endl;

    // Step 5: Each user computes the shared secret
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
