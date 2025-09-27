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
// Problem modulus:
const int MOD = 998244353;
const int MXN = 200000 + 5;

struct Mint {
    int val;
    Mint(long long v = 0) {
        long long x = v % MOD;
        if (x < 0) x += MOD;
        val = (int)x;
    }
    Mint& operator+=(const Mint& other) {
        val += other.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    Mint& operator-=(const Mint& other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }
    Mint& operator*=(const Mint& other) {
        val = (int)((1LL * val * other.val) % MOD);
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
// Precompute factorials
//--------------------------
vector<Mint> fact(MXN), invfact(MXN);

void precompute_factorials(int up_to = MXN - 1) {
    fact[0] = 1;
    for (int i = 1; i <= up_to; ++i) fact[i] = fact[i - 1] * Mint(i);
    invfact[up_to] = fact[up_to].inv();
    for (int i = up_to - 1; i >= 0; --i) invfact[i] = invfact[i + 1] * Mint(i + 1);
}

Mint nCr(int n, int r) {
    if (r < 0 || r > n) return Mint(0);
    return fact[n] * invfact[r] * invfact[n - r];
}

//--------------------------
// Solve Function
//--------------------------
void solve_one() {
    int n;
    cin >> n;
    vector<int> a(n);
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum != n) {
        cout << 0 << '\n';
        return;
    }
    int R = (n + 1) / 2;
    for (int r = R; r < n; ++r) {
        if (a[r] != 0) {
            cout << 0 << '\n';
            return;
        }
    }
    Mint ans = 1;
    long long used_above = 0; 
    for (int r = R; r >= 1; --r) {
        long long s_r = n - 2LL * (r - 1);
        long long avail = s_r - used_above;
        if (avail < a[r - 1]) {
            cout << 0 << '\n';
            return;
        }
        ans *= nCr((int)avail, (int)a[r - 1]);
        used_above += a[r - 1];
    }
    cout << ans << '\n';
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    precompute_factorials(MXN - 1);
    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
