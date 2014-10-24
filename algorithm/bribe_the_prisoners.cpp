
/*
 * The problem on P130 of book: <<Programming Contest Challenge Book>>
 */

#include <stdio.h>
#include <algorithm>
#include <limits.h>

#define MAX_Q 50

int P, Q, A[MAX_Q+2];   // A is used to save the data, start from 1

int dp[MAX_Q+1][MAX_Q+2];

void solve()
{
    A[0] = 0;
    A[Q+1] = P+1;

    for (int q = 0; q <= Q; q++)
        dp[q][q+1] = 0;

    for (int w = 2; w <= Q+1; w++) {
        printf("*******************\n");
        for (int i = 0; i+w <= Q+1; i++) {
            int j = i+w;
            int t = INT_MAX;

            for (int k = i+1; k<j; k++)
                t = std::min(t, dp[i][k]+dp[k][j]); // release a[k], then the room for a[k] is empty now.

            printf("i = %d, j = %d\n", i, j);

            dp[i][j] = t + A[j] - A[i] - 2;
        }
    }

    printf("%d\n", dp[0][Q+1]);
}

int main()
{
    P = 20;
    Q = 3;

    A[1] = 3;
    A[2] = 6;
    A[3] = 14;

    solve();

    return 0;
}
