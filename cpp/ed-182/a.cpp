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
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int best_l = -1, best_r = -1, best_total_sum = -1;

    for (int l = 0; l < n - 2; l++) {
        for (int r = l + 1; r < n - 1; r++) {
            int s1 = 0, s2 = 0, s3 = 0;
            int total_sum = 0;

            for (int i = 0; i <= l; i++) {
                s1 += a[i];
                total_sum += a[i];
            }
            s1 %= 3;

            for (int i = l + 1; i <= r; i++) {
                s2 += a[i];
                total_sum += a[i];
            }
            s2 %= 3;

            for (int i = r + 1; i < n; i++) {
                s3 += a[i];
                total_sum += a[i];
            }
            s3 %= 3;

            if ((s1 != s2 && s2 != s3 && s1 != s3) || (s1 == s2 && s2 == s3)) {
                if (best_l == -1 || total_sum > best_total_sum || (total_sum == best_total_sum && l < best_l) || (total_sum == best_total_sum && l == best_l && r < best_r)) {
                    best_l = l;
                    best_r = r;
                    best_total_sum = total_sum;
                }
            }
        }
    }

    if (best_l != -1) {
        cout << best_l + 1 << " " << best_r + 1 << "\n";
    } else {
        cout << "0 0\n";
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