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
    cin >> n;
    int m = 2 * n;
    vector<int> ans(m + 1, 0);
    vector<int> nxt(m + 2);
    for (int i = 1; i <= m + 1; ++i) nxt[i] = i;

    auto findNext = [&](int start) -> int {
        if (start > m) return m + 1;
        int r = start;
        while (r <= m && nxt[r] != r) r = nxt[r];
        int cur = start;
        while (cur <= m && nxt[cur] != r) {
            int tmp = nxt[cur];
            nxt[cur] = r;
            cur = tmp;
        }
        return r;
    };

    for (int x = n; x >= 1; --x) {
        bool placed = false;
        int i = findNext(1);
        while (i <= m) {
            for (int q = i + x; q <= m; q += x) {
                if (findNext(q) == q) {
                    ans[i] = (int)x;
                    ans[q] = (int)x;
                    nxt[i] = findNext(i + 1);
                    nxt[q] = findNext(q + 1);
                    placed = true;
                    break;
                }
            }
            if (placed) break;
            i = findNext(i + 1);
        }
    }

    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << (i == m ? '\n' : ' ');
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
