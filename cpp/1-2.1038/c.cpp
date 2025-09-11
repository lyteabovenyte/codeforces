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
// const int MOD = 998244353;

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
void solve()
{
    int n;
    cin >> n;
    vi x(n), y(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }

    vector<pii> u(n), v(n), w(n), z(n);
    for (int i = 0; i < n; i++)
    {
        u[i] = {x[i] + y[i], i};
        v[i] = {x[i] - y[i], i};
        w[i] = {-x[i] + y[i], i};
        z[i] = {-x[i] - y[i], i};
    }

    auto proc = [&](vector<pii> arr)
    {
        sort(all(arr));
        int cur = 0;
        vector<pii> pairs;
        int l = 0, r = n - 1;
        while (l < r)
        {
            int i1 = arr[l].second, i2 = arr[r].second;
            int d = abs(x[i1] - x[i2]) + abs(y[i1] - y[i2]);
            cur += d;
            pairs.pb({i1 + 1, i2 + 1});
            l++;
            r--;
        }
        return make_pair(cur, pairs);
    };
    auto [sum1, pairs1] = proc(u);
    auto [sum2, pairs2] = proc(v);
    auto [sum3, pairs3] = proc(w);
    auto [sum4, pairs4] = proc(z);

    if (sum1 >= sum2 && sum1 >= sum3 && sum1 >= sum4)
    {
        for (auto &p : pairs1)
            cout << p.first << " " << p.second << "\n";
    }
    else if (sum2 >= sum1 && sum2 >= sum3 && sum2 >= sum4)
    {
        for (auto &p : pairs2)
            cout << p.first << " " << p.second << "\n";
    }
    else if (sum3 >= sum1 && sum3 >= sum2 && sum3 >= sum4)
    {
        for (auto &p : pairs3)
            cout << p.first << " " << p.second << "\n";
    }
    else
    {
        for (auto &p : pairs4)
            cout << p.first << " " << p.second << "\n";
    }
}

//--------------------------
// Main
//--------------------------
int32_t main()
{
    fastio;
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}