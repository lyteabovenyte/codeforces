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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> prefZero(n + 1, 0);
    for (int i = 1; i <= n; ++i) prefZero[i] = prefZero[i - 1] + (a[i] == 0);

    vector<int> prefBad(n + 1, 0);
    for (int i = 1; i <= n - 1; ++i) prefBad[i] = prefBad[i - 1] + (a[i] == a[i + 1]);
    prefBad[n] = prefBad[n - 1];

    while (q--) {
        int l, r;
        cin >> l >> r;
        int m = r - l + 1;
        int zeros = prefZero[r] - prefZero[l - 1];
        int ones = m - zeros;

        if (zeros % 3 != 0 || ones % 3 != 0) {
            cout << -1 << '\n';
            continue;
        }

        long long ans = m / 3;

        bool alternating = ((m % 6 == 0) && ((prefBad[r - 1] - prefBad[l - 1]) == 0));

        if (alternating) ans += 1;
        cout << ans << '\n';
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
