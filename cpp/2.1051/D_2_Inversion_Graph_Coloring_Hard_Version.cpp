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
    Mint(int v = 0) : val((v % MOD + MOD) % MOD) {}
    Mint& operator+=(const Mint& o) {
        val += o.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    Mint& operator-=(const Mint& o) {
        val -= o.val;
        if (val < 0) val += MOD;
        return *this;
    }
    Mint& operator*=(const Mint& o) {
        val = (ll)val * o.val % MOD;
        return *this;
    }
    Mint operator+(const Mint& o) const { return Mint(*this) += o; }
    Mint operator-(const Mint& o) const { return Mint(*this) -= o; }
    Mint operator*(const Mint& o) const { return Mint(*this) *= o; }
    friend ostream& operator<<(ostream& os, const Mint& m) { return os << m.val; }
};

//--------------------------
// Fenwick (BIT) template for prefix sums (0-indexed keys)
//--------------------------
struct BIT {
    int n;
    vector<int> bit; // values modulo MOD
    BIT() : n(0) {}
    BIT(int _n) { init(_n); }
    void init(int _n) {
        n = _n;
        bit.assign(n + 1, 0);
    }
    void add(int idx, int v) { // add to index idx (0-based)
        for (int i = idx + 1; i <= n; i += i & -i) {
            bit[i] += v;
            if (bit[i] >= MOD) bit[i] -= MOD;
        }
    }
    int sumPref(int idx) const { // sum [0..idx]
        if (idx < 0) return 0;
        int r = 0;
        for (int i = idx + 1; i > 0; i -= i & -i) {
            r += bit[i];
            if (r >= MOD) r -= MOD;
        }
        return r;
    }
    int rangeSum(int l, int r) const { // sum [l..r]
        if (r < l) return 0;
        int res = sumPref(r) - sumPref(l - 1);
        if (res < 0) res += MOD;
        return res;
    }
};

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int m = n + 1;

    vector<BIT> row(m, BIT(m)), col(m, BIT(m));

    auto add_cell = [&](int r, int c, int val) {
        if (val == 0) return;
        row[r].add(c, val);
        col[c].add(r, val);
    };

    int total = 0;
    add_cell(0, 0, 1);
    total = (total + 1) % MOD;

    for (int x : a) {
        for (int t2 = x + 1; t2 <= n; ++t2) {
            int ways = col[t2].sumPref(x);
            if (ways) {
                add_cell(x, t2, ways);
                total += ways;
                if (total >= MOD) total -= MOD;
            }
        }
        for (int t1 = 0; t1 <= x; ++t1) {
            int ways = row[t1].rangeSum(t1, x);
            if (ways) {
                add_cell(t1, x, ways);
                total += ways;
                if (total >= MOD) total -= MOD;
            }
        }
    }

    cout << total % MOD << "\n";
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
