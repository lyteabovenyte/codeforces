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

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n, y;
    cin >> n >> y;
    vi c(n);
    int Cmax = 0;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        Cmax = max(Cmax, c[i]);
    }

    vector<int> cnt(Cmax + 1, 0);
    for (int v : c) cnt[v]++;

    vector<int> pref(Cmax + 1, 0);
    for (int i = 1; i <= Cmax; ++i) pref[i] = pref[i - 1] + cnt[i];

    int best = -LINF;

    for (int x = 2; x <= Cmax + 1; ++x) {
        int Kmax = (Cmax + x - 1) / x;
        int sum_prices = 0;
        int reused = 0;

        for (int k = 1; k <= Kmax; ++k) {
            int L = (k - 1) * x + 1;
            int R = min(k * x, Cmax);
            int required_k = pref[R] - pref[L - 1];
            if (required_k == 0) continue;
            sum_prices += k * required_k;
            reused += min(required_k, cnt[k]);
        }

        int printed = n - reused;
        int income = sum_prices - y * printed;
        best = max(best, income);
    }

    cout << best << "\n";
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
