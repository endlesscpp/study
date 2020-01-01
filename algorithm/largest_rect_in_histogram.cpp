#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int largestRectangleArea(vector<int>& height)
{
    int max = 0;
    height.push_back(0);
    stack<int> s; //maintain a increasing stack, the item is the index

    for (int i = 0; i < height.size(); i++) {
        if (s.empty() || height[i] >= height[s.top()]) {
            s.push(i);
        } else {
            while (!s.empty() && height[i] < height[s.top()]) {
                int j = s.top();
                s.pop();

                int len = s.empty() ? i: i-s.top()-1;
                int area = len * height[j];
                if (max < area)
                    max = area;
            }
            s.push(i);
        }
    }

    return max;
}


int main()
{
    vector<int> heights;
    heights.push_back(1);
    heights.push_back(1);

    int ans = largestRectangleArea(heights);
    cout<<"ans = "<<ans<<endl;
    return 0;
}
