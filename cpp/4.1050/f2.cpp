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
    int n;
    cin >> n;
    vector<vector<int>> arrays(n);
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        arrays[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> arrays[i][j];
        }
        if (k > max_len) {
            max_len = k;
        }
    }

    vector<int> min_for_col(max_len + 1, INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < arrays[i].size(); j++) {
            if (j + 1 <= max_len) {
                if (arrays[i][j] < min_for_col[j + 1]) {
                    min_for_col[j + 1] = arrays[i][j];
                }
            }
        }
    }

    sort(arrays.begin(), arrays.end(), [&](const vector<int>& a, const vector<int>& b) {
        int i = 0;
        int na = a.size(), nb = b.size();
        while (i < na && i < nb) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
            i++;
        }
        if (na > nb) {
            while (i < na && a[i] == min_for_col[i + 1]) {
                i++;
            }
            if (i < na) {
                return a[i] < min_for_col[i + 1];
            } else {
                return false;
            }
        } else if (na < nb) {
            while (i < nb && b[i] == min_for_col[i + 1]) {
                i++;
            }
            if (i < nb) {
                return min_for_col[i + 1] < b[i];
            } else {
                return false;
            }
        } else {
            return false;
        }
    });

    for (int j = 0; j < max_len; j++) {
        if (j < arrays[0].size()) {
            cout << arrays[0][j] << " ";
        } else {
            cout << min_for_col[j + 1] << " ";
        }
    }
    cout << "\n";
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