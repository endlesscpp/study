#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
/**
 * need to use a more concise dp problem.
 */
int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();  // m rows
        int n = matrix[0].size(); // n cols
        int x[m][n] = {};
        int y[m][n] = {};
        
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    x[i][j] = ++cnt;
                } else {
                    cnt = 0;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                if (matrix[j][i] == 1) {
                    y[j][i] = ++cnt;
                } else {
                    cnt = 0;
                }
            }
        }

        int maxsz = 0;
        for (int i = 0; i < n; i++) {
            int sz = 0;
            for (int j = 0; j < n - i && j < m; j++) {
                if (min(x[j][i+j], y[j][i+j]) > sz) {
                    sz++;
                    maxsz = max(sz, maxsz);
                } else {
                    sz = min(x[j][i+j], y[j][i+j]);
                }
            }
        }
        for (int i = 1; i < m; i++) {
            int sz = 0;
            for (int j = 0; j < m - i && j < n; j++) {
                if (min(x[i+j][j], y[i+j][j]) > sz) {
                    sz++;
                    maxsz = max(sz, maxsz);
                } else {
                    sz = min(x[i+j][j], y[i+j][j]);
                }
            }
        }

        return maxsz;
    }
};

int main() {
    vector<vector<char>> matrix = {
        {1, 0, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0}
    };

    Solution s;
    int cnt = s.maximalSquare(matrix);
    cout << "cnt = " << cnt << endl;
    return 0;
}
