#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <iterator>
#include <ostream>
#include <queue>
#include <stack>
#include <vector>
 
using namespace std;
 
int main() {
    int tt;
    cin >> tt;
    while (tt--) {
        int k, n;
        cin >> k >> n;
        while (k--) {
            n <<= 1;
        }
        cout << n << endl;
    }
}