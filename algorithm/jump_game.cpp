#include <stdio.h>
#include <vector>
using namespace std;

bool canJump(int A[], int n) {
    vector<int> f(n, 0);
    f[0] = 0;
    for (int i = 1; i < n; i++) {
        f[i] = max(f[i - 1], A[i - 1]) - 1;
        if (f[i] < 0) return false;;
    }
    return f[n - 1] >= 0;
}

int main()
{
    int A[] = {1, 2};
    bool ret = canJump(A, sizeof(A) / sizeof(A[0]));

    printf("ret = %s\n", ret ? "true" : "false");
    return 0;
}

