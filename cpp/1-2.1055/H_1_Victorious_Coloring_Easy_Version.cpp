#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
using namespace std;

//--------------------------
// Macros and Aliases
//--------------------------
#define fastio                   \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define int long long

using ll = long long;

struct Edge {
    int to, w;
};

//--------------------------
// Solve Function
//--------------------------
void solve() {
    int n;
    cin >> n;
    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    // Root the tree once (at 1) and get a post-order
    vector<int> parent(n + 1, 0), pw(n + 1, 0), order;
    order.reserve(n);
    vector<int> st = { 1 };
    parent[1] = 0;
    pw[1] = 0;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        order.push_back(u);
        for (auto e : g[u])
            if (e.to != parent[u]) {
                parent[e.to] = u;
                pw[e.to] = e.w;
                st.push_back(e.to);
            }
    }
    // We'll process nodes in reverse order for DP
    reverse(all(order));

    int q;
    cin >> q;

    vector<long long> A(n + 1), B(n + 1), C(n + 1);

    while (q--) {
        long long t;
        cin >> t;

        // DP per query
        for (int u : order) {
            long long au = 0, bu = 0;
            for (auto e : g[u])
                if (e.to != parent[u]) {
                    int v = e.to, w = e.w;
                    // A[u]: u not selected
                    au += max(A[v], C[v] - w);
                    // B[u]: u selected, open upwards
                    long long join = B[v];           // connect u and v
                    long long sep1 = A[v] - w;       // v not selected -> boundary once
                    long long sep2 = C[v] - 2LL * w; // v has closed component -> boundary twice
                    bu += max({ join, sep1, sep2 });
                }
            A[u] = au;
            B[u] = bu;
            C[u] = bu + t; // close component at u (count +t); edge to parent handled above
        }

        cout << max(A[1], C[1]) << '\n';
    }
}

//--------------------------
// Main
//--------------------------
int32_t main() {
    fastio;
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
