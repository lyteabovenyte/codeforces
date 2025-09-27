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

struct Node {
    Node* child[2];
    int cnt;
    Node() : cnt(0) {
        child[0] = child[1] = nullptr;
    }
};

void insert(Node* root, long long val) {
    Node* cur = root;
    for (int k = 29; k >= 0; --k) {
        int bit = (val >> k) & 1;
        if (cur->child[bit] == nullptr) {
            cur->child[bit] = new Node();
        }
        cur = cur->child[bit];
        cur->cnt++;
    }
}

void remove_val(Node* root, long long val) {
    Node* cur = root;
    for (int k = 29; k >= 0; --k) {
        int bit = (val >> k) & 1;
        cur = cur->child[bit];
        cur->cnt--;
    }
}

long long find_optimal(Node* root, long long b) {
    long long val = 0;
    Node* cur = root;
    for (int k = 29; k >= 0; --k) {
        int bb = (b >> k) & 1;
        int prefer = (bb == 1) ? 0 : 1;
        int chosen = prefer;
        if (cur->child[prefer] == nullptr || cur->child[prefer]->cnt == 0) {
            chosen = 1 - prefer;
        }
        val |= (long long)chosen << k;
        cur = cur->child[chosen];
    }
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int test = 0; test < t; ++test) {
        long long l, r;
        cin >> l >> r;
        long long n = r - l + 1;
        long long sum = n * (l + r) / 2;
        long long min_and = 0;
        for (int k = 0; k < 30; ++k) {
            long long mask = 1LL << k;
            int m = 0;
            for (long long x = l; x <= r; ++x) {
                if (x & mask) ++m;
            }
            long long e = max(0LL, 2LL * m - n);
            min_and += e * mask;
        }
        long long max_or = 2LL * sum - min_and;
        // Now construct the permutation
        vector<long long> bs;
        for (long long x = l; x <= r; ++x) {
            bs.push_back(x);
        }
        sort(bs.begin(), bs.end(), [](long long x, long long y) {
            int px = __builtin_popcountll(x);
            int py = __builtin_popcountll(y);
            if (px != py) return px > py;
            return x > y;
        });
        Node* root = new Node();
        for (long long x = l; x <= r; ++x) {
            insert(root, x);
        }
        map<long long, long long> b_to_a;
        for (long long b : bs) {
            long long v = find_optimal(root, b);
            b_to_a[b] = v;
            remove_val(root, v);
        }
        cout << max_or << '\n';
        for (long long x = l; x <= r; ++x) {
            cout << b_to_a[x];
            if (x < r) cout << ' ';
            else
                cout << '\n';
        }
    }
    return 0;
}