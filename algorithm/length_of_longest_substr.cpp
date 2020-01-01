#include <iostream>
#include <string>
#include <map>
using namespace std;

    int lengthOfLongestSubstring(string s) {
        if (s.empty())
            return 0;
        
        int max_len = 0;
        int begin = 0;
        int end;
        int mp[256];
        for (int i = 0; i<256; i++)
            mp[i] = -1;
        
        for (end = 0; end < s.length(); end++) {
            
            int existingIndex = mp[(unsigned char)(s[end])];
            if (existingIndex != -1) {
                for (int i = begin; i<=existingIndex; i++)
                    mp[ (unsigned char)(s[i]) ] = -1;

                int len = end - begin;
                if (len > max_len)
                    max_len = len;
                    
                begin = existingIndex + 1;
            }
            
            mp[ (unsigned char)(s[end]) ] = end;
        }
        
        if (end - begin > max_len)
            max_len = end - begin;
            
        return max_len;
    }

int main()
{
    string str = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";
    int len = lengthOfLongestSubstring(str);

    cout<<len<<endl;
    return 0;
}
