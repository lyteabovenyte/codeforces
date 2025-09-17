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

#ifdef LOCAL
#define debug(x) cerr << #x << " = " << (x) << "\n";
#else
#define debug(x)
#endif

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    string s;
    cin >> n >> s;

    if (n % 2) {
        cout << -1 << '\n';
        return;
    }

    int K = 0;
    for (int i = 0; i < n; ++i) {
        int one_based_is_odd = ((i % 2) == 0);
        if ((one_based_is_odd && s[i] == '(') || (!one_based_is_odd && s[i] == ')'))
            ++K;
    }

    if (K == 0 || (K & 1)) {
        cout << -1 << '\n';
        return;
    }

    int needOddOpen = K / 2;
    int needEvenOpen = n / 2 - K / 2;

    string t;
    t.reserve(n);
    int bal = 0;
    for (int i = 0; i < n; ++i) {
        bool odd = (i % 2 == 0);
        if (odd) {
            if (needOddOpen > 0) {
                t.push_back('(');
                --needOddOpen;
                ++bal;
            } else {
                t.push_back(')');
                --bal;
            }
        } else {
            if (needEvenOpen > 0) {
                t.push_back('(');
                --needEvenOpen;
                ++bal;
            } else {
                t.push_back(')');
                --bal;
            }
        }
        if (bal < 0) {
        }
    }

    cout << t << '\n';
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

/*
observation:
K = '(' on odd positions + ')' on even positions (1-based)
    must be even and at least 2
for k:
    Construct any RBS with this K:
    need '(' on odd positions: K/2
    need '(' on even positions: n/2 - K/2

*/