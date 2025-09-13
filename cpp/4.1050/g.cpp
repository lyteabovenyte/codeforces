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
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int n, a[200005], cnt[200005];
vector<int> divisors[200005];

void sieve() {
    for (int i = 1; i < 200005; i++)
        for (int j = 0; j < 200005; j += i)
            divisors[j].push_back(i);
}

void solve() {
    cin >> n;
    fill(cnt + 1, cnt + n + 1, 0);
    vector<int> vec;
    int ans = 0;
    int g1 = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int g2 = gcd(g1, a[i]);
        if (g1 != g2 && g1)
            for (int j : divisors[g1])
                if (g2 % j)
                    ans = max(ans, cnt[j]);
        g1 = g2;
        for (int j : divisors[a[i]]) {
            cnt[j]++;
            if (g1 % j) ans = max(ans, cnt[j]);
        }
        cout << ans << ' ';
    }
    cout << '\n';
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    int t;
    cin >> t;
    sieve();
    while (t--) {
        solve();
    }
    return 0;
}