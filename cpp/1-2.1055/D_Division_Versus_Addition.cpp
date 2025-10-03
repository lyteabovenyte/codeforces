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

// y > 0
static inline bool is_pow2(unsigned long long y) {
    return y && ((y & (y - 1)) == 0);
}

static inline int ceil_log2_ull(unsigned long long y) {
    if (y <= 1) return 0;
    return 64 - __builtin_clzll(y - 1);
}

static inline long long single_val(unsigned long long x) {
    if (x == 1) return 0;
    unsigned long long y = x - 1;
    int m = ceil_log2_ull(y);
    if (m == 0) return 1;
    return m;
}

void solve_one() {
    int n, q;
    cin >> n >> q;
    vector<unsigned long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<long long> prefVal(n + 1, 0);
    vector<int> prefSpecial(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        prefVal[i] = prefVal[i - 1] + single_val(a[i]);
        int special = (a[i] >= 3 && is_pow2(a[i] - 1)) ? 1 : 0;
        prefSpecial[i] = prefSpecial[i - 1] + special;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        long long base = prefVal[r] - prefVal[l - 1];
        int cntSp = prefSpecial[r] - prefSpecial[l - 1];
        cout << base + (cntSp / 2) << '\n';
    }
}

int32_t main() {
    fastio;
    int T;
    if (!(cin >> T)) return 0;
    while (T--) solve_one();
    return 0;
}
