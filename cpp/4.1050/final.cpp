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
using vvi = vector<vi>;

//--------------------------
// Constants
//--------------------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;

struct Mint {
    int val;
    Mint(int v = 0) : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    Mint& operator+=(const Mint& other) {
        val = (val + other.val) % MOD;
        return *this;
    }
    Mint& operator-=(const Mint& other) {
        val = (val - other.val + MOD) % MOD;
        return *this;
    }
    Mint& operator*=(const Mint& other) {
        val = (val * other.val) % MOD;
        return *this;
    }
    Mint operator+(const Mint& other) const { return Mint(*this) += other; }
    Mint operator-(const Mint& other) const { return Mint(*this) -= other; }
    Mint operator*(const Mint& other) const { return Mint(*this) *= other; }
    bool operator==(const Mint& other) const { return val == other.val; }
    friend ostream& operator<<(ostream& os, const Mint& m) { return os << m.val; }
};

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

    vvi a(n);
    int L = 0;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; ++j) cin >> a[i][j];
        L = max(L, k);
    }

    vector<vector<pair<int, int>>> columns(L);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sz(a[i]); ++j) {
            columns[j].push_back({ i, a[i][j] });
        }
    }

    vector<int> next_rank(n, -1);

    vector<int> best(L, -1);

    vector<tuple<int, int, int>> items;

    for (int j = L - 1; j >= 0; --j) {
        if (columns[j].empty()) continue;

        items.clear();
        items.reserve(columns[j].size());
        for (auto& p : columns[j]) {
            int i = p.first;
            int v = p.second;
            items.emplace_back(v, next_rank[i], i);
        }

        sort(all(items));

        best[j] = get<2>(items.front());

        int r = 0;
        int prev_v = get<0>(items[0]);
        int prev_nr = get<1>(items[0]);

        for (auto& t : items) {
            int v, nr, i;
            tie(v, nr, i) = t;
            if (v != prev_v || nr != prev_nr) {
                ++r;
                prev_v = v;
                prev_nr = nr;
            }
            next_rank[i] = r;
        }
    }

    int p = 0;
    while (p < L) {
        int i = best[p];
        for (int j = p; j < sz(a[i]); ++j) {
            cout << a[i][j] << (j + 1 == L ? '\n' : ' ');
        }
        p = sz(a[i]);
    }
    if (L == 0) cout << "\n";
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