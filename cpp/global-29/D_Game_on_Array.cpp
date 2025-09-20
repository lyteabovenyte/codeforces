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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int test = 0; test < t; test++) {
        int n;
        cin >> n;
        map<long long, long long> freq;
        long long total = 0;
        for (int i = 0; i < n; i++) {
            long long a;
            cin >> a;
            freq[a]++;
            total += a;
        }
        vector<pair<long long, long long>> comp;
        for (auto& p : freq) {
            comp.push_back({ p.second, p.first });
        }
        sort(comp.rbegin(), comp.rend());
        long long alice = 0;
        long long pos = 0;
        for (auto& p : comp) {
            long long f = p.first;
            long long v = p.second;
            bool start_even = (pos % 2 == 0);
            long long num = start_even ? (v + 1) / 2 : v / 2;
            alice += num * f;
            pos += v;
        }
        long long bob = total - alice;
        cout << alice << " " << bob << "\n";
    }
    return 0;
}