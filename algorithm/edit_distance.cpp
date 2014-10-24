#include <string>
using namespace std;

/*
 * treate the string with length m as one be devided by m+1 dividers.
 * f[i][j]: distance from A[0][i] to B[0][j]
 * str1c => str2d
 *
 * 1) c == d: f[i][j] = f[i-1][j-1]
 * 2) c != d: 
 * replace c with d: f[i][j] = f[i-1][j-1] + 1
 * remove c: f[i][j] = f[i-1][j] + 1
 * add d after c: f[i][j] = f[i][j-1] + 1
 */

int minDistance2(string word1, string word2)
{
    int m = word1.length();
    int n = word2.length();

    int f[m+1][n+1];

    for (int i = 0; i<=m; i++)
        f[i][0] = i;
    for (int i = 0; i<=n; i++)
        f[0][i] = i;

    for (int i = 1; i<=m; i++) {
        for (int j = 1; j<=n; j++) {
            if (word1[i-1] == word2[j-1]) {
                f[i][j] = f[i-1][j-1];
            } else {
                // here attention f[i][j-1] must > f[i-1][j-1]
                f[i][j] = min(min(f[i-1][j-1], f[i][j-1]), f[i-1][j]) + 1;
            }
        }
    }

    return f[m][n];
}

int minDistance(string word1, string word2)
{
    int m = word1.length();
    int n = word2.length();

    if (m < n)
        return minDistance(word2, word1);

    int f[n+1];
    int upper_left = 0; //f[i-1][j-1]

    for (int i = 0; i<=n; i++)
        f[i] = i;

    for (int i = 1; i<=m; i++) {
        upper_left = f[0];
        f[0] = i;

        for (int j = 1; j<=n; j++) {
            int upper = f[j];

            if (word1[i-1] == word2[j-1]) {
                f[j] = upper_left;
            } else {
                f[j] = min(upper_left, min(f[j-1], f[j])) + 1;
            }

            upper_left = upper;
        }
    }

    return f[n];
}


int main()
{
    string word1 = "abcd";
    string word2 = "abcd";

    int ans1 = minDistance(word1, word2);
    int ans2 = minDistance2(word1, word2);

    printf("ans1 = %d, ans2 = %d\n", ans1, ans2);
    return 0;
}
