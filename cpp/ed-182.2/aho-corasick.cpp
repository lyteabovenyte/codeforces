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
const int MXN = 2e5 + 5;

struct AhoCorasick {
    static constexpr int ALPHABET = 2; // '(' -> 0, ')' -> 1
    struct Node {
        int len;
        int link;       // failure link
        int dict_link;  // dictionary link
        array<int, ALPHABET> next;
        bool terminal;  // is end of a pattern
        Node() : len(0), link(0), dict_link(0), terminal(false), next{} {}
    };

    vector<Node> t;

    AhoCorasick() { init(); }

    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
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
        t[p].terminal = true; // mark pattern end
        return p;
    }

    void build() {
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    int y = t[x].next[i];
                    t[y].link = t[t[x].link].next[i];
                    // dictionary link setup
                    if (t[t[y].link].terminal)
                        t[y].dict_link = t[y].link;
                    else
                        t[y].dict_link = t[t[y].link].dict_link;
                    q.push(y);
                }
            }
        }
    }

    inline int go(int p, int x) const { return t[p].next[x]; }
    inline int link(int p) const { return t[p].link; }
    inline int dict_link(int p) const { return t[p].dict_link; }
    inline bool terminal(int p) const { return t[p].terminal; }
    inline int size() const { return (int)t.size(); }

    // collect all matches ending at node p
    vector<int> report(int p) const {
        vector<int> res;
        for (int u = p; u; u = t[u].dict_link) {
            if (t[u].terminal) res.push_back(u);
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<string> s(n);
    AhoCorasick ac;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        ac.add(s[i]);
    }
    ac.build();
    cout << "Automaton built with size: " << ac.size() << "\n";
}

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}