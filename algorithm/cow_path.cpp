#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

class Solution {
    private:
        int rows;
        int cols;
        int* mPoints;
    private:
        /**
         * i - the row in compressed matrix
         * j - the col in compressed matrix
         */
        inline bool isPoint(int i, int j) {
            return mPoints[i*cols+j] != 0;
        }

        /*
         * (0,0) left-top (r,c) bottom-right
         * 1. if f(i-1, j) is point, then
         *      height(i, j) = 1
         *      left(i, j) = 0
         *      right(i, j) = cols-1
         *
         *  2. if f(i-1, j) is not point, then
         *      height(i, j) = height(i-1, j) + 1
         *      left(i, j) = max{left(i-1, j), the first point at the left of (i-1, j) on row (i-1). The boundry (i-1, 0) 
         *                                      is also considered as a point.}
         *      right(i, j) = min{right(i-1, j), the first point at the right of (i-1, j) on row(i-1). the boundry (i-1, cols-1)
         *                                      is also considered as a point.}
         *
         *  The rectangle is [left, right] with height.
         *
         *
         *  Please reference to https://wenku.baidu.com/view/728cd5126edb6f1aff001fbb.html.
         *  This program use the method2.
         */
        int calcMaxRect(int* x, int* y) {
            int ans = 0;
            int h[cols];
            int l[cols];
            int r[cols];

            for (int i = 0; i < cols; i++) {
                h[i] = 0;
                l[i] = 0;
                r[i] = x[cols-1];
            }

            // 从第2行开始遍历，但是要考察上一行的点是否为障碍点
            for (int i = 1; i < rows; i++) {
                int left = 0;
                int right = x[cols-1];
                // 这儿用的是[left, right].
                for (int j = 0; j < cols; j++) {
                    if (isPoint(i-1, j)) {
                        h[j] = y[i] - y[i-1];
                        l[j] = 0;
                        r[j] = x[cols-1];
                        left = x[j];
                    } else {
                        h[j] = h[j] + (y[i] - y[i-1]);
                        l[j] = std::max(l[j], left);
                    }
                }

                for (int j = cols-1; j >= 0; j--) {
                    int temp = 0;
                    if (isPoint(i-1, j)) {
                        right = x[j];
                        temp = (x[cols-1])*(y[i]-y[i-1]);
                    } else {
                        r[j] = std::min(r[j], right);
                        temp = (r[j] - l[j]) * h[j];
                    }
                    ans = std::max(ans, temp);
                }
            }

            // 计算纵向的区间，因为这些点可能在矩形的边界上
            for (int i = 1; i < cols; i++) {
                int t = (x[i] - x[i-1]) * y[rows-1];
                ans = std::max(ans, t);
            }

            return ans;
        }

    public:
        int calc(int x[], int y[], int n) {
            // compress the matrix.
            int x2[n];
            int y2[n];
            memcpy(x2, x, sizeof(int)*n);
            memcpy(y2, y, sizeof(int)*n);

            sort(x, x+n);
            sort(y, y+n);

            int c = 1, r = 1;
            for (int i = 1; i < n; i++) {
                if (x[i] != x[i-1]) {
                    x[c++] = x[i];
                }
            }
            for (int i = 1; i < n; i++) {
                if (y[i] != y[i-1]) {
                    y[r++] = y[i];
                }
            }

            this->rows = r;
            this->cols = c;
            this->mPoints = new int[rows * cols];
            fill_n(mPoints, rows*cols, 0);

            for (int i = 0; i < n; i++) {
                auto r = equal_range(y, y+rows, y2[i]);
                auto c = equal_range(x, x+cols, x2[i]);
                if (r.first != r.second && c.first != c.second) {
                    mPoints[(r.first - &y[0]) * cols + c.first - &x[0]] = 1;
                }
            }

            int ans = calcMaxRect(x, y);
            delete[] mPoints;
            return ans;
        }
};



int main() {
    int L; // cols
    int W; // rows

    while (scanf("%d%d", &L, &W) == 2) {
        int n;
        scanf("%d", &n);
        int x[n+2];
        int y[n+2];

        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x[i], &y[i]);
        }
        x[n] = 0;
        x[n+1] = L;
        y[n] = 0;
        y[n+1] = W;
        n = n+2;


        Solution s;
        int ans = s.calc(x, y, n);
        printf("%d\n", ans);
    }
}

