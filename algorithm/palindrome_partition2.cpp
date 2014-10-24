#include <string>
#include <iostream>
#include <limits.h>
#include <stdio.h>
using namespace std;

bool* g_palindrome; //palindrome[i][j] indicate if s[i, j] is a palindrome
int* g_minCutCache;

int calcMinCut(string& s, int len, int begin)
{
    if (begin >= len)
        return -1;

    if (g_minCutCache[begin] != -1)
        return g_minCutCache[begin];

    int min = INT_MAX;
    for (int i = begin; i<len; i++) {
        if (g_palindrome[begin*len + i]) {
            int val = calcMinCut(s, len, i+1);
            printf("begin = %d, i+1 = %d, val = %d\n", begin, i+1, val);
            if (min > val)
                min = val;
        }
    }

    min = min+1;
    g_minCutCache[begin] = min;
    return min;
}

void preComputePalindrome(const string& s, int len)
{
    for (int i = 0; i<len; i++) {
        g_palindrome[ i*len + i ] = true; //dp[i][i] = true
    }

    for (int i = 0; i<len-1; i++) {
        if (s[i] == s[i+1]) { //dp[i][i+1] = true
            g_palindrome[ i*len + (i+1) ] = true;
        }
    }


    for (int step = 2; step < len; step++ ) { //dp[i][i+step] = (s[i] == s[i+step] && dp[i+1][i+step-1])
        for (int i = 0; i<len-step; i++) {
            if (s[i] == s[i+step] && g_palindrome[ (i+1)*len + (i+step-1) ]) {
                g_palindrome[i*len + (i+step)] = true;
            }
        }
    }
}

int minCut(string s) {
    int len = s.length();
    if (len <= 1)
        return 0;

    g_palindrome = new bool[len*len];
    memset(g_palindrome, 0, len*len*sizeof(bool));

    g_minCutCache = new int[len];
    for (int i = 0; i<len; i++)
        g_minCutCache[i] = -1;

    preComputePalindrome(s, len);
    /*
    for (int i = 0; i<len; i++) {
        for (int j = 0; j<len; j++)
            printf("%d, ", g_palindrome[i*len + j]);
        printf("\n");
    }
    */

    int ans = calcMinCut(s, len, 0);

    delete[] g_minCutCache;
    delete[] g_palindrome;
    return ans;
}


int main()
{
    // string s = "abbab";
    string s = "abcccb";
    int n = minCut(s);
    cout<<"ans = "<<n<<endl;
    return 0;
}


