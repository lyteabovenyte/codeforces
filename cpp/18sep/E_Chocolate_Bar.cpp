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

const int N = 30 + 3, K = 50 + 5;
int dp[N][N][K];

void fill_dp() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int l = 0; l < K; l++) {
                if (l > i * j) {
                    dp[i][j][l] = INF;
                    continue;
                }
                if (l == 0 || l == i * j) {
                    dp[i][j][l] = 0;
                    continue;
                }

                // dp update
                dp[i][j][l] = INF;

                // horizontal
                for (int i1 = 1; i1 < i; i1++) {
                    for (int l1 = 0; l1 <= l; l1++) {
                        int i2 = i - i1, l2 = l - l1;
                        dp[i][j][l] = min(dp[i][j][l], dp[i1][j][l1] + dp[i2][j][l2] + j * j);
                    }
                }

                // vertical
                for (int j1 = 1; j1 < j; j1++) {
                    for (int l1 = 0; l1 <= l; l1++) {
                        int j2 = j - j1, l2 = l - l1;
                        dp[i][j][l] = min(dp[i][j][l], dp[i][j1][l1] + dp[i][j2][l2] + i * i);
                    }
                }
            }
        }
    }
}

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    cout << dp[n][m][k] << "\n";
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    fill_dp();
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        cout << dp[n][m][k] << "\n";
    }
    return 0;
}