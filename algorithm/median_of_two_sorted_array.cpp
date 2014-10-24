#include <iostream>
using namespace std;
#include <stdio.h>
/*
 * [b1, e1)
 * [b2, e2)
 */

int findKLargest(int A[], int b1, int e1, int B[], int b2, int e2, int k) {
    printf("b1 = %d, e1 = %d, b2 = %d, e2 = %d, k = %d\n", b1, e1, b2, e2, k);
    if (b1 >= e1)
    {
        // printf("B, b2 = %d, e2 = %d, k = %d\n", b2, e2, k);
        return B[e2-k];
    }

    if (b2 >= e2) {
        // printf("A, b1 = %d, e1 = %d, k = %d\n", b1, e1, k);
        return A[e1-k];
    }

    int m1 = (b1+e1)/2;
    int m2 = (b2+e2)/2;

    if (A[m1] <= B[m2]) {
        if (e1-m1+e2-m2 > k)
            return findKLargest(A, m1+1, e1, B, b2, e2, k);
        else
            return findKLargest(A, b1, e1, B, b2, m2, k-(e2-m2));
    } else {
        if (e2-m2+e1-m1 > k)
            return findKLargest(B, m2+1, e2, A, b1, e1, k);
        else
            return findKLargest(B, b2, e2, A, b1, m1, k-(e1-m1));
    }
}

int findMedianSortedArrays(int A[], int m, int B[], int n) {
    int k = (m + n)/2 + 1;

    printf("---begin, m = %d, n = %d, k = %d\n", m, n, k);
    return findKLargest(A, 0, m, B, 0, n, k);
}

int main()
{
    int a = 7;
    int b = 4;
    int c = a + b % 2;
    printf("c = %d\n", c);

    int A[] = {1, 2, 3, 5};
    int B[] = {7, 8, 9};

    int ans = findMedianSortedArrays(A, sizeof(A)/sizeof(int), B, sizeof(B)/sizeof(int));
    
    cout<<ans<<endl;
}

