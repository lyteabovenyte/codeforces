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

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> r;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        r.push_back({ a, b });
    }

    int cs = 0;
    int ct = 0;
    int tp = 0;

    for (int i = 0; i < n; i++) {
        int dt = r[i].first;
        int ds = r[i].second;

        int td = dt - ct;
        int sd = abs(ds - cs);

        if (sd > td) {
            cout << -1 << "\n";
            return;
        }

        tp += sd;

        int et = td - sd;
        if (et > 0) {
            tp += (et / 2) * 2;
        }

        cs = ds;
        ct = dt;
    }

    int rt = m - ct;
    if (rt > 0) {
        tp += rt;
    }

    cout << tp << "\n";
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