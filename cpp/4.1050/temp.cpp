#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using ull = unsigned long long;

#define X first
#define Y second
#define SZ(x) int(x.size())
#define all(x) x.begin(), x.end()
#define mins(a, b) (a = min(a, b))
#define maxs(a, b) (a = max(a, b))
#define pb push_back
#define Mp make_pair
#define lc id << 1
#define rc lc | 1
#define mid ((l + r) >> 1)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll INF = 1e9 + 23;
const ll MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int LOG = 23;

vector<int> D[MXN];

void sieve() {
    for (int i = 1; i < MXN; i++)
        for (int j = 0; j < MXN; j += i)
            D[j].push_back(i);
}

int n, a[MXN], cnt[MXN];

void Main() {
    cin >> n;
    fill(cnt + 1, cnt + n + 1, 0);
    vector<int> vec;
    int ans = 0;
    int g1 = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int g2 = gcd(g1, a[i]);
        if (g1 != g2 && g1)
            for (int j : D[g1])
                if (g2 % j)
                    maxs(ans, cnt[j]);
        g1 = g2;
        for (int j : D[a[i]]) {
            cnt[j]++;
            if (g1 % j) maxs(ans, cnt[j]);
        }
        cout << ans << ' ';
    }
    cout << '\n';
}

int32_t main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    sieve();
    while (T--) Main();
    return 0;
}