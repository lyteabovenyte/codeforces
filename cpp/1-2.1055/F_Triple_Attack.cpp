#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

//--------------------------
// Macros and Aliases
//--------------------------
#define fastio                   \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define int long long

using ll = long long;
using vi = vector<int>;

//--------------------------
// Constants
//--------------------------
const ll LINF = (ll)4e18;
const int LOG = 20; // 2^19 > 2.5e5, keep a bit extra

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    ll z;
    cin >> n >> z;

    vector<ll> x(n + 2, 0);
    for (int i = 1; i <= n; ++i) cin >> x[i];
    x[n + 1] = LINF; // sentinel

    // nxt[i] = first index > i with x[nxt[i]] > x[i] + z
    vector<int> nxt(n + 2, n + 1);
    for (int i = 1; i <= n; ++i) {
        int j = upper_bound(x.begin() + i + 1, x.begin() + n + 2, x[i] + z) - x.begin();
        nxt[i] = j; // in [i+1 .. n+1]
    }
    nxt[n + 1] = n + 1;

    // Binary lifting table for nxt
    static int jump[LOG][300005]; // sufficient for constraints across tests
    for (int i = 1; i <= n + 1; ++i) jump[0][i] = nxt[i];
    for (int k = 1; k < LOG; ++k) {
        for (int i = 1; i <= n + 1; ++i) {
            jump[k][i] = jump[k - 1][jump[k - 1][i]];
        }
    }

    // depth[i] = number of jumps from i to reach n+1
    vector<int> depth(n + 2, 0);
    depth[n + 1] = 0;
    for (int i = n; i >= 1; --i) {
        depth[i] = 1 + depth[nxt[i]];
    }

    auto count_until = [&](int start, int r) -> int {
        if (start > r) return 0;
        int cur = start;
        int cnt = 1; // include start
        for (int k = LOG - 1; k >= 0; --k) {
            int to = jump[k][cur];
            if (to <= r) {
                cnt += (1LL << k);
                cur = to;
            }
        }
        return cnt;
    };

    auto meet = [&](int a, int b) -> int {
        if (a > n) a = n + 1;
        if (b > n) b = n + 1;
        if (a == b) return a;
        // align depths (distance to sink)
        if (depth[a] > depth[b]) {
            int d = depth[a] - depth[b];
            for (int k = 0; k < LOG; ++k)
                if (d & (1LL << k)) a = jump[k][a];
        } else if (depth[b] > depth[a]) {
            int d = depth[b] - depth[a];
            for (int k = 0; k < LOG; ++k)
                if (d & (1LL << k)) b = jump[k][b];
        }
        if (a == b) return a;
        for (int k = LOG - 1; k >= 0; --k) {
            if (jump[k][a] != jump[k][b]) {
                a = jump[k][a];
                b = jump[k][b];
            }
        }
        return jump[0][a]; // first common node
    };

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        int len1 = count_until(l, r);
        int len2 = (l + 1 <= r) ? count_until(l + 1, r) : 0;

        int m = meet(l, l + 1);
        int overlap = (m <= r ? count_until(m, r) : 0);

        cout << (len1 + len2 - overlap) << '\n';
    }
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
