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
// Solve Function
//--------------------------
void solve() {
    int n;
    string s;
    cin >> n >> s;

    vector<int> ans;
    ans.reserve(n);
    int last = 0; // last index where s[last-1] == '1' (0 means none yet)
    // process positions 1..n
    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] == '1') {
            int start = last + 1;
            int end = i - 1;
            vector<int> tmp;
            tmp.reserve(max(0LL, end - start + 1));
            int k = start;
            while (k + 1 <= end) {
                tmp.push_back(k + 1);
                tmp.push_back(k);
                k += 2;
            }
            if (k <= end) tmp.push_back(k); // leftover if odd count
            int L = end - start + 1;
            if ((L % 2) == 1 && !tmp.empty()) {
                // rotate tmp: move last element to front to avoid creating
                // a fixed point at position end when s[end] == '0'
                int lastv = tmp.back();
                tmp.pop_back();
                tmp.insert(tmp.begin(), lastv);
            }
            for (int v : tmp) ans.push_back(v);
            ans.push_back(i); // ensure i becomes stable
            last = i;
        }
    }
    // trailing zeros (after last '1') from last+1 .. n
    {
        int start = last + 1;
        int end = n;
        vector<int> tmp;
        tmp.reserve(max(0LL, end - start + 1));
        int k = start;
        while (k + 1 <= end) {
            tmp.push_back(k + 1);
            tmp.push_back(k);
            k += 2;
        }
        if (k <= end) tmp.push_back(k);
        int L = end - start + 1;
        if ((L % 2) == 1 && !tmp.empty()) {
            int lastv = tmp.back();
            tmp.pop_back();
            tmp.insert(tmp.begin(), lastv);
        }
        for (int v : tmp) ans.push_back(v);
    }

    if ((int)ans.size() != n) {
        cout << "NO\n";
        return;
    }
    // safety: check ans is a permutation of 1..n
    vector<char> seen(n + 1, 0);
    for (int v : ans) {
        if (v < 1 || v > n || seen[v]) {
            cout << "NO\n";
            return;
        }
        seen[v] = 1;
    }

    // compute stable string from constructed permutation and compare with s
    // stable condition: value x is stable iff its position is x and prefix max up to x equals x
    vector<int> pos(n + 1, 0);
    for (int i = 0; i < n; ++i) pos[ans[i]] = i + 1; // 1-indexed positions
    vector<int> prefmax(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefmax[i] = max(prefmax[i - 1], ans[i - 1]);
    }
    string got(n, '0');
    for (int x = 1; x <= n; ++x) {
        if (pos[x] == x && prefmax[x] == x) got[x - 1] = '1';
    }

    if (got != s) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
