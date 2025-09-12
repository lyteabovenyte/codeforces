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

struct Mint {
    int val;
    Mint(int v = 0) : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    Mint& operator+=(const Mint& other) {
        val = (val + other.val) % MOD;
        return *this;
    }
    Mint& operator-=(const Mint& other) {
        val = (val - other.val + MOD) % MOD;
        return *this;
    }
    Mint& operator*=(const Mint& other) {
        val = (val * other.val) % MOD;
        return *this;
    }
    Mint operator+(const Mint& other) const { return Mint(*this) += other; }
    Mint operator-(const Mint& other) const { return Mint(*this) -= other; }
    Mint operator*(const Mint& other) const { return Mint(*this) *= other; }
    bool operator==(const Mint& other) const { return val == other.val; }
    friend ostream& operator<<(ostream& os, const Mint& m) { return os << m.val; }
};

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
    vector<vector<int>> a(2, vector<int>(n));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<Mint> f(k + 1);
    f[k] = 1;
    for (int j = 1; j < n; j++) {
        vector<Mint> w(2 * k + 1);
        for (int x = 1; x <= k; x++) {
            if (x != -1 && a[0][j] != -1 && x != a[0][j]) {
                continue;
            }
            for (int y = 1; y <= k; y++) {
                if (y != -1 && a[1][j - 1] != -1 && y != a[1][j - 1]) {
                    continue;
                }
                w[x - y + k] += 1;
            }
        }
        vector<Mint> new_f(k + 1);
        for (int v = 0; v <= k; v++) {
            if (f[v] == 0) {
                continue;
            }
            for (int d = -k + 1; d <= k - 1; d++) {
                int new_v = v;
                if (v == k) {
                    if (d >= 0) {
                        new_v = k;
                    } else {
                        new_v = -d;
                    }
                } else {
                    if (v - d < 0) {
                        continue;
                    }
                    if (d < 0) {
                        new_v = -d;
                    } else {
                        new_v = v - d;
                    }
                }
                assert(new_v >= 0 && new_v <= k);
                new_f[new_v] += f[v] * w[d + k];
            }
        }
        swap(f, new_f);
    }
    Mint ans = accumulate(f.begin(), f.end(), Mint(0));
    if (a[0][0] == -1) {
        ans *= k;
    }
    if (a[1][n - 1] == -1) {
        ans *= k;
    }
    cout << ans << '\n';
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

/*
# 0) Problem being encoded

We have a $2 \times n$ grid with values from $[1..k]$ (unknown cells are $-1$).
We must count how many ways to fill the $-1$ so that **every subgrid** has a **greedy** top-left→(right/down only) path whose value is **maximum** among all such paths in that subgrid.
All answers are modulo $998\,244\,353$ (class `Mint`).

For a $2 \times n$ grid, that global requirement can be enforced **locally** through the chain of consecutive $2 \times 2$ squares. The only interaction between consecutive squares happens across their **anti-diagonal** cells:

* top of the right column of the current square, call it $x = a_{0,j}$
* bottom of the left column of the current square, call it $y = a_{1,j-1}$

Define the “step” on square $j$ as $d = x - y$ (can range from $-(k-1)$ to $+(k-1)$).

As we sweep the $n-1$ adjacent $2\times2$ squares from left to right, we maintain a single number $v$ that represents the **current headroom** (a non-negative slack) that guarantees the greedy path property for *every prefix subgrid considered so far*. Think of $v$ as how much “budget” remains before the conditions would be violated. A special value $v = k$ is used as **$\infty$** (unbounded headroom) before any square is processed.

When we see a new step $d=x-y$, the headroom updates as follows:

* If $v=\infty$ (we haven’t restricted anything yet):

  * if $d\ge 0$, we stay at $\infty$
  * if $d<0$, headroom becomes $-d$ (we’ve now used up $-d$ budget)

* If $v<\infty$:

  * the transition is **feasible only if** $v-d \ge 0$ (otherwise we would go below 0 budget)
  * the new headroom is

    * $-d$ if $d<0$ (a negative step forces the new budget to be its absolute size)
    * $v-d$ if $d\ge 0$ (we spend $d$ from the current budget)

This “budget with reflecting resets” is exactly what the code implements in the inner DP transition.

---

# 1) Reading input

```cpp
int tt; cin >> tt;
while (tt--) {
  int n,k; cin >> n >> k;
  vector a(2, vector<int>(n));
  for (int i=0;i<2;i++)
    for (int j=0;j<n;j++)
      cin >> a[i][j];
```

`a[i][j]` is $-1$ if the cell is unknown; otherwise it is fixed in $[1..k]$.

---

# 2) DP state

```cpp
vector<Mint> f(k + 1);
f[k] = 1;           // k means "infinite" headroom
```

`f[v]` = number of ways to fill cells up to (and including) column `j-1` such that the running headroom equals `v` (with `v==k` meaning ∞).
We start before any $2\times2$ square has been processed, so the headroom is unbounded: `f[k]=1`.

We will process `j = 1..n-1`, i.e., each adjacent $2\times2$ block formed by columns $(j-1, j)$.

---

# 3) Count all allowed steps $d = x - y$ for the current block

For each square at position `j` we need, for every possible $x = a_{0,j}$ and $y = a_{1,j-1}$ consistent with the fixed entries, the number of pairs that give a particular difference $d=x-y$.

```cpp
vector<Mint> w(2 * k + 1);      // w[d + k] = count of pairs (x,y) s.t. x-y = d
for (int x = 1; x <= k; x++) {
  if (a[0][j] != -1 && x != a[0][j]) continue; // respect fixed top cell of column j
  for (int y = 1; y <= k; y++) {
    if (a[1][j - 1] != -1 && y != a[1][j - 1]) continue; // respect fixed bottom cell of column j-1
    w[x - y + k] += 1;            // one more way to realize this difference d
  }
}
```

So `w` summarizes all **choices in this square that matter to the DP**.
(Notice that the other two cells of the square—`a[0][j-1]` and `a[1][j]`—are not touched here; they are accounted for in other squares or at the very end—see §6.)

---

# 4) Transition: update headroom with this square’s $d$

```cpp
vector<Mint> new_f(k + 1);
for (int v = 0; v <= k; v++) {
  if (f[v] == 0) continue;
  for (int d = -k + 1; d <= k - 1; d++) {
    int new_v = v;
    if (v == k) {                 // v == ∞
      new_v = (d >= 0 ? k : -d);
    } else {                      // finite v
      if (v - d < 0) continue;    // infeasible
      new_v = (d < 0 ? -d : v - d);
    }
    new_f[new_v] += f[v] * w[d + k];
  }
}
swap(f, new_f);
```

This is the exact “budget update” described at the top.
Each `w[d+k]` ways to realize difference `d` are added to the appropriate `new_v`.
Complexity per square is $O(k^2)$ (building `w`) + $O(k \cdot k)$ (DP transitions).

---

# 5) After all squares

When all $n-1$ squares have been processed, **any** headroom $v$ is acceptable. So the total number of fillings contributed by the chain of squares is

```cpp
Mint ans = accumulate(f.begin(), f.end(), Mint(0));
```

But there are two **corner cells** that never appear in any $x$ or $y$ during the sweep:

* `a[0][0]` (top-left corner)
* `a[1][n-1]` (bottom-right corner)

If they are unknown, each can be chosen freely in $[1..k]$ and their choices were not counted yet, so we multiply:

```cpp
if (a[0][0] == -1) ans *= k;
if (a[1][n - 1] == -1) ans *= k;
```

Finally we print the answer.

---

# 6) Why this matches the greedy condition

For $2\times n$, the “greedy is optimal in **every** subgrid” requirement reduces to keeping the running headroom non-negative as we move across consecutive $2\times2$ squares, where each square contributes only through the anti-diagonal difference $d = a_{0,j} - a_{1,j-1}$. The update rules above are precisely the feasibility/propagation of that invariant (with $\infty$ before the first square). The program counts all fillings that keep the invariant valid.

---

# 7) Small implementation notes

* `Mint` is a modular arithmetic wrapper over modulus $998244353$.
* Arrays:

  * `f` has size `k+1` because we store states `0..k-1` plus the special `k` meaning $\infty$.
  * `w` has size `2k+1` and is indexed by `d+k` to shift negative `d` to $[0..2k]$.
* Edge cells `a[0][0]` and `a[1][n-1]` are handled at the end because they are not part of any `(x,y)` in the sweep.

---

# 8) Complexity

For each of the $n-1$ squares:

* Computing `w`: $O(k^2)$ (skips forbidden values if the cells are fixed).
* DP transition: $O(k \cdot (2k-1)) = O(k^2)$.

Total: $O(n \cdot k^2)$ time and $O(k)$ memory, which fits the constraints ($\sum n \le 500$, $k \le 500$).

*/