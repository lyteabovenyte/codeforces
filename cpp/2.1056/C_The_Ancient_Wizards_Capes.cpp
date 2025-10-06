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

static inline int solve_one_case(int n, const vector<int>& a) {
    vector<long long> c(n + 1, 0), s(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        c[i] = a[i - 1] + (i - 1) - n;
        s[i] = c[i] - s[i - 1];
    }

    auto check = [&](long long p) -> bool {
        if (p < 0 || p > n) return false;
        long long pref = 0;
        for (int i = 1; i <= n; ++i) {
            long long x;
            if (i & 1) x = p + s[i] - s[i - 1];
            else
                x = s[i] - (p + s[i - 1]);
            if (!(x == 0 || x == 1)) return false;
            pref += x;
            if (pref < 0 || pref > i) return false;
        }
        return pref == p;
    };

    if (n % 2 == 0) {
        long long p = s[n];
        return check(p) ? 1 : 0;
    } else {
        if (s[n] != 0) return 0;
        unordered_set<long long> cand = { s[0] - s[1], s[0] - s[1] + 1 };
        for (int i = 2; i <= n; ++i) {
            unordered_set<long long> opt;
            if (i & 1) {
                opt.insert(s[i - 1] - s[i]);
                opt.insert(s[i - 1] - s[i] + 1);
            } else {
                opt.insert(s[i] - s[i - 1]);
                opt.insert(s[i] - s[i - 1] - 1);
            }
            unordered_set<long long> next;
            for (auto v : cand)
                if (opt.count(v)) next.insert(v);
            cand.swap(next);
            if (cand.empty()) return 0;
        }
        int cnt = 0;
        for (auto p : cand)
            if (check(p)) ++cnt;
        return cnt;
    }
}

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << solve_one_case(n, a) << "\n";
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    int t;
    if (!(cin >> t)) return 0;
    while (t--) solve();
    return 0;
}
