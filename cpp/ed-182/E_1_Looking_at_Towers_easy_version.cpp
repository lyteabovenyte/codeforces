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
// const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MOD = 998244353;

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

Mint compute_left(const vll& a, int st, int en, const vector<ll>& ch) {
    int le = en - st + 1;
    if (le < 0) le = 0;
    int ssz = ch.size();
    vector<vector<Mint>> dp(le + 1, vector<Mint>(ssz + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < le; i++) {
        int id = st + i;
        ll h = a[id];
        for (int pl = 0; pl <= ssz; pl++) {
            Mint w = dp[i][pl];
            if (w.val == 0) continue;
            ll cb = (pl == 0 ? 0LL : ch[pl - 1]);
            bool cex = (h <= cb);
            bool isn = (pl < ssz && h == ch[pl]);
            if (cex) dp[i + 1][pl] += w * Mint(2);
            else
                dp[i + 1][pl] += w;
            if (isn) dp[i + 1][pl + 1] += w;
        }
    }
    return dp[le][ssz];
}

Mint compute_right(const vll& a, int st, int en, const vector<ll>& ch) {
    int le = en - st + 1;
    if (le < 0) le = 0;
    int ssz = ch.size();
    vector<vector<Mint>> dp(le + 1, vector<Mint>(ssz + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < le; i++) {
        int id = st + 1;
        ll h = a[id];
        for (int pl = 0; pl <= ssz; pl++) {
            Mint w = dp[i][pl];
            if (w.val == 0) continue;
            ll cb = (pl == ssz ? 0LL : ch[pl]);
            bool cex = (h <= cb);
            bool isn = (pl < ssz && h == ch[pl]);
            if (cex) dp[i + 1][pl] += w * Mint(2);
            else
                dp[i + 1][pl] += w;
            if (isn) dp[i + 1][pl + 1] += w;
        }
    }
    return dp[le][ssz];
}

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    cin >> n;
    vll a(n);
    for (auto& x : a) cin >> x;
    set<ll> Lset, Rset;
    ll curmax = 0;
    for (auto x : a) {
        if (x > curmax) {
            Lset.insert(x);
            curmax = x;
        }
    }
    curmax = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] > curmax) {
            Rset.insert(a[i]);
            curmax = a[i];
        }
    }
    if (n == 0) {
        cout << 1 << "\n";
        return;
    }

    ll maxh = *Lset.rbegin();
    vector<ll> leftc(Lset.begin(), Lset.end());
    int pp = leftc.size();
    vector<ll> rightc(Rset.rbegin(), Rset.rend());
    int qq = rightc.size();
    vector<ll> bb;
    for (int i = 0; i < pp; i++) {
        bb.pb(leftc[i]);
    }
    int ss = bb.size();
    vector<ll> cc;
    for (int i = 1; i < qq; i++) {
        cc.pb(rightc[i]);
    }
    int tt = cc.size();
    vi maxposs;
    for (int i = 0; i < n; i++) {
        if (a[i] == maxh) {
            maxposs.pb(i);
        }
    }
    Mint ans = 0;
    for (int kk : maxposs) {
        Mint lways = compute_left(a, 0, kk - 1, bb);
        Mint rways = compute_right(a, kk + 1, n - 1, cc);
        ans += lways * rways;
    }
    cout << ans << "\n";
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