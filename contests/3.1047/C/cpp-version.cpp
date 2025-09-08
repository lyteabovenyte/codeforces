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
    long long a, b;
    cin >> a >> b;
    if (((a & 1) == 0) && ((b & 1) == 1)) {
      cout << -1 << endl;
    } else if (((a & 1) == 1) && ((b & 1) == 0)) {
      long long k = b >> 1;
      if ((k & 1) == 1) {
        cout << -1 << endl;
      } else {
        long long res = a * k + 2;
        cout << res << endl;
      }
    } else if (((a & 1) == 1) && ((b & 1) == 1)) {
      long long res = a * b + 1;
      cout << res << endl;
    } else if (((a & 1) == 0) && ((b & 1) == 0)) {
      long long k = b >> 1;
      long long res = a * k + 2;
      cout << res << endl;
    }
  }
  return 0;
}