#include <string>
#include <iostream>
using namespace std;

#define MAX_LEN 1000
string longestPalindrome(string s)
{
    int len = s.length();
    if (len == 0 || len == 1)
        return s;

    bool dp[len][len];
    //fill_n( &dp[0][0], len*len, false);
    memset( &dp[0][0], false, len*len*sizeof(false));

    /*
    for (int i = 0; i<MAX_LEN; i++)
        for (int j = 0; j<MAX_LEN; j++)
            dp[i][j] = false;
            */

    for (int i = 0; i<len; i++)
        dp[i][i] = true;

    int max_step = 0;
    int begin = 0;

    for (int i = 0; i<len-1; i++) {
        if (s[i] == s[i+1]) {
            begin = i;
            max_step = 1;
            dp[i][i+1] = true;
        }
    }

    for (int step = 2; step < len; step++) {
        for (int i = 0; i<len-step; i++) {
            if (dp[i+1][i+step-1] && (s[i] == s[i+step])) {
                begin = i;
                max_step = step;
                dp[i][i+step] = true;
            }
        }
    }


    return s.substr(begin, max_step+1);
}

int main()
{
    string str = "abb";
    string substr = longestPalindrome(str);
    cout<<substr<<endl;

    return 0;
}


