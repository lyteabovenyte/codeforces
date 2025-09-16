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
#include <array>

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
using u64 = unsigned long long;

//--------------------------
// Constants
//--------------------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
// const int MOD = 998244353;

//--------------------------
// Aho–Corasick for '(' , ')'
// Root is node 1; node 0 is -1 layer (standard trick)
//--------------------------
struct AhoCorasick {
    static constexpr int ALPHABET = 2; // '(' -> 0, ')' -> 1
    struct Node {
        int len;
        int link;
        array<int, ALPHABET> next;
        Node() : len(0), link(0), next{} {}
    };

    vector<Node> t;

    AhoCorasick() { init(); }

    void init() {
        t.assign(2, Node());
        t[0].next.fill(1); // fail from virtual node goes to root
        t[0].len = -1;
        // root = 1
    }
    int newNode() {
        t.emplace_back();
        return (int)t.size() - 1;
    }
    static inline int cid(char c) { return (c == '(') ? 0 : 1; }

    int add(const string& s) {
        int p = 1;
        for (char ch : s) {
            int x = cid(ch);
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }

    void build() {
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }

    inline int go(int p, int x) const { return t[p].next[x]; }
    inline int link(int p) const { return t[p].link; }
    inline int size() const { return (int)t.size(); }
};

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n, k;
    cin >> n >> k;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        // If "()" is forbidden, impossible (any regular host of length k contains "()" as a substring).
        if (s[i] == "()") {
            cout << -1 << "\n";
            return;
        }
    }

    // Build AC over all patterns.
    vector<int> endPos(n);
    AhoCorasick ac;
    for (int i = 0; i < n; i++) endPos[i] = ac.add(s[i]);
    ac.build();

    int N = ac.size();

    // bad[v] = true if node v corresponds to a state that matches at least one pattern
    vector<char> bad(N, 0);
    for (int i = 0; i < n; i++) bad[endPos[i]] = 1;
    for (int v = 1; v < N; v++) {
        int u = v;
        while (u) {
            if (bad[u]) {
                bad[v] = 1;
                break;
            }
            u = ac.link(u);
        }
    }

    // DP over positions with bitmask of possible balances at each AC node.
    // dp[i][v] is a bitmask (u64) where bit b == 1 means: after i chars, at automaton node v, balance==b is reachable
    // balance ∈ [0, k/2], so use up to 26 bits (k<=50).
    int maxBal = k / 2;
    vector<vector<u64>> dp(k + 1, vector<u64>(N, 0));
    dp[0][1] = 1ULL; // at pos 0, node=1 (root), balance 0

    for (int i = 0; i < k; i++) {
        for (int v = 1; v < N; v++) {
            if (bad[v]) continue;
            u64 mask = dp[i][v];
            if (!mask) continue;

            // put '(' ⇒ balance +1
            int vL = ac.go(v, 0);
            if (!bad[vL]) {
                u64 nxt = (mask << 1);
                // keep only balances <= maxBal
                nxt &= ((maxBal >= 63) ? ULLONG_MAX : ((1ULL << (maxBal + 1)) - 1));
                dp[i + 1][vL] |= nxt;
            }
            // put ')' ⇒ balance -1 (only if current balance > 0)
            int vR = ac.go(v, 1);
            if (!bad[vR]) {
                u64 nxt = (mask >> 1);
                dp[i + 1][vR] |= nxt;
            }
        }
    }

    // Try to end at pos=k, balance=0 (bit 0 set), any safe node.
    int endNode = -1;
    for (int v = 1; v < N; v++) {
        if (!bad[v] && (dp[k][v] & 1ULL)) {
            endNode = v;
            break;
        }
    }

    if (endNode != -1) {
        // Reconstruct a host string.
        string host;
        host.reserve(k);
        int pos = k;
        int bal = 0;
        int v = endNode;

        while (pos) {
            bool stepFound = false;
            // We search a predecessor (u, ch) that transitions to (v, bal) at pos.
            for (int u = 1; u < N && !stepFound; u++)
                if (!bad[u]) {
                    // If we place ')' at pos-1: we must have come from (u, bal+1) and ac.go(u,1) == v
                    int uToR = ac.go(u, 1);
                    if (uToR == v) {
                        u64 prevMask = dp[pos - 1][u];
                        if ((prevMask >> (bal + 1)) & 1ULL) {
                            host.push_back(')');
                            v = u;
                            bal = bal + 1;
                            stepFound = true;
                            break;
                        }
                    }
                    // If we place '(' at pos-1: we must have come from (u, bal-1) and ac.go(u,0) == v
                    if (bal > 0) {
                        int uToL = ac.go(u, 0);
                        if (uToL == v) {
                            u64 prevMask = dp[pos - 1][u];
                            if ((prevMask >> (bal - 1)) & 1ULL) {
                                host.push_back('(');
                                v = u;
                                bal = bal - 1;
                                stepFound = true;
                                break;
                            }
                        }
                    }
                }
            // Should always find a valid predecessor if dp is consistent.
            pos--;
        }
        reverse(all(host));

        cout << 1 << "\n";
        cout << host << "\n";
        cout << n << "\n";
        for (int i = 1; i <= n; i++) {
            cout << i << (i == n ? '\n' : ' ');
        }
        return;
    }

    // Otherwise, use the 2-host construction:
    // Host A: "()()()..." avoids ANY string containing ")("
    // Host B: "(((...)))" avoids strings that DO contain ")("
    vector<int> groupA, groupB;
    for (int i = 0; i < n; i++) {
        if (s[i].find(")(") == string::npos) groupA.pb(i);
        else
            groupB.pb(i);
    }

    cout << 2 << "\n";

    // Print host for groupB first (to mirror your example): "(((...)))"
    string hostB(k / 2, '(');
    hostB += string(k / 2, ')');
    cout << hostB << "\n";
    cout << (int)groupB.size() << "\n";
    for (int i = 0; i < (int)groupB.size(); i++) {
        cout << groupB[i] + 1 << (i + 1 == (int)groupB.size() ? '\n' : ' ');
    }

    // Then host for groupA: "()()()..."
    string hostA;
    hostA.reserve(k);
    for (int i = 0; i < k / 2; i++) hostA += "()";
    cout << hostA << "\n";
    cout << (int)groupA.size() << "\n";
    for (int i = 0; i < (int)groupA.size(); i++) {
        cout << groupA[i] + 1 << (i + 1 == (int)groupA.size() ? '\n' : ' ');
    }
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    // single test per statement
    solve();
    return 0;
}
