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
// Globals for one test
//--------------------------
struct SegTree {
    int n;
    vector<int> cnt1, cnt0, first1, first0, last1, last0, pairs1, pairs0;
    vector<char> flip;
    vector<int>& bound;

    SegTree(int n_, vector<int>& bound_) : n(n_), bound(bound_) {
        int SZ = 4 * n + 5;
        cnt1.assign(SZ, 0);
        cnt0.assign(SZ, 0);
        first1.assign(SZ, -1);
        first0.assign(SZ, -1);
        last1.assign(SZ, -1);
        last0.assign(SZ, -1);
        pairs1.assign(SZ, 0);
        pairs0.assign(SZ, 0);
        flip.assign(SZ, 0);
    }

    inline int in_sub(int i, int j) const {
        if (i <= 0 || j <= 0) return 0;
        return (j > i && j <= bound[i]) ? 1 : 0;
    }

    inline void pull(int p) {
        int L = p << 1, R = L | 1;
        cnt1[p] = cnt1[L] + cnt1[R];
        cnt0[p] = cnt0[L] + cnt0[R];

        first1[p] = (cnt1[L] ? first1[L] : first1[R]);
        first0[p] = (cnt0[L] ? first0[L] : first0[R]);

        last1[p] = (cnt1[R] ? last1[R] : last1[L]);
        last0[p] = (cnt0[R] ? last0[R] : last0[L]);

        pairs1[p] = pairs1[L] + pairs1[R];
        if (cnt1[L] && cnt1[R]) pairs1[p] += in_sub(last1[L], first1[R]);

        pairs0[p] = pairs0[L] + pairs0[R];
        if (cnt0[L] && cnt0[R]) pairs0[p] += in_sub(last0[L], first0[R]);
    }

    inline void apply_flip(int p) {
        flip[p] ^= 1;
        swap(cnt1[p], cnt0[p]);
        swap(first1[p], first0[p]);
        swap(last1[p], last0[p]);
        swap(pairs1[p], pairs0[p]);
    }

    inline void push(int p) {
        if (flip[p]) {
            apply_flip(p << 1);
            apply_flip(p << 1 | 1);
            flip[p] = 0;
        }
    }

    void build(int p, int l, int r, const vector<int>& arr) {
        if (l == r) {
            if (arr[l]) {
                cnt1[p] = 1;
                first1[p] = last1[p] = l;
                pairs1[p] = 0;
                cnt0[p] = 0;
                first0[p] = last0[p] = -1;
                pairs0[p] = 0;
            } else {
                cnt1[p] = 0;
                first1[p] = last1[p] = -1;
                pairs1[p] = 0;
                cnt0[p] = 1;
                first0[p] = last0[p] = l;
                pairs0[p] = 0;
            }
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, arr);
        build(p << 1 | 1, m + 1, r, arr);
        pull(p);
    }

    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            apply_flip(p);
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        if (ql <= m) update(p << 1, l, m, ql, qr);
        if (qr > m) update(p << 1 | 1, m + 1, r, ql, qr);
        pull(p);
    }

    inline int answer() const { return cnt1[1] - pairs1[1]; }
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    vector<int> tin(n + 1, 0), tout(n + 1, 0), order(n + 1, 0), parent(n + 1, 0);
    int timer = 0;
    vector<tuple<int, int, int>> st;
    st.reserve(2 * n);
    st.emplace_back(1, 0, 0);
    while (!st.empty()) {
        auto [u, p, state] = st.back();
        st.pop_back();
        if (state == 0) {
            parent[u] = p;
            tin[u] = ++timer;
            order[timer] = u;
            st.emplace_back(u, p, 1);
            for (int v : g[u])
                if (v != p) st.emplace_back(v, u, 0);
        } else {
            tout[u] = timer;
        }
    }

    vector<int> bound(n + 1, 0), arr(n + 1, 0);
    for (int pos = 1; pos <= n; ++pos) {
        int u = order[pos];
        bound[pos] = tout[u];
        arr[pos] = a[u];
    }

    SegTree stree(n, bound);
    stree.build(1, 1, n, arr);

    cout << stree.answer() << "\n";

    int q;
    cin >> q;
    while (q--) {
        int v;
        cin >> v;
        stree.update(1, 1, n, tin[v], tout[v]);
        cout << stree.answer() << "\n";
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
