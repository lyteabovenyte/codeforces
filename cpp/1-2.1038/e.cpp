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
const int MOD = 998244353;

#define N 510
#define M 998244353

int a[2][N];
int k;

bool ok(int val) {
    return 1 <= val && val <= k;
}

int fun(int i, int d) {
    // a[1][i] - a[0][i + 1] = d
    // l - u = d
    int l = a[1][i], u = a[0][i + 1];
    if (l != -1 && u != -1) {
        return (l - u) == d;
    } else if (l == -1 && u != -1) {
        return ok(u + d);
    } else if (l != -1 && u == -1) {
        return ok(l - d);
    } else {
        return k - abs(d);
    }
}

//--------------------------
// Solve Function
//--------------------------
void solve() {

    int n;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[0][i];
    for (int i = 0; i < n; i++) cin >> a[1][i];

    int dp[n][k + 1], dpPos[n];

    for (int j = 0; j < n; j++)
        for (int i = 0; i <= k; i++) dp[j][i] = 0;

    for (int i = 0; i < n; i++) dpPos[i] = 0;

    dpPos[n - 1] = 1;

    for (int i = n - 2; i >= 0; i--) {
        // Positive at i
        for (int d = 1; d < k; d++) {
            int cnt = fun(i, d);
            // next is positive
            dpPos[i] += (cnt * dpPos[i + 1]) % M;
            dpPos[i] %= M;

            // next is negative with sum = s >= -d
            for (int s = 0; s <= d; s++) {
                dpPos[i] += (cnt * dp[i + 1][s]) % M;
                dpPos[i] %= M;
            }
        }

        // Negative at i
        for (int d = 0; d < k; d++) {
            int cnt = fun(i, -d);
            // next is positive
            dp[i][d] += (cnt * dpPos[i + 1]) % M;
            dp[i][d] %= M;

            // next is neg with sum s
            for (int s = 0; s <= k; s++) {
                if (d + s < k) {
                    dp[i][d + s] += (cnt * dp[i + 1][s]) % M;
                    dp[i][d + s] %= M;
                } else {
                    dp[i][k] += (cnt * dp[i + 1][s]) % M;
                    dp[i][k] %= M;
                }
            }
        }
    }

    int ans = dpPos[0];
    for (int i = 0; i <= k; i++) {
        ans += dp[0][i];
        ans %= M;
    }

    // cout << dpPos[0] << '\n';
    // for (int d = 0; d <= k; d++) cout << dp[0][d] << ' ';
    // cout << '\n';

    if (a[0][0] == -1) ans = (ans * k) % M;
    if (a[1][n - 1] == -1) ans = (ans * k) % M;

    cout << ans << '\n';
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
