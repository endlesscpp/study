#include <stdio.h>
#include <iostream>
using namespace std;

bool isMatch(const char* s, const char* p)
{
    if (*p == '\0')
        return *s == '\0';
    
    if (*(p+1) != '*') {
        if (*s == *p || (*p == '.' && *s != '\0'))
            return isMatch(s+1, p+1);
        else
            return false;
    } else {
        while(*s == *p || (*p == '.' && *s != '\0') ) {
            if (isMatch(s, p+2))
                return true;
            s++;
        }
        return isMatch(s, p+2);
    }
}

int main()
{
    bool ans = isMatch("aab", "c*a*b");
    cout<<"ans = "<< (ans ? "true" : "false") <<endl;
    return 0;
}
