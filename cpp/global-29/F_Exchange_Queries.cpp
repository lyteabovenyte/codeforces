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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        long long init_or = 0;
        for (auto x : a) init_or |= x;
        int init_pop = __builtin_popcountll(init_or);
        vector<pair<long long, int>> costs;
        for (int k = 0; k < 40; k++) {
            if (init_or & (1LL << k)) continue;
            long long target = 1LL << k;
            long long min_cost = 1e18;
            int best_idx = -1;
            for (int i = 0; i < n; i++) {
                long long curr = a[i];
                long long need = target - (curr & (target - 1));
                if (need > 0 && need < min_cost) {
                    min_cost = need;
                    best_idx = i;
                }
            }
            if (min_cost != 1e18) {
                long long next_val = a[best_idx] + min_cost;
                int additional_bits = __builtin_popcountll(next_val) - __builtin_popcountll(a[best_idx]);
                costs.emplace_back(min_cost, additional_bits);
            }
        }
        // Sort by cost, then by additional bits gained
        sort(costs.begin(), costs.end());
        int nc = costs.size();
        vector<long long> pref(nc + 1, 0);
        vector<int> bit_gains(nc + 1, 0);
        for (int i = 1; i <= nc; i++) {
            pref[i] = pref[i - 1] + costs[i - 1].first;
            bit_gains[i] = bit_gains[i - 1] + costs[i - 1].second;
        }
        for (int i = 0; i < q; i++) {
            long long b;
            cin >> b;
            int low = 0, high = nc;
            int max_bits = init_pop;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (mid <= nc && pref[mid] <= b) {
                    max_bits = max(max_bits, init_pop + mid + (bit_gains[mid] > 0 ? bit_gains[mid] - 1 : 0));
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            cout << max_bits << '\n';
        }
    }
    return 0;
}