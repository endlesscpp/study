#include <vector>
#include <iostream>
using namespace std;

int minimumTotal(vector<vector<int> >& triangle)
{
    int m = triangle.size();
    if (m == 0)
        return 0;

    int total_size = (m * (m+1)) / 2;
    vector<int> dp(total_size, INT_MAX);

    dp[0] = triangle[0][0];

    for (int i = 0; i<m-1; i++) {
        int begin = (i * (i+1) ) / 2;
        int next_begin = ((i+1) * (i+2)) / 2;
        // cout<<"begin = "<<begin<<", next_begin = "<<next_begin<<endl;

        for (int j = 0; j < i+1; j++) {
            dp[next_begin+j] = min(dp[next_begin+j], dp[begin+j] + triangle[i+1][j]);
            dp[next_begin+j+1] = min(dp[next_begin+j+1], dp[begin+j] + triangle[i+1][j+1]);
        }
    }

    int ans = INT_MAX;
    int begin = ((m-1)*m) / 2;
    for (int i = 0; i<m; i++) {
        if (ans > dp[begin+i])
            ans = dp[begin+i];
    }

    return ans;
}

int main()
{
    vector<vector<int> > triangle;
    triangle.push_back( {2} );
    triangle.push_back( {3, 4});
    triangle.push_back( {6, 5, 7} );
    triangle.push_back( {4, 1, 8, 3} );

    int ans = minimumTotal(triangle);
    cout<<"ans = "<<ans<<endl;
    return 0;
}

