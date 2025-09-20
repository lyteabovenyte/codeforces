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
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int test = 0; test < t; ++test) {
        long long x, y;
        cin >> x >> y;
        int ans = -1;
        if (x < y) {
            ans = 2;
        } else if (y >= 2 && x >= y + 2) {
            ans = 3;
        }
        cout << ans << '\n';
    }
    return 0;
}