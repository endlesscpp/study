#include <stdio.h>
#include <vector>
using namespace std;

// dynamic programming
// TODO：we can use the 1-D rotating array to represent the 2-D DP array.
class Solution2 {
public:
    int uniquePathsWithObstacles(vector<vector<int> >& obstacleGrid)
    {
        int m = obstacleGrid.size();
        if (m == 0)
            return 0;
        
        int n = obstacleGrid[0].size();
        if (n == 0)
            return 0;

        int dp[m][n];

        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (obstacleGrid[i][j] == 1)
                    dp[i][j] = 0;
                else if (i == m-1 && j == n-1)
                    dp[i][j] = 1;
                else if (i == m-1)
                    dp[i][j] = dp[i][j+1];
                else if (j == n-1)
                    dp[i][j] = dp[i+1][j];
                else
                    dp[i][j] = dp[i][j+1] + dp[i+1][j];
            }
        }

        return dp[0][0];
    }
};


int main()
{
    Solution2 s2;
    vector<vector<int> > v;
    for (int i = 0; i<3; i++)
        v.push_back( { 0, 0, 0 } );

    v[1][1] = 1;


    int ans = s2.uniquePathsWithObstacles(v);
    printf("ans = %d\n", ans);

    return 0;
}

