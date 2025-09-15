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

int val(int n) {
    int ans = 0;
    for (int a2 = 0; a2 < 2; a2++) {
        for (int a3 = 0; a3 < 2; a3++) {
            for (int a5 = 0; a5 < 2; a5++) {
                for (int a7 = 0; a7 < 2; a7++) {
                    int ct = 0, div = 1;
                    if (a2) {
                        div *= 2;
                        ct++;
                    }
                    if (a3) {
                        div *= 3;
                        ct++;
                    }
                    if (a5) {
                        div *= 5;
                        ct++;
                    }
                    if (a7) {
                        div *= 7;
                        ct++;
                    }
                    if (ct % 2 == 0) {
                        ans += n / div;
                    } else {
                        ans -= n / div;
                    }
                }
            }
        }
    }
    return ans;
}
//--------------------------
// Solve Function
//--------------------------
void solve2() {
    int l, r;
    cin >> l >> r;
    cout << val(r) - val(l - 1) << "\n";
}

bool good(int x) {
    return (x % 2 && x % 3 && x % 5 && x % 7);
}

int get_naive(int x) {
    int ans = 0;
    for (int i = 0; i < x; i++) {
        if (good(i)) ans++;
    }
    return ans;
}

int get(int r) {
    return (r / 210) * get_naive(210) + get_naive(r % 210);
}

void solve() {
    int l, r;
    cin >> l >> r;
    cout << get(r + 1) - get(l) << "\n";
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}