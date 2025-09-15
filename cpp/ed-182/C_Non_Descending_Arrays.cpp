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
const int MXN = 2e5 + 5;

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] = 1;
    dp[0][1] = 1;

    for (int i = 1; i < n; i++) {
        if (a[i - 1] <= a[i] && b[i - 1] <= b[i]) dp[i][0] = (dp[i][0] + dp[i - 1][0]) % MOD;
        if (b[i - 1] <= a[i] && a[i - 1] <= b[i]) dp[i][0] = (dp[i][0] + dp[i - 1][1]) % MOD;

        if (a[i - 1] <= b[i] && b[i - 1] <= a[i]) dp[i][1] = (dp[i][1] + dp[i - 1][0]) % MOD;
        if (b[i - 1] <= b[i] && a[i - 1] <= a[i]) dp[i][1] = (dp[i][1] + dp[i - 1][1]) % MOD;
    }

    int ans = (dp[n - 1][0] + dp[n - 1][1]) % MOD;
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
