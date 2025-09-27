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

//-----------------
// Segment Tree template (full version)
//-----------------
struct SegTree {
    int n;
    vector<long long> mx;
    vector<long long> lz;

    SegTree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        mx.assign(2 * n, 0);
        lz.assign(2 * n, 0);
    }

    void apply(int p, long long v) {
        mx[p] += v;
        lz[p] += v;
    }

    void push(int p) {
        if (lz[p] != 0) {
            apply(p << 1, lz[p]);
            apply(p << 1 | 1, lz[p]);
            lz[p] = 0;
        }
    }

    void range_add(int L, int R, long long v, int p, int l, int r) {
        if (L > R) return;
        if (L <= l && r <= R) {
            apply(p, v);
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        if (L <= m) range_add(L, R, v, p << 1, l, m);
        if (R > m) range_add(L, R, v, p << 1 | 1, m + 1, r);
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
    void range_add(int L, int R, long long v) {
        if (L <= R) range_add(L, R, v, 1, 0, n - 1);
    }

    void point_set(int idx, long long val, int p, int l, int r) {
        if (l == r) {
            mx[p] = val;
            lz[p] = 0;
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        if (idx <= m) point_set(idx, val, p << 1, l, m);
        else
            point_set(idx, val, p << 1 | 1, m + 1, r);
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
    void point_set(int idx, long long val) { point_set(idx, val, 1, 0, n - 1); }

    long long all_max() const { return mx[1]; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int maxA = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            maxA = max(maxA, a[i]);
        }
        int K = max(n, maxA) + 2;
        SegTree st(K);

        for (int i = 0; i < n; ++i) {
            int x = a[i];
            if (x > 0) st.range_add(0, x - 1, 1);
            st.point_set(x, 0);
            cout << st.all_max() << (i + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
