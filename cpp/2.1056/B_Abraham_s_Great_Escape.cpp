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

char delta_to_char(int dr, int dc) {
    if (dr == -1 && dc == 0) return 'U';
    if (dr == 1 && dc == 0) return 'D';
    if (dr == 0 && dc == -1) return 'L';
    if (dr == 0 && dc == 1) return 'R';
    return 'U';
}

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n, k;
    cin >> n >> k;
    int total = n * n;
    if (k == total - 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";

    vector<pair<int, int>> coords;
    coords.reserve(total);
    for (int r = 0; r < n; ++r) {
        if (r % 2 == 0) {
            for (int c = 0; c < n; ++c) coords.emplace_back(r, c);
        } else {
            for (int c = n - 1; c >= 0; --c) coords.emplace_back(r, c);
        }
    }

    vector<string> grid(n, string(n, '?'));

    for (int i = 0; i < k; ++i) {
        int r = coords[i].first, c = coords[i].second;
        if (i == 0) {
            if (r == 0) grid[r][c] = 'U';
            else if (c == 0)
                grid[r][c] = 'L';
            else
                grid[r][c] = 'U';
        } else {
            int pr = coords[i - 1].first, pc = coords[i - 1].second;
            grid[r][c] = delta_to_char(pr - r, pc - c);
        }
    }

    int m = total - k;
    if (m > 0) {
        for (int i = k; i <= total - 3; ++i) {
            int r = coords[i].first, c = coords[i].second;
            int nr = coords[i + 1].first, nc = coords[i + 1].second;
            grid[r][c] = delta_to_char(nr - r, nc - c);
        }

        int a = total - 2, b = total - 1;
        if (a >= k) {
            int r1 = coords[a].first, c1 = coords[a].second;
            int r2 = coords[b].first, c2 = coords[b].second;
            grid[r1][c1] = delta_to_char(r2 - r1, c2 - c1);
            grid[r2][c2] = delta_to_char(r1 - r2, c1 - c2);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << grid[i] << '\n';
    }
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
