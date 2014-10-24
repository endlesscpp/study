#include <stdio.h>
#include <algorithm>
using namespace std;

void bucket_sort(int A[], int n)
{
    for (int i = 0; i<n; i++) {
        while (A[i] != i+1) {
            if (A[i] <= 0 || A[i] > n || A[i] == A[A[i]-1])
                break;
            swap(A[i], A[A[i] - 1]);
        }
    }
}

int firstMissingPositive(int A[], int n)
{
    if (n == 0)
        return 1;

    bucket_sort(A, n);

    for (int i = 0; i<n; i++)
        printf("%d, ", A[i]);
    printf("\n");

    for (int i = 0; i < n; i++) {
        if (A[i] != i+1)
            return i+1;
    }

    return n+1;
}

int main()
{
    int A[] = {1};
    int ans = firstMissingPositive(A, sizeof(A) / sizeof(A[0]));
    printf("ans = %d\n", ans);

    return 0;
}


