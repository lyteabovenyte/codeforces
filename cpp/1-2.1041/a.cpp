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
// MEX Function
//--------------------------
int mex(const vi& arr) {
    set<int> s(all(arr));
    int result = 0;
    while (s.count(result)) {
        result++;
    }
    return result;
}

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    

    if (count(all(a), 0) > 0) {
        cout << "NO" << "\n";
        return;
    }

    set<int> s;
    for (int x : a) if (x >= 1) s.insert(x);
    cout << (s.size() <= 1 ? "YES" : "NO") << "\n";
}

//--------------------------
// Main
//--------------------------
int main() {
    fastio;
    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}