#include <stdio.h>
#include <limits.h>

int maxSubArray(int A[], int n)
{
    int ans = INT_MIN;
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
        
        if (sum > ans) {
            ans = sum;
        }

        if (sum < 0)
            sum = 0;
    }

    return ans;
}



int main()
{
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int ans = maxSubArray(A, sizeof(A) / sizeof(A[0]));

    printf("ans = %d\n", ans);
    return 0;
}

