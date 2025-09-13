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

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

void solve() {
    int n;
    cin >> n;
    vector<vi> arrays(n);
    int maxk = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        arrays[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> arrays[i][j];
        }
        maxk = max(maxk, (int)arrays[i].size());
    }

    if (n <= 6) {
        vi best_bottom(maxk, INF);

        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);

        do {
            vector<vi> grid(n, vi(maxk, 0));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < sz(arrays[perm[i]]); j++) {
                    grid[i][j] = arrays[perm[i]][j];
                }
            }

            for (int col = 0; col < maxk; col++) {
                int write_pos = n - 1;
                for (int row = n - 1; row >= 0; row--) {
                    if (grid[row][col] != 0) {
                        if (write_pos != row) {
                            grid[write_pos][col] = grid[row][col];
                            grid[row][col] = 0;
                        }
                        write_pos--;
                    }
                }
            }

            vi bottom(maxk, 0);
            for (int j = 0; j < maxk; j++) {
                bottom[j] = grid[n - 1][j];
            }

            if (bottom < best_bottom) {
                best_bottom = bottom;
            }
        } while (next_permutation(perm.begin(), perm.end()));

        bool first = true;
        for (int val : best_bottom) {
            if (val != 0) {
                if (!first) cout << " ";
                cout << val;
                first = false;
            }
        }
        cout << "\n";
    } else {
        vector<multiset<int>> columns(maxk);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < sz(arrays[i]); j++) {
                columns[j].insert(arrays[i][j]);
            }
        }

        vi result;
        for (int col = 0; col < maxk; col++) {
            if (!columns[col].empty()) {
                result.push_back(*columns[col].begin());
            }
        }

        for (int i = 0; i < sz(result); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }
}

int32_t main() {
    fastio;
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
