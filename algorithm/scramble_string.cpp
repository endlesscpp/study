#include <string>
#include <iostream>
#include <map>
using namespace std;

struct Item {
    int b1;
    int b2;
    int len;
};
static bool operator < (const Item& lhs, const Item& rhs)
{
    if (lhs.b1 != rhs.b1)
        return lhs.b1 < rhs.b1;
    if (lhs.b2 != rhs.b2)
        return lhs.b2 < rhs.b2;

    return lhs.len < rhs.len;
}

class Solution {
    public:
        bool isScramble(string& s1, string& s2, int b1, int b2, int len, map<Item, bool>& cache) {
            if (len == 1)
                return s1[b1] == s2[b2];

            Item it;
            it.b1 = b1;
            it.b2 = b2;
            it.len = len;
            if (cache.find(it) != cache.end())
                return cache[it];

            bool bRet = false;
            for (int i = 1; i<len; i++) {
                if (isScramble(s1, s2, b1+0, b2+0, i, cache) && isScramble(s1, s2, b1+i, b2+i, len-i, cache)) {
                    bRet = true;
                    break;
                }
                if (isScramble(s1, s2, b1+0, b2+len-i, i, cache) && isScramble(s1, s2, b1+i, b2+0, len-i, cache)) {
                    bRet = true;
                    break;
                }
            }

            cache[it] = bRet;
            return bRet;
        }

        bool isScramble(string s1, string s2) {
            if (s1.empty() && s2.empty())
                return true;

            int len = s1.length();
            if (s2.length() != len)
                return false;

            map<Item, bool> cache;

            return isScramble(s1, s2, 0, 0, len, cache);
        }
};

int main()
{
    Solution s;
    string s1 = "great";
    string s2 = "rgate";
    bool ans = s.isScramble(s1, s2);

    cout<<"ans = " << ans << endl;

    return 0;
}


