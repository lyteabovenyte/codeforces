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

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    string s;
    cin >> n >> s;

    // map each zero position to an id
    vector<int> pos_to_id(n, -1);
    vector<int> zeros;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            pos_to_id[i] = (int)zeros.size();
            zeros.push_back(i);
        }
    }
    int m = (int)zeros.size();
    if (m == 0) { // no rabbits -> always safe
        cout << "YES\n";
        return;
    }

    vector<vector<int>> adj(m);
    vector<int> unary(m, -1); // -1 = none, 0 = must be L, 1 = must be R

    // build constraints from each '1'
    for (int j = 0; j < n; ++j) {
        if (s[j] != '1') continue;
        int l = j - 1;
        int r = j + 1;
        bool lz = (l >= 0 && s[l] == '0');
        bool rz = (r < n && s[r] == '0');
        if (lz && rz) {
            int u = pos_to_id[l];
            int v = pos_to_id[r];
            adj[u].push_back(v);
            adj[v].push_back(u);
        } else if (lz && !rz) {
            int u = pos_to_id[l];
            if (unary[u] == -1) unary[u] = 0;
            else if (unary[u] != 0) {
                cout << "NO\n";
                return;
            }
        } else if (rz && !lz) {
            int v = pos_to_id[r];
            if (unary[v] == -1) unary[v] = 1;
            else if (unary[v] != 1) {
                cout << "NO\n";
                return;
            }
        }
    }

    vector<int> visited(m, 0), assigned(m, -1);
    deque<int> dq;
    for (int i = 0; i < m; ++i) {
        if (visited[i]) continue;
        // collect component
        vector<int> comp;
        dq.clear();
        dq.push_back(i);
        visited[i] = 1;
        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();
            comp.push_back(u);
            for (int v : adj[u])
                if (!visited[v]) {
                    visited[v] = 1;
                    dq.push_back(v);
                }
        }
        // find a seed with unary constraint if exists
        int seed = -1;
        for (int u : comp)
            if (unary[u] != -1) {
                seed = u;
                break;
            }
        if (seed == -1) {
            seed = comp[0];
            assigned[seed] = 0; // arbitrary
        } else {
            assigned[seed] = unary[seed];
        }
        // propagate parity (edges mean different)
        dq.clear();
        dq.push_back(seed);
        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();
            if (unary[u] != -1 && unary[u] != assigned[u]) {
                cout << "NO\n";
                return;
            }
            for (int v : adj[u]) {
                if (assigned[v] == -1) {
                    assigned[v] = 1 - assigned[u];
                    dq.push_back(v);
                } else {
                    if (assigned[v] == assigned[u]) {
                        cout << "NO\n";
                        return;
                    }
                }
            }
        }
    }

    cout << "YES\n";
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
