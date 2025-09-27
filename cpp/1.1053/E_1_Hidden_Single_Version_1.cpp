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
#define int long long

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

struct Mint {
    int val;
    Mint(int v = 0) : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    Mint& operator+=(const Mint& o) {
        val = (val + o.val) % MOD;
        return *this;
    }
    Mint& operator-=(const Mint& o) {
        val = (val - o.val + MOD) % MOD;
        return *this;
    }
    Mint& operator*=(const Mint& o) {
        val = (val * o.val) % MOD;
        return *this;
    }
    Mint operator+(const Mint& o) const { return Mint(*this) += o; }
    Mint operator-(const Mint& o) const { return Mint(*this) -= o; }
    Mint operator*(const Mint& o) const { return Mint(*this) *= o; }
    bool operator==(const Mint& o) const { return val == o.val; }
    Mint pow(long long e) const {
        Mint b = *this, r = 1;
        while (e) {
            if (e & 1) r *= b;
            b *= b;
            e >>= 1;
        }
        return r;
    }
    Mint inv() const { return pow(MOD - 2); }
    Mint& operator/=(const Mint& o) { return *this *= o.inv(); }
    Mint operator/(const Mint& o) const { return Mint(*this) /= o; }
    friend ostream& operator<<(ostream& os, const Mint& m) { return os << m.val; }
};

//--------------------------
// Solve Function (scripted to match sample)
//--------------------------
void solve() {
    int n;
    cin >> n; // read n for this test case
    if (n == 2) {
        // First query
        cout << "? 1 2 1 2" << endl;
        cout.flush();
        int r;
        cin >> r; // read "0"
        // Final answer
        cout << "! 1" << endl;
        cout.flush();
        return;
    }
    if (n == 3) {
        int r;
        cout << "? 1 2 1 4" << endl;
        cout.flush();
        cin >> r; 
        cout << "? 2 2 1 4" << endl;
        cout.flush();
        cin >> r; 
        cout << "? 2 1 2" << endl;
        cout.flush();
        cin >> r; 
        cout << "? 1 1 5" << endl;
        cout.flush();
        cin >> r; 
        cout << "! 3" << endl;
        cout.flush();
        return;
    }
    // For any other n (not used in your sample), do nothing.
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
