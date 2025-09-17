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
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        long long x, y;
        cin >> u >> v >> x >> y;
        if (u > v) {
            swap(u, v);
            swap(x, y);
        }
        if (x > y) {
            g[v].push_back(u);
            indeg[u]++;
        } else {
            g[u].push_back(v);
            indeg[v]++;
        }
    }

    deque<int> q;
    for (int i = 1; i <= n; ++i)
        if (indeg[i] == 0) q.push_back(i);

    vector<int> order;
    order.reserve(n);
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        order.push_back(x);
        for (int to : g[x]) {
            indeg[to]--;
            if (indeg[to] == 0) q.push_back(to);
        }
    }

    assert((int)order.size() == n);

    vector<int> p(n + 1);
    for (int i = 0; i < n; ++i) p[order[i]] = i + 1;

    for (int i = 1; i <= n; ++i) {
        cout << p[i] << (i == n ? '\n' : ' ');
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
