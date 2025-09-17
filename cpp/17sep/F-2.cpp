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
#include <array>

using namespace std;

string s[50];
int cvis[50];
vector<int> ansv;
int tre[2510][2], fail[2510], vis[2510], dp[51][51][2510], p = 1;
void ins(int x) {
    int t = 0, i, c;
    for (i = 0; i < s[x].length(); i++) {
        if (s[x][i] == '(') c = 0;
        else
            c = 1;
        if (tre[t][c] == 0) {
            tre[t][c] = p;
            p++;
        }
        t = tre[t][c];
    }
    vis[t] = 1;
}
queue<int> q;
void buildac() {
    int i, t;
    q.push(0);
    while (!q.empty()) {
        t = q.front();
        q.pop();
        for (i = 0; i < 2; i++) {
            if (tre[t][i] == 0) {
                if (t == 0) tre[t][i] = 0;
                else
                    tre[t][i] = tre[fail[t]][i];
            } else {
                if (t == 0) fail[tre[t][i]] = 0;
                else
                    fail[tre[t][i]] = tre[fail[t]][i];
                q.push(tre[t][i]);
                vis[tre[t][i]] |= vis[fail[tre[t][i]]];
            }
        }
    }
}
bool check(int n, int k) {
    int i, j, t;
    for (i = 0; i < n; i++) ins(i);
    buildac();
    for (i = 0; i < p; i++) {
        if (!vis[i]) dp[k][0][i] = 1;
    }
    for (i = k - 1; i > -1; i--) {
        for (j = 0; j <= k; j++) {
            for (t = 0; t < p; t++) {
                if (vis[t]) continue;
                if (j + 1 <= k) dp[i][j][t] |= dp[i + 1][j + 1][tre[t][0]];
                if (j - 1 >= 0) dp[i][j][t] |= dp[i + 1][j - 1][tre[t][1]];
            }
        }
    }
    if (dp[0][0][0] == 0) return 0;
    cout << "1\n";
    j = 0;
    t = 0;
    for (i = 0; i < k; i++) {
        if (j + 1 <= k && dp[i + 1][j + 1][tre[t][0]]) {
            t = tre[t][0];
            j++;
            cout << '(';
        } else {
            t = tre[t][1];
            j--;
            cout << ')';
        }
    }
    cout << '\n';
    cout << n << '\n';
    for (i = 1; i <= n; i++) cout << i << ' ';
    cout << '\n';
    return 1;
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n, k, i, j;
    cin >> n >> k;
    for (i = 0; i < n; i++) {
        cin >> s[i];
        if (s[i] == "()") {
            cout << "-1\n";
            return 0;
        }
    }
    if (check(n, k)) return 0;
    for (i = 0; i < n; i++) {
        for (j = 1; j < s[i].length(); j++) {
            if (s[i][j] == s[i][j - 1]) cvis[i] = 1;
        }
    }
    cout << "2\n";
    for (i = 0; i < k / 2; i++) cout << "(";
    for (i = 0; i < k / 2; i++) cout << ")";
    cout << '\n';
    for (i = 0; i < n; i++) {
        if (!cvis[i]) ansv.push_back(i);
    }
    cout << ansv.size() << '\n';
    for (i = 0; i < ansv.size(); i++) cout << ansv[i] + 1 << ' ';
    cout << '\n';
    ansv.clear();
    for (i = 0; i < k / 2; i++) cout << "()";
    cout << '\n';
    for (i = 0; i < n; i++) {
        if (cvis[i]) ansv.push_back(i);
    }
    cout << ansv.size() << '\n';
    for (i = 0; i < ansv.size(); i++) cout << ansv[i] + 1 << ' ';
    cout << '\n';
    ansv.clear();
    return 0;
}