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

//--------------------------
// Macros and Aliases
//--------------------------
#define fastio                   \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define sz(x) (int)(x).size()
// #define int long long

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

//--------------------------
// Constants
//--------------------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
// const int MOD = 998244353;

struct Mint {
    int val;
    Mint(int v = 0) : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    Mint& operator+=(const Mint& other) {
        val = (val + other.val) % MOD;
        return *this;
    }
    Mint& operator-=(const Mint& other) {
        val = (val - other.val + MOD) % MOD;
        return *this;
    }
    Mint& operator*=(const Mint& other) {
        val = (val * other.val) % MOD;
        return *this;
    }
    Mint operator+(const Mint& other) const { return Mint(*this) += other; }
    Mint operator-(const Mint& other) const { return Mint(*this) -= other; }
    Mint operator*(const Mint& other) const { return Mint(*this) *= other; }
    bool operator==(const Mint& other) const { return val == other.val; }
    Mint pow(long long exp) const {
        Mint base = *this, res = 1;
        while (exp > 0) {
            if (exp & 1) res *= base;
            base *= base;
            exp >>= 1;
        }
        return res;
    }
    Mint inv() const {
        return pow(MOD - 2);
    }
    Mint& operator/=(const Mint& other) {
        return *this *= other.inv();
    }
    Mint operator/(const Mint& other) const { return Mint(*this) /= other; }
    friend ostream& operator<<(ostream& os, const Mint& m) { return os << m.val; }
};

//--------------------------
// Debug Utilities (disabled on judge)
//--------------------------
#ifdef LOCAL
#define debug(x) cerr << #x << " = " << (x) << "\n";
#else
#define debug(x)
#endif

int fact(int n) {
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        ans *= i;
    }
    return ans;
}

//--------------------------
// Solve Function
//--------------------------
void solve() {
}
//--------------------------
// Main
//--------------------------
#include <iostream>
#include <iomanip>
#include <cstdlib>

int main(int argc, char** argv) {
    // Defaults: 365 days, 50% target probability
    long double days = 365.0L;
    long double target = 0.5L;

    if (argc >= 2) days = std::stold(argv[1]);   // e.g., ./a.out 365
    if (argc >= 3) target = std::stold(argv[2]); // e.g., ./a.out 365 0.5

    if (days <= 0.0L || target <= 0.0L || target >= 1.0L) {
        std::cerr << "Invalid input. days must be > 0 and 0 < target < 1.\n";
        return 1;
    }

    // p_no: probability that all birthdays are distinct among n people
    long double p_no = 1.0L;
    int n = 0;

    // Incrementally add people until 1 - p_no >= target
    while (true) {
        // Add the (n+1)-th person
        n++;
        // Multiply by the probability that this person's birthday is new
        p_no *= (days - (n - 1)) / days;

        long double p_shared = 1.0L - p_no;
        if (p_shared + 1e-18L >= target) { // tiny tolerance for rounding
            std::cout << std::fixed << std::setprecision(10);
            std::cout << "Minimum n = " << n << "\n";
            std::cout << "P(at least one shared birthday) = " << p_shared << "\n";
            std::cout << "Assumptions: " << (int)days << " equally likely birthdays, no leap day.\n";
            break;
        }

        // Safety: can't have more unique birthdays than 'days'
        if (n >= static_cast<int>(days)) {
            std::cout << "n reached " << n << " (days=" << days
                      << ") without meeting target probability " << target << ".\n";
            break;
        }
    }

    return 0;
}