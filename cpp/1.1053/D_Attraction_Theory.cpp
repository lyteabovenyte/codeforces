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
// Using modulus from problem statement:
const int MOD = 998244353;
const int MXF = 400000 + 5; // factorial upper bound (safe for sum n <= 2e5)

// Mint struct (mod 998244353)
struct Mint {
    int val;
    Mint(long long v = 0) {
        long long x = v % MOD;
        if (x < 0) x += MOD;
        val = (int)x;
    }
    Mint& operator+=(const Mint& other) {
        val += other.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    Mint& operator-=(const Mint& other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }
    Mint& operator*=(const Mint& other) {
        val = (int)((1LL * val * other.val) % MOD);
        return *this;
    }
    friend Mint pow(Mint a, long long e) {
        Mint r = 1;
        while (e) {
            if (e & 1) r *= a;
            a *= a;
            e >>= 1;
        }
        return r;
    }
    Mint inv() const { return pow(*this, MOD - 2); }
    Mint& operator/=(const Mint& other) { return *this *= other.inv(); }
    friend Mint operator+(Mint a, const Mint& b) {
        a += b;
        return a;
    }
    friend Mint operator-(Mint a, const Mint& b) {
        a -= b;
        return a;
    }
    friend Mint operator*(Mint a, const Mint& b) {
        a *= b;
        return a;
    }
    friend Mint operator/(Mint a, const Mint& b) {
        a /= b;
        return a;
    }
    friend ostream& operator<<(ostream& os, const Mint& m) {
        os << m.val;
        return os;
    }
};

static Mint fact[MXF], invfact[MXF];

Mint nCr(int n, int r) {
    if (r < 0 || r > n || n < 0) return Mint(0);
    return fact[n] * invfact[r] * invfact[n - r];
}

void precompute_factorials(int N) {
    fact[0] = Mint(1);
    for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * Mint(i);
    invfact[N] = fact[N].inv();
    for (int i = N; i > 0; i--) invfact[i - 1] = invfact[i] * Mint(i);
}

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<Mint> diff(n + 3, Mint(0));

    for (int r = 1; r <= n; ++r) {
        int L = n - (r - 1);
        int M = n - r;

        if (r == 1) {
            diff[1] += Mint(n);
            diff[n + 1] -= Mint(n);
            continue;
        }

        Mint S_i = Mint(0), S_b = Mint(0);

        for (int m = 0; m <= M / 2; ++m) {
            int T = M - 2 * m;
            Mint coeff1 = nCr(m + r - 2, r - 2);
            Mint g;
            if (T == 0) g = Mint(1);
            else if (T == 1)
                g = Mint(2);
            else
                g = Mint((2LL * T) % MOD);
            S_i += coeff1 * g;

            if (r >= 3) {
                Mint coeff2 = nCr(m + r - 3, r - 3);
                long long combT = ((1LL * (T + 2) * (T + 1) / 2) % MOD);
                S_b += coeff2 * Mint(combT);
            }
        }

        if (r == 2) {
            long long sb = ((1LL * n * (n - 1) / 2) % MOD);
            S_b = Mint(sb);
        }

        int l1 = 1, r1 = min(n, L);
        if (l1 <= r1) {
            diff[l1] += S_b;
            diff[r1 + 1] -= S_b;
        }

        int l2 = r, r2 = min(n, r + L - 1);
        if (l2 <= r2) {
            diff[l2] += S_b;
            diff[r2 + 1] -= S_b;
        }

        for (int j = 1; j <= r - 2; ++j) {
            int lx = j + 1;
            int rx = min(n, j + L);
            if (lx <= rx) {
                diff[lx] += S_i;
                diff[rx + 1] -= S_i;
            }
        }
    }

    vector<Mint> cnt(n + 1, Mint(0));
    Mint cur = 0;
    for (int x = 1; x <= n; ++x) {
        cur += diff[x];
        cnt[x] = cur;
    }

    Mint ans = 0;
    for (int x = 1; x <= n; ++x) {
        Mint term = Mint(a[x - 1] % MOD) * cnt[x];
        ans += term;
    }

    cout << ans << '\n';
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    precompute_factorials(MXF - 5);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
