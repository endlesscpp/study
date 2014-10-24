#include <vector>
#include <stack>
#include <iostream>
using namespace std;


    int calcMaxArea(vector<int>& heights)
    {
        for (int i = 0; i<heights.size(); i++)
            cout<<heights[i]<<",";
        cout<<endl;

        stack<int> stack;
        int max = 0;
    
        for (int i = 0; i < heights.size(); i++) {
            if (stack.empty() || heights[i] > heights[stack.top()]) {
                stack.push(i);
            } else {
                while (!stack.empty() && heights[i] <= heights[stack.top()]) {
                    int j = stack.top();
                    stack.pop();
    
                    int length = stack.empty() ? i : i - stack.top() - 1;
                    int area = length * heights[j];
                    if (max < area)
                        max = area;
                }
                stack.push(i);
            }
        }
    
        return max;
    }
    
    // m*n
    int maximalRectangle(vector<vector<char> >& matrix)
    {
        int m = matrix.size();
        if (m == 0)
            return 0;
    
        int n = matrix[0].size();
        if (n == 0)
            return 0;
    
        int max = 0;
        vector<int> heights(n+1, 0);
    
        for (int i = 0; i<m; i++) {
            //for each row, calc it's height array
            for (int j = 0; j < n; j++) {
                heights[j] = 0;
                for (int k = i; k >= 0; k--) {
                    if (matrix[k][j] == '1')
                        heights[j]++;
                    else
                        break;
                }
            }
            
            int area = calcMaxArea(heights);
            if (max < area)
                max = area;
        }
    
        return max;
    }


int main()
{
    vector<vector<char> > vv;
    vector<char> v;
    v.push_back('0');
    v.push_back('1');
    vv.push_back(v);

    int ans = maximalRectangle(vv);
    cout<<"ans = "<<ans<<endl;

    return 0;
}

