#include <stdio.h>

    int search2(int A[], int l, int r, int x)
    {
        if (l >= r)
            return -1;
    
        // printf("l = %d, r = %d, x = %d\n", l, r, x);

        int m = (l+r)/2;
        if (x == A[m])
            return m;
        
        int m1 = m;
        while (m1 < r-1 && A[m1] == A[r-1])
            m1++;

        printf("l = %d, r = %d, m1 = %d, x = %d\n", l, r, m1, x);
            
        if (A[m1] <= A[r-1]) {
            if (x > A[m1] && x <= A[r-1])
                return search2(A, m1+1, r, x);
            else
                return search2(A, l, m, x);
        } else {
            if (x >= A[l] && x < A[m])
                return search2(A, l, m, x);
            else
                return search2(A, m+1, r, x);
        }
    }
    
    bool search(int A[], int n, int target) {
        int index = search2(A, 0, n, target);
        return (index != -1);
    }


int main()
{
    int A[] = {1, 1, 1, 3, 1};
    int index = search2(A, 0, sizeof(A)/sizeof(int), 3);
    printf("index = %d\n", index);

    return 0;
}

