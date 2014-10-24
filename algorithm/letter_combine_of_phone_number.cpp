#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Solution {
    public:
        static const string digit_to_letters[];

        /*
        vector<string> letterCombinations2(vector<string>& prev, string digits, int begin, int end) {
            if (begin == end)
                return prev;

            vector<string> ans;
            string candidates = digit_to_letters[ digits[begin] - '0' ];
            for (int i = 0; i<candidates.length(); i++) {
                    for (string s : prev) {
                        s.append(1, candidates[i]);
                        ans.push_back(s);
                    }
            }

            return letterCombinations2(ans, digits, begin+1, end);
        }

        vector<string> letterCombinations(string digits) {
            vector<string> prev;
            prev.push_back("");
            return letterCombinations2(prev, digits, 0, digits.length());
        }
        */
        void dfs(string path, string digits, int begin, vector<string>& ans) {
            if (begin == digits.length()) {
                ans.push_back(path);
                return;
            }

            string str = digit_to_letters[ digits[begin] - '0'];
            for (auto ch : str )
                dfs(path+ch, digits, begin+1, ans);
        }

        vector<string> letterCombinations(string digits) {
            vector<string> ans;
            dfs("", digits, 0, ans);
            return ans;
        }

};

const string Solution::digit_to_letters[] = 
{
    "",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz",
};

int main()
{
    Solution solution;
    vector<string> ans = solution.letterCombinations("23");
    cout<<"[";
    for (string s : ans)
        cout<<s<<",";
    cout<<"]"<<endl;

    return 0;
}

