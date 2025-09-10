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

int hamid(string s, int x) {
    int pl = x - 1;
    while (pl >= 0 && s[pl] == '.') pl--;
    int pr = x + 1;
    while (pr < (int)s.size() && s[pr] == '.') pr++;
    int ans = min(pl + 2, (int)s.size() - pr + 1);
    return ans;
}
//--------------------------
// Solve Function
//--------------------------
void solve() {
    ll n, x;
    cin >> n >> x;
    x--;
    string s;
    cin >> s;
    
    int ans1 = 0, ans2 = 0;
    {
        string t = s;
        int pl = x + 1;
        while (pl < n && s[pl] == '#') pl++;
        if (pl != n) {
            t[pl] = '#';
            ans1 = hamid(t, x);
        }
    }
    {
        string t = s;
        int pr = x - 1;
        while(pr >= 0 && s[pr] == '#') pr--;
        if (pr != -1){
            t[pr] = '#';
            ans2 = hamid(t, x);
        }
    }

    cout << max(ans1, ans2) << "\n";
    
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