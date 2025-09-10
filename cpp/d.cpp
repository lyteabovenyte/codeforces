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
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define sz(x) (int)(x).size()

using ll  = long long;
using ld  = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;
using vll = vector<ll>;

//--------------------------
// Constants
//--------------------------
const int INF  = 1e9;
const ll  LINF = 1e18;
const int MOD  = 1e9+7;
// const int MOD = 998244353;

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
    for (int &x : a) cin >> x;


    vll dp(n + 1), dp1(n + 1);
    dp[n] = 0;
    dp[n - 1] = a[n - 1];
    dp1[n] = 0;
    dp1[n - 1] = a[n - 1] - 1;
    for (int i = n - 2; i >= 0; i--) {
        int x = max(0ll, 1ll * a[i + 1] - i - 1);
        dp[i] = min(a[i] + dp1[i + 1], a[i] + x + dp1[i + 2]);
        dp1[i] = min(dp[i], a[i] - 1 + dp1[i + 1]);
    }
    cout << dp[0] << "\n";
}

//--------------------------
// Main
//--------------------------
int main() {
    fastio;
    int t;
    cin >> t; 
    while (t--) {
        solve();
    }
    return 0;
}