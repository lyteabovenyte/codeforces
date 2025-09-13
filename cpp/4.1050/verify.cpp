#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    vector<vector<int>> arrays = { { 1, 2 }, { 3, 1 }, { 2, 3 } };
    int n = 3;
    int maxk = 2;

    vector<int> best_bottom(maxk, 1e9);

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);

    do {
        vector<vector<int>> grid(n, vector<int>(maxk, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < arrays[perm[i]].size(); j++) {
                grid[i][j] = arrays[perm[i]][j];
            }
        }

        for (int col = 0; col < maxk; col++) {
            int write_pos = n - 1;
            for (int row = n - 1; row >= 0; row--) {
                if (grid[row][col] != 0) {
                    if (write_pos != row) {
                        grid[write_pos][col] = grid[row][col];
                        grid[row][col] = 0;
                    }
                    write_pos--;
                }
            }
        }

        vector<int> bottom(maxk, 0);
        for (int j = 0; j < maxk; j++) {
            bottom[j] = grid[n - 1][j];
        }

        cout << "Permutation: ";
        for (int x : perm) cout << x << " ";
        cout << "-> Bottom: ";
        for (int x : bottom) cout << x << " ";
        cout << "\n";

        if (bottom < best_bottom) {
            best_bottom = bottom;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    cout << "Best bottom: ";
    for (int x : best_bottom) cout << x << " ";
    cout << "\n";

    return 0;
}
