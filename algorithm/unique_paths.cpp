#include <stdio.h>

// memorized search
class Solution {
public:
    int dfs(int i, int j) {
        if (i >= m_m || j >= m_n)
            return 0;
        if (i == m_m-1 && j == m_n-1) {
            m_dp[i][j] = 1;
            return 1;
        }
        
        if (m_dp[i][j] == -1)
            m_dp[i][j] = dfs(i+1, j) + dfs(i, j+1);
        
        return m_dp[i][j];
    }
    
    int uniquePaths(int m, int n) {
        m_m = m;
        m_n = n;
        
        for (int i = 0; i<m; i++)
            for (int j = 0; j<n; j++)
                m_dp[i][j] = -1;
                
        return dfs(0, 0);
    }
private:
    int m_m;
    int m_n;
    int m_dp[100][100];
};

// dynamic programming
class Solution2 {
public:
    int uniquePaths(int m, int n) {
        if (m <= 0 || n <= 0)
            return 0;

        int dp[m][n];

        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (i == m-1 && j == n-1)
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
    Solution s1;
    Solution2 s2;

    for (int m = 1; m<100; m++) {
        int ans1 = s1.uniquePaths(m, m);
        int ans2 = s2.uniquePaths(m, m);

        if (ans1 != ans2) {
            printf("incorrect, m = %d\n", m);
            return -1;
        }
    }

    printf("correct\n");
    return 0;
}

