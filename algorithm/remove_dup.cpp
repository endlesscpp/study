#include <stdio.h>

    int removeDuplicates(int A[], int n) {
        if (n < 2)
            return n;
        
        int i = 0;
        for (int j = 1; j<n; j++ ) {
            if (A[i] != A[j]) {
                i++;
                A[i] = A[j];
            }
        }
        
        return i+1;
    }


int main()
{
    int A[] = {1,1, 1, 3};
    int len = removeDuplicates( A, sizeof(A) / sizeof(A[0]));

    printf("len = %d\n", len);
    return 0;
}
