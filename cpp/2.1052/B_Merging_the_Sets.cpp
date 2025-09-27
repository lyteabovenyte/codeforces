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
    int n, m;
    cin >> n >> m;

    vector<vector<int>> sets(n);
    vector<int> cnt(m + 1, 0);

    for (int i = 0; i < n; ++i) {
        int li;
        cin >> li;
        sets[i].resize(li);
        for (int j = 0; j < li; ++j) {
            int x;
            cin >> x;
            sets[i][j] = x;
            if (1 <= x && x <= m) cnt[x]++;
        }
    }

    for (int x = 1; x <= m; ++x) {
        if (cnt[x] == 0) {
            cout << "NO\n";
            return;
        }
    }

    vector<char> forced(n, false);
    for (int i = 0; i < n; ++i) {
        for (int x : sets[i]) {
            if (cnt[x] == 1) {
                forced[i] = true;
                break;
            }
        }
    }

    vector<char> covered_by_forced(m + 1, false);
    for (int i = 0; i < n; ++i)
        if (forced[i]) {
            for (int x : sets[i]) covered_by_forced[x] = true;
        }

    bool all_covered_by_forced = true;
    for (int x = 1; x <= m; ++x) {
        if (!covered_by_forced[x]) {
            all_covered_by_forced = false;
            break;
        }
    }

    if (all_covered_by_forced) {
        int non_forced = 0;
        for (int i = 0; i < n; ++i)
            if (!forced[i]) ++non_forced;
        cout << (non_forced >= 2 ? "YES\n" : "NO\n");
    } else {
        cout << "YES\n";
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
