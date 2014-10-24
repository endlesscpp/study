#include <algorithm>
#include <stdio.h>

static const int MAX_M = 15;
int M, X;
double P;

double dp[2][(1 << MAX_M) + 1];

void solve()
{
    int n = 1 << M;

    double* prev = dp[0];
    double* next = dp[1];

    for (int i = 0; i<= n+1; i++)
        prev[i] = 0;
    prev[n] = 1.0;

    for (int r = 0; r<M; r++) {
        for (int i = 0; i<=n; i++) {
            int step = std::min(i, n-i);
            double t = 0.0;

            printf("*****i = %d, step = %d\n", i, step);

            for (int j = 0; j <= step; j++) {
                printf("%.6f*P + %.6f*(1-P)\n", prev[i+j], prev[i-j]);
                t = std::max(t, P * prev[i+j] + (1-P) * prev[i - j]);
            }

            printf("t = %.6f\n", t);
            next[i] = t;
        }

        std::swap(prev, next);
    }

    int i = (long long)X * n / 1000000;

    printf("*****************\n");
    printf("i = %d\n", i);
    printf("%.6f\n", prev[i]);
}


int main()
{
    M = 2;
    P = 0.5;
    X = 250000;

    solve();

    return 0;
}

