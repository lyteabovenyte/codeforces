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

// struct Mint {
//     int val;
//     Mint(int v = 0) : val(v % MOD) {
//         if (val < 0) val += MOD;
//     }
//     Mint& operator+=(const Mint& other) {
//         val = (val + other.val) % MOD;
//         return *this;
//     }
//     Mint& operator-=(const Mint& other) {
//         val = (val - other.val + MOD) % MOD;
//         return *this;
//     }
//     Mint& operator*=(const Mint& other) {
//         val = (val * other.val) % MOD;
//         return *this;
//     }
//     Mint operator+(const Mint& other) const { return Mint(*this) += other; }
//     Mint operator-(const Mint& other) const { return Mint(*this) -= other; }
//     Mint operator*(const Mint& other) const { return Mint(*this) *= other; }
//     bool operator==(const Mint& other) const { return val == other.val; }
//     Mint pow(long long exp) const {
//         Mint base = *this, res = 1;
//         while (exp > 0) {
//             if (exp & 1) res *= base;
//             base *= base;
//             exp >>= 1;
//         }
//         return res;
//     }
//     Mint inv() const {
//         return pow(MOD - 2);
//     }
//     Mint& operator/=(const Mint& other) {
//         return *this *= other.inv();
//     }
//     Mint operator/(const Mint& other) const { return Mint(*this) /= other; }
//     friend ostream& operator<<(ostream& os, const Mint& m) { return os << m.val; }
// };

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
// void solve() {
//     int n, m, k;
//     cin >> n >> m >> k;
//     vi a(n);
//     for (int i = 0; i < n; i++) {
//         cin >> a[i];
//     }
//     vi diff(n + 2);
//     vector<tuple<int, int, int>> ops(m);
//     for (int i = 0; i < m; i++) {
//         int l, r, x;
//         cin >> l >> r >> x;
//         l--; // make it zero-baesd
//         ops[i] = make_tuple(l, r, x);
//     }
//
//     for (int i = 0; i < k; i++) {
//         int x, y;
//         cin >> x >> y;
//         x--;
//         y--;
//         for (int j = x; j <= y; j++) {
//             diff[get<0>(ops[j])] += get<2>(ops[j]);
//             diff[get<1>(ops[j])] -= get<2>(ops[j]);
//         }
//     }
//
//     for (int i = 1; i < n; i++) {
//         diff[i] += diff[i - 1];
//         a[i] += diff[i];
//     }
//
//     for (int i = 0; i < n; i++) {
//         cout << a[i] << " ";
//     }
// }

void solve2() {
    int n, m, k;
    cin >> n >> m >> k;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vi diff(n + 2);
    vector<tuple<int, int, int>> ops(m + 1);
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        ops[i] = make_tuple(l, r, x);
    }

    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        for (int j = x; j <= y; j++) {
            diff[get<0>(ops[j])] += get<2>(ops[j]);
            diff[get<1>(ops[j]) + 1] -= get<2>(ops[j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        diff[i] += diff[i - 1];
        a[i] += diff[i];
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vi a(n + 2, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<pair<int, int>> ops(m + 2);
    vi val(m + 2);
    for (int i = 1; i <= m; i++) cin >> ops[i].first >> ops[i].second >> val[i];

    vi opsCount(m + 2, 0);
    while (k--) {
        int x, y;
        cin >> x >> y;
        y++;
        opsCount[x]++;
        opsCount[y]--;
    }
    for (int i = 1; i <= m; i++) opsCount[i] += opsCount[i - 1];

    vi dif(n + 2, 0);
    for (int i = 1; i <= m; i++) {
        if (opsCount[i]) {
            int l = ops[i].first, r = ops[i].second;
            r++;
            dif[l] += opsCount[i] * val[i];
            dif[r] -= opsCount[i] * val[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        dif[i] += dif[i - 1];
        a[i] += dif[i];
    }
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
}

signed main() {
    int t;
    solve();
    return 0;
}