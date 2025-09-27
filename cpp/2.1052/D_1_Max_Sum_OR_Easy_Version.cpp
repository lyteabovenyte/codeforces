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

using ll = long long;

// Recursively build the optimal reordering of `a` to match fixed `b`.
// Greedy at bit `bit`: move as many zeros of `a` as possible to positions where `b` has 1.
// Then recurse independently on those two blocks for lower bits.
static vector<ll> solve(const vector<ll>& a, const vector<ll>& b, int bit) {
    if (bit < 0 || a.size() <= 1) return a;

    vector<ll> A0, A1, B0, B1;
    A0.reserve(a.size());
    A1.reserve(a.size());
    B0.reserve(b.size());
    B1.reserve(b.size());

    for (ll x : a) ((x >> bit) & 1LL ? A1 : A0).push_back(x);
    for (ll x : b) ((x >> bit) & 1LL ? B1 : B0).push_back(x);

    size_t take0to1 = min(A0.size(), B1.size());

    vector<ll> aForB1;
    aForB1.reserve(B1.size());
    vector<ll> aForB0;
    aForB0.reserve(B0.size());

    // Fill B1 positions: as many zeros as possible, then ones.
    for (size_t i = 0; i < take0to1; ++i) aForB1.push_back(A0[i]);
    for (size_t i = 0; i < B1.size() - take0to1; ++i) aForB1.push_back(A1[i]);

    // Remaining elements go to B0 positions.
    for (size_t i = take0to1; i < A0.size(); ++i) aForB0.push_back(A0[i]);
    for (size_t i = B1.size() - take0to1; i < A1.size(); ++i) aForB0.push_back(A1[i]);

    // Recurse on lower bit.
    auto resB0 = solve(aForB0, B0, bit - 1);
    auto resB1 = solve(aForB1, B1, bit - 1);

    // Merge back following the original order of b.
    vector<ll> res;
    res.reserve(a.size());
    size_t p0 = 0, p1 = 0;
    for (ll y : b) {
        if ((y >> bit) & 1LL) res.push_back(resB1[p1++]);
        else
            res.push_back(resB0[p0++]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        long long l, r;
        cin >> l >> r;
        int n = int(r - l + 1);

        vector<ll> b;
        b.reserve(n);
        for (ll x = l; x <= r; ++x) b.push_back(x);

        vector<ll> a = b; // same multiset; we will reorder `a`
        // Highest relevant bit is 29 since r < 2^30
        vector<ll> perm = solve(a, b, 29);

        // Compute maximum sum
        long long ans = 0;
        for (int i = 0; i < n; ++i) ans += (perm[i] | b[i]);

        cout << ans << "\n";
        for (int i = 0; i < n; ++i) {
            cout << perm[i] << (i + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
