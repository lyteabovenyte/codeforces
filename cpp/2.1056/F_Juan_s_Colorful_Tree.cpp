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

const int MAXN = 3e5 + 5; // max number of nodes
const int MAXQ = 3e5 + 5; // max number of queries
const int MAXK = 305;     // max number of colors (1 <= k <= 300)

struct DSU {
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            // Union by size
            if (size[rootX] < size[rootY]) {
                swap(rootX, rootY);
            }
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

int main() {
    fastio;

    int t;
    cin >> t;

    while (t--) {
        int n, k, s, q;
        cin >> n >> k >> s >> q;

        vector<vector<int>> g(n + 1);

        // Reading the tree
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // For each color, store the nodes that have this color
        vector<vector<int>> color_nodes(k + 1);
        for (int i = 0; i < s; i++) {
            int v, c;
            cin >> v >> c;
            color_nodes[c].push_back(v);
        }

        // For each query, store the queries
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            cin >> queries[i].first >> queries[i].second;
        }

        // Step 1: Perform DSU for each color
        vector<DSU> dsu(k + 1, DSU(n + 1)); // one DSU for each color

        // Perform DSU union operations for each color
        for (int c = 1; c <= k; c++) {
            for (int i = 1; i < color_nodes[c].size(); i++) {
                int u = color_nodes[c][i - 1];
                int v = color_nodes[c][i];
                dsu[c].unite(u, v);
            }
        }

        // Step 2: Process each query
        vector<int> answers(q, 0);

        // For each query (u, v), check how many colors have u and v connected in the same component
        for (int i = 0; i < q; i++) {
            int u = queries[i].first;
            int v = queries[i].second;
            int count = 0;
            // Check all colors
            for (int c = 1; c <= k; c++) {
                if (dsu[c].find(u) == dsu[c].find(v)) {
                    count++;
                }
            }
            answers[i] = count;
        }

        // Output all answers for the queries in this test case
        for (int i = 0; i < q; i++) {
            cout << answers[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
