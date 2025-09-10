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
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define sz(x) (int)(x).size()

using ll  = long long;
using ld  = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;
using vll = vector<ll>;

//--------------------------
// Constants
//--------------------------
const int INF  = 1e9;
const ll  LINF = 1e18;
const int MOD  = 1e9+7;
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
void solve() {
    int n, k;
    cin >> n >> k;
    vi a(n), b(n);
    for (int &x : b) cin >> x;
    for (int &x : a) cin >> x;

    // init
    ll sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += abs(a[i] - b[i]);
    }

    // swap and sort
    vector<pii> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = {a[i], b[i]};
    }

    sort(v.begin(), v.end(), [](auto &x, auto &y){
        return x.first > y.first;
    });

    for (int i = 0; i < n; i++) {
        a[i] = v[i].first;
        b[i] = v[i].second;
    }

    ll ans = LINF;
    for (int i = 0; i < n; i++) {
        vi flat = {v[i].first, v[i].second, v[i+1].first, v[i+1].second};
        ll before = abs(flat[0] - flat[2]) + abs(flat[1] - flat[3]);
        sort(flat.begin(), flat.end());
        ll after = abs(flat[0] - flat[2]) + abs(flat[1] - flat[3]);
        ans = min(ans, abs(before - after));
    }

    cout << sum + ans << "\n";

}

//--------------------------
// Main
//--------------------------
int main() {
    fastio;
    int t;
    cin >> t; 
    while (t--) {
        solve();
    }
    return 0;
}