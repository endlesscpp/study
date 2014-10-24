#include <vector>
#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    string processOneLine(vector<string>& words, int i, int j, int L, int charCnt, bool lastLine)
    {
        string str;
        int sep_cnt = j - i - 1;
        cout<<"L = "<<L<<", charCnt = "<<charCnt<<endl;
        cout<<"i = "<<i<<", j = "<<j<<endl;

        if (lastLine) {
            while (i < j) {
                str += words[i];
                if (i < j-1)
                    str.append(1, ' ');
                else if (sep_cnt == 0)
                    str.append( L - charCnt, ' ');
                i++;
            }
            str.append(L - charCnt - sep_cnt, ' ');
            cout<<"str.length() = "<<str.length()<<endl;
            return str;
        }

        int aver_space = sep_cnt > 0 ? (L - charCnt)  / sep_cnt : 0;
        int addition_cnt = sep_cnt > 0 ? (L - charCnt) % sep_cnt : 0;
        int sep_idx = 0;
        while (i < j) {
            str += words[i];
            if (i < j-1)
                str.append( aver_space + ((sep_idx < addition_cnt) ? 1 : 0), ' ' );
            sep_idx++;
            i++;
        }

        return str;
    }
    
    vector<string> fullJustify(vector<string> &words, int L) {
        vector<string> ans;
        
        int cnt = 0; // char count
        for (int i = 0, j = 0; j<=words.size(); j++) {
            if (j == words.size()) {
                string str = processOneLine(words, i, j, L, cnt, true);
                ans.push_back(str);
                break;
            }
            
            if (cnt + words[j].length() + (j-i) > L) {
                // consider the empty space.
                // new line
                string str = processOneLine(words, i, j, L, cnt, false);
                ans.push_back(str);
                cnt = 0;
                i = j;
            }
            
            cnt += words[j].length();
        }
        
        return ans;
    }
};


int main()
{
    Solution s;
    // vector<string> words = {"a", "b", "c", "d", "e"};
    vector<string> words = {""};
    vector<string> ans = s.fullJustify(words, 0);
    cout<<"ans.size = "<<ans.size()<<endl;

    for (auto str : ans)
        cout<<str<<endl;

    return 0;
}

