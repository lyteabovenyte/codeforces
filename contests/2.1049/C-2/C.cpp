#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long ans = 0;
    long long mx2 = -1e18, mn1 = 1e18;
    long long mx = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            ans -= a[i];
            mx = max(mx, 2 * a[i] + i - mn1);
            mx2 = max(mx2, 2LL * a[i] - i);
        } else {
            ans += a[i];
            mn1 = min(mn1, 2LL * a[i] + i);
            mx = max(mx, mx2 - 2 * a[i] + i);
        }
    }

    if (n % 2) {
        mx = max(mx, (long long)(n - 1));
    } else {
        mx = max(mx, (long long)(n - 2));
    }
    ans += mx;
    cout << ans << "\n";
}

int main() {
    fastio;
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
