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
    Mint pow(long long exp) const {
        Mint base = *this, res = 1;
        while (exp > 0) {
            if (exp & 1) res *= base;
            base *= base;
            exp >>= 1;
        }
        return res;
    }
    Mint inv() const {
        return pow(MOD - 2);
    }
    Mint& operator/=(const Mint& other) {
        return *this *= other.inv();
    }
    Mint operator/(const Mint& other) const { return Mint(*this) /= other; }
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
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vi initials(m);
    for (auto& x : initials) cin >> x;
    map<int, int> blocks;
    if (m > 0) {
        int st = initials[0], en = initials[0];
        for (int j = 1; j < m; ++j) {
            if (initials[j] == en + 1) {
                en = initials[j];
            } else {
                blocks[st] = en;
                st = en = initials[j];
            }
        }
        blocks[st] = en;
    }
    auto next_white_after = [&](int pos) -> int {
        int x = pos + 1;
        auto ub = blocks.upper_bound(x);
        if (ub == blocks.begin()) {
            return x;
        }
        auto pit = std::prev(ub);
        if (pit->first <= x && x <= pit->second) {
            return pit->second + 1;
        } else {
            return x;
        }
    };
    auto add_black = [&](int z) {
        auto it = blocks.upper_bound(z);
        bool is_black = false;
        auto prev_it = (it != blocks.begin()) ? std::prev(it) : blocks.end();
        if (prev_it != blocks.end() && prev_it->second >= z) {
            is_black = true;
        }
        if (is_black) return;
        bool merge_prev = (prev_it != blocks.end() && prev_it->second + 1 == z);
        auto next_it = it;
        bool merge_next = (next_it != blocks.end() && next_it->first == z + 1);
        int new_st = z;
        int new_en = z;
        if (merge_prev) {
            new_st = prev_it->first;
            new_en = z;
            blocks.erase(prev_it);
        }
        if (merge_next) {
            new_en = next_it->second;
            blocks.erase(next_it);
        }
        blocks[new_st] = new_en;
    };
    int curr = 1;
    for (int i = 0; i < n; ++i) {
        char cmd = s[i];
        int nextp;
        if (cmd == 'A') {
            nextp = curr + 1;
        } else {
            nextp = next_white_after(curr);
        }
        add_black(nextp);
        if (cmd == 'B') {
            curr = next_white_after(nextp);
        } else {
            curr = nextp;
        }
    }
    vi ans;
    for (auto& p : blocks) {
        for (int pos = p.first; pos <= p.second; ++pos) {
            ans.pb(pos);
        }
    }
    cout << sz(ans) << '\n';
    for (auto pos : ans) {
        cout << pos << ' ';
    }
    cout << '\n';
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