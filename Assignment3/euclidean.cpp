#include <iostream>

using namespace std;

// Function to compute GCD using the Euclidean algorithm
int euclidean_algorithm(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute GCD and coefficients x and y using Extended Euclidean algorithm
int extended_euclidean_algorithm(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extended_euclidean_algorithm(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    while (true) {
        cout << "\nEuclidean and Extended Euclidean Algorithm" << endl;
        cout << "1. Compute GCD using Euclidean Algorithm" << endl;
        cout << "2. Compute GCD and coefficients using Extended Euclidean Algorithm" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int a, b;
            cout << "\nEnter the first integer (a): ";
            cin >> a;
            cout << "Enter the second integer (b): ";
            cin >> b;
            int gcd = euclidean_algorithm(a, b);
            cout << "\nGCD of " << a << " and " << b << " is: " << gcd << endl;
        } else if (choice == 2) {
            int a, b;
            cout << "\nEnter the first integer (a): ";
            cin >> a;
            cout << "Enter the second integer (b): ";
            cin >> b;
            int x, y;
            int gcd = extended_euclidean_algorithm(a, b, x, y);
            cout << "\nGCD of " << a << " and " << b << " is: " << gcd << endl;
            cout << "Coefficients x and y are: x = " << x << ", y = " << y << endl;
            cout << "\nBézout's identity: " << a << "*(" << x << ") + " << b << "*(" << y << ") = " << gcd << endl;
        } else if (choice == 3) {
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
