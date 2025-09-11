#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
    vi points[n];
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = { x, y, i };
    }

    sort(points, points + n);

    int Fx[n], Fy[n];
    for (int i = 0; i < n; i++) {
        Fx[points[i][2]] = (i < n / 2 ? -1 : 1);
    }

    for (int i = 0; i < n; i++) {
        swap(points[i][0], points[i][1]);
    }
    sort(points, points + n);

    for (int i = 0; i < n; i++) {
        Fy[points[i][2]] = (i < n / 2 ? -1 : 1);
    }

    vi LP, LN, RP, RN;
    for (int i = 0; i < n; i++)
        if (Fx[i] == -1) {
            if (Fy[i] == -1) {
                LN.pb(i + 1);
            } else {
                LP.pb(i + 1);
            }
        } else {
            if (Fy[i] == -1)
                RN.pb(i + 1);
            else
                RP.pb(i + 1);
        }

    while (!LP.empty()) {
        cout << LP.back() << ' ' << RN.back() << "\n";
        LP.pop_back();
        RN.pop_back();
    }

    while (!LN.empty()) {
        cout << LN.back() << ' ' << RP.back() << "\n";
        LN.pop_back();
        RP.pop_back();
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