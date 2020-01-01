#include <stdio.h>

    int searchInsert(int A[], int n, int target) {
        int begin = 0, end = n;
        
        while (begin < end) {
            int mid = (begin + end) / 2;
            if (A[mid] == target) {
                return mid;
            }
            
            if (A[mid] < target) {
                begin = mid + 1;
            } else {
                end = mid;
            }
        }

        printf("begin = %d, end = %d\n", begin, end);
        return begin;
    }


int main()
{
    int A[] = {1, 3};
    int index = searchInsert(A, sizeof(A)/sizeof(int), 0);

    printf("index = %d\n", index);
    return 0;
}

