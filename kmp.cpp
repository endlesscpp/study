// use KMP to find the sub string
// get this algorithm from the Dragon book Chapter 3, P87.
#include <stdio.h>
#include <string.h>

// m is the length of str
// a[k] is the map between length and length.
// str[0] .. str[ a[k]-1 ] is the longest (really prefix && postfix )
void calcFailureArray(const char* str, int* a, int m)
{
    a[0] = 0;
    a[1] = 0;

    for (int len = 2; len <= m; len++)
    {
        int t = a[len-1];

        while (t > 0 && str[t] != str[len-1])
            t = a[t];

        if (str[t] == str[len-1])
            a[len] = t + 1;
        else
            a[len] = 0;
    }

    for (int i = 1; i<=m; i++)
        printf("%d ,", a[i]);
    printf("\n");
}

// return the index if find, otherwise return -1
int find(const char* str, const char* substr)
{
    if (str == NULL || substr == NULL)
        return -1;

    int m = strlen(str);
    int n = strlen(substr);

    if (n == 0)
        return 0;
    if (m < n)
        return -1;

    int* f = new int[n+1];
    calcFailureArray(substr, f, n);


    int ans_index = -1;

    int t = 0;
    for (int i = 0; i<m; i++)
    {
        while (t > 0 && str[i] != substr[t])
            t = f[t];

        if (str[i] == substr[t])
            t++;

        // no need else branch because t must be 0 in the else branch
        // else
        //     t = 0;

        if (t == n)
        {
            ans_index = i+1-n;
            break;
        }
    }

    delete[] f;
    return ans_index;
}



int main()
{
    const char* str = "abababaab";
    const char* substr = "ababaa";

    int ans = find(str, substr);
    printf("ans = %d\n", ans);

    return 0;
}
