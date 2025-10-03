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
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;

struct Mint { // (unused)
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
        val = (1LL * val * o.val) % MOD;
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

//--------------------------
void solve() {
    long long n, rk, ck, rd, cd;
    cin >> n >> rk >> ck >> rd >> cd;

    long long minRow = max(0LL, rk - 1);
    long long maxRow = min(n, rk + 1);
    long long minCol = max(0LL, ck - 1);
    long long maxCol = min(n, ck + 1);

    bool canTop = (minRow <= rd - 2);
    bool canBottom = (maxRow >= rd + 2);
    bool canLeft = (minCol <= cd - 2);
    bool canRight = (maxCol >= cd + 2);

    long long ans = 1;

    if (canTop) ans = max(ans, rd);
    if (canBottom) ans = max(ans, n - rd);
    if (canLeft) ans = max(ans, cd);
    if (canRight) ans = max(ans, n - cd);

    cout << ans << "\n";
}

//--------------------------
int32_t main() {
    fastio;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
