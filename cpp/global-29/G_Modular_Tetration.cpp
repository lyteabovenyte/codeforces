#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <bitset>
#include <numeric>
#include <functional>
#include <climits>
#include <limits>
#include <iomanip>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;

const int MOD = 998244353;

// Function for modular exponentiation (a^b mod m)
long long mod_exp(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b /= 2;
    }
    return result;
}

// Function for computing modular inverse of a under modulo m
long long mod_inv(long long a, long long m) {
    return mod_exp(a, m - 2, m);
}

int main() {
    int t;
    std::cin >> t; // Number of test cases

    while (t--) {
        long long x, y, z;
        std::cin >> x >> y >> z;

        // Calculate m = xyz
        long long m = x * y * z;

        // Finding the modular density for m-tetrative integers
        long long p = mod_exp(x, y, MOD);
        long long q = mod_exp(z, 1, MOD);
        long long q_inv = mod_inv(q, MOD);

        // Calculate the final result x = p * q^(-1) % M
        long long result = (p * q_inv) % MOD;

        std::cout << result << std::endl;
    }

    return 0;
}
