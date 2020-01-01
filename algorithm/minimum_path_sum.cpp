#include <vector>
#include <stdio.h>
using namespace std;

// use a 2D array to represent the DP.
int minPathSum2(vector<vector<int> >& grid)
{
    int m = grid.size();
    if (m == 0)
        return 0;

    int n = grid[0].size();
    if (n == 0)
        return 0;

    int dp[m][n]; // the sum from [0][0] to [i][j]

    for (int i = 0; i<m; i++) {
        for (int j = 0; j<n; j++) {
            if (i == 0 && j == 0)
                dp[i][j] = grid[i][j];
            else if (i == 0)
                dp[i][j] = dp[i][j-1] + grid[i][j];
            else if (j == 0)
                dp[i][j] = dp[i-1][j] + grid[i][j];
            else
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }

    return dp[m-1][n-1];
}


    // use a 1-D array to represent the DP. (rotating array)
    int minPathSum(vector<vector<int> >& grid)
    {
        int m = grid.size();
        if (m == 0)
            return 0;
    
        int n = grid[0].size();
        if (n == 0)
            return 0;
    
        int dp[n];
        dp[0] = grid[0][0];
        for (int i = 1; i<n; i++)
            dp[i] = grid[0][i] + dp[i-1];

        for (int i = 1; i<m; i++) {
            for (int j = 0; j<n; j++) {
                if (j == 0)
                    dp[j] = dp[j] + grid[i][j];
                else
                    dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
            }
        }
    
        return dp[n-1];
    }


int main()
{
    vector<vector<int> > v;
    v.push_back( {1, 2, 3} );
    v.push_back( {4, 5, 6} );

    int path = minPathSum(v);
    printf("path = %d\n", path);

    return 0;
}
