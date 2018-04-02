#include <stdio.h>
#include <algorithm>
#include <unordered_set>
using namespace std;

static const int MAXN = 5002;

typedef struct Point2 {
    int x;
    int y;
} Point2;

struct myHash   
{  
    size_t operator()(const Point2& pt) const  
    {  
        return static_cast<size_t>((pt.x << 16) + pt.y);  
    }  
}; 

bool operator==(const Point2& p1, const Point2& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

static bool isPoint(int px, int py, unordered_set<Point2, myHash>& pts) {
    Point2 p;
    p.x = px;
    p.y = py;
    return pts.find(p) != pts.end();
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
static int calcMaxRect(int* x, int* y, int rows, int cols, unordered_set<Point2, myHash>& pts) {
    int ans = 0;
    int h[cols];
    int l[cols];
    int r[cols];

    // printf("rm = %d\n", x[cols-1]);
    // for (int i = 0; i < cols; i++) {
    //     printf("%d,", x[i]);
    // }
    // printf("\n");

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
            if (isPoint(x[j], y[i-1], pts)) {
                //printf("(%d, %d) is point\n", x[j], y[i-1]);
                h[j] = y[i] - y[i-1];
                l[j] = 0;
                r[j] = x[cols-1];
                left = x[j];
            } else {
                h[j] = h[j] + (y[i] - y[i-1]);
                l[j] = std::max(l[j], left);
            }
            //printf("i = %d, l[%d] = %d, h[%d] = %d\n", i, j, l[j], j, h[j]);
        }

        for (int j = cols-1; j >= 0; j--) {
            int temp = 0;
            if (isPoint(x[j], y[i-1], pts)) {
                right = x[j];
                temp = (x[cols-1])*(y[i]-y[i-1]);
                //printf("w = %d, y[i] = %d, y[i-1] = %d\n", x[cols-1], y[i], y[i-1]);
            } else {
                r[j] = std::min(r[j], right);
                temp = (r[j] - l[j]) * h[j];
                //printf("i = %d, l[%d] = %d, r[%d] = %d, h[%d] = %d\n", i, j, l[j], j, r[j], j, h[j]);
            }
            ans = std::max(ans, temp);
        }
    }

     for (int i = 1; i < cols; i++) {
         int t = (x[i] - x[i-1]) * y[rows-1];
         ans = std::max(ans, t);
     }

    return ans;
}



int main() {
    int L; // cols
    int W; // rows

    static int x[MAXN];
    static int y[MAXN];
    unordered_set<Point2, myHash> pts;

    while (scanf("%d%d", &L, &W) == 2) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x[i], &y[i]);
            Point2 pt;
            pt.x = x[i];
            pt.y = y[i];
            pts.insert(pt);
        }
        x[n] = 0;
        x[n+1] = L;
        y[n] = 0;
        y[n+1] = W;
        n = n+2;

        sort(x, x+n);
        sort(y, y+n);

        int cols = 1, rows = 1;
        for (int i = 1; i < n; i++) {
            if (x[i] != x[i-1]) {
                x[cols++] = x[i];
            }
        }
        for (int i = 1; i < n; i++) {
            if (y[i] != y[i-1]) {
                y[rows++] = y[i];
            }
        }

        int ans = 0;
        ans = calcMaxRect(x, y, rows, cols, pts);
        printf("%d\n", ans);
    }
}

