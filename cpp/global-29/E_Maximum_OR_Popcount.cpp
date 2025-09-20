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

        
        vector<pair<long long, int>> costs; // (cost, net_popcount_gain)
        for (int k = 0; k < 40; k++) {
            if (init_or & (1LL << k)) continue;
            long long target = 1LL << k;
            long long min_cost = 1e18;
            int best_idx = -1;
            for (int i = 0; i < n; i++) {
                long long curr = a[i];
                long long lower_mask = target - 1;
                long long max_lower = curr & lower_mask;
                long long need = target - max_lower; 
                if (need < min_cost) {
                    min_cost = need;
                    best_idx = i;
                }
            }
            if (min_cost != 1e18 && min_cost <= 1e9) { 
        
                long long new_val = a[best_idx] + min_cost;
                int new_pop = __builtin_popcountll(new_val);
                int old_pop = __builtin_popcountll(a[best_idx]);
                int net_gain = new_pop - old_pop; 
                costs.emplace_back(min_cost, net_gain);
            }
        }

        
        sort(costs.begin(), costs.end());
        int nc = costs.size();
        vector<long long> pref(nc + 1, 0);
        vector<int> pop_gains(nc + 1, 0);
        for (int i = 1; i <= nc; i++) {
            pref[i] = pref[i - 1] + costs[i - 1].first;
            pop_gains[i] = pop_gains[i - 1] + costs[i - 1].second;
        }

        for (int i = 0; i < q; i++) {
            long long b;
            cin >> b;
            int low = 0, high = nc;
            int max_pop = init_pop;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (mid <= nc && pref[mid] <= b) {
                    max_pop = max(max_pop, init_pop + pop_gains[mid]);
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            cout << max_pop << '\n';
        }
    }
    return 0;
}