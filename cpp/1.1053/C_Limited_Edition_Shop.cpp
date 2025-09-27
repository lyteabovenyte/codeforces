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

using ll = long long;
const ll INF = (ll)4e18;


struct Dinic {
    struct E {
        int to, rev;
        ll cap;
    };
    int N;
    vector<vector<E>> g;
    vector<int> level, it;
    Dinic(int n = 0) { init(n); }
    void init(int n) {
        N = n;
        g.assign(N, {});
        level.assign(N, 0);
        it.assign(N, 0);
    }
    void add_edge(int u, int v, ll c) {
        E a{ v, (int)g[v].size(), c };
        E b{ u, (int)g[u].size(), 0 };
        g[u].push_back(a);
        g[v].push_back(b);
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto& e : g[u])
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
        }
        return level[t] != -1;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = it[u]; i < (int)g[u].size(); ++i) {
            E& e = g[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                ll got = dfs(e.to, t, min(f, e.cap));
                if (got) {
                    e.cap -= got;
                    g[e.to][e.rev].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }
    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (true) {
                ll pushed = dfs(s, t, INF);
                if (!pushed) break;
                flow += pushed;
            }
        }
        return flow;
    }
};


struct Seg {
    struct Node {
        int l, r, lc, rc;
        int last;
    };
    int n, root, nxt;
    vector<Node> st;
    Seg(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        st.assign(4 * n + 5, { 0, 0, 0, 0, 0 });
        nxt = 0;
        root = build(1, n);
    }
    int build(int l, int r) {
        int id = ++nxt;
        st[id].l = l;
        st[id].r = r;
        st[id].last = 0;
        if (l != r) {
            int m = (l + r) >> 1;
            st[id].lc = build(l, m);
            st[id].rc = build(m + 1, r);
        }
        return id;
    }

    // On query of (L..R), connect u -> last[node] (if exists). Thanks to insert-chains,
    // this gives reachability to all older indices in that segment.
    template <class AddEdge>
    void query_last(int id, int L, int R, int uIdx, const AddEdge& addEdge) {
        int l = st[id].l, r = st[id].r;
        if (R < l || r < L) return;
        if (L <= l && r <= R) {
            if (st[id].last) addEdge(uIdx, st[id].last);
            return;
        }
        query_last(st[id].lc, L, R, uIdx, addEdge);
        query_last(st[id].rc, L, R, uIdx, addEdge);
    }


    template <class AddEdge>
    void insert_chain(int id, int pos, int idx, const AddEdge& addEdge) {
        if (st[id].last) addEdge(idx, st[id].last); 
        st[id].last = idx;
        if (st[id].l == st[id].r) return;
        int m = (st[id].l + st[id].r) >> 1;
        if (pos <= m) insert_chain(st[id].lc, pos, idx, addEdge);
        else
            insert_chain(st[id].rc, pos, idx, addEdge);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> v(n + 1);
        for (int i = 1; i <= n; i++) cin >> v[i];
        vector<int> a(n + 1), b(n + 1), posB(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            posB[b[i]] = i;
        }

        vector<int> p(n + 1);
        for (int i = 1; i <= n; i++) p[i] = posB[a[i]];


        int S = 0, Tt = 1, itemBase = 2;
        Dinic mf(n + 2);

        long long sumPos = 0;
        for (int i = 1; i <= n; i++) {
            int node = itemBase + i - 1;
            long long val = v[a[i]];
            if (val >= 0) {
                mf.add_edge(S, node, val);
                sumPos += val;
            } else {
                mf.add_edge(node, Tt, -val);
            }
        }

        Seg seg(n);
        auto addEdge = [&](int fromIdx, int toIdx) {
            int u = itemBase + (fromIdx - 1);
            int vtx = itemBase + (toIdx - 1);
            mf.add_edge(u, vtx, INF);
        };

        for (int i = 1; i <= n; i++) {
            if (p[i] < n) seg.query_last(seg.root, p[i] + 1, n, i, addEdge);
            seg.insert_chain(seg.root, p[i], i, addEdge);
        }

        long long flow = mf.maxflow(S, Tt);
        cout << (sumPos - flow) << '\n';
    }
    return 0;
}
