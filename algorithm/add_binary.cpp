#include <string>
#include <iostream>
using namespace std;

    string addBinary(string a, string b) {
        if (a.empty())
            return b;
        if (b.empty())
            return a;
        
        string ans;
        
        int i = a.length()-1;
        int j = b.length()-1;
        int carry = 0;
        
        while (i >= 0 || j >= 0 || carry > 0) {
            int m = (i >= 0) ? a[i--] - '0' : 0;
            m += (j >= 0) ? b[j--] - '0': 0;
            m += carry;
            cout<<"m = "<<m<<endl;
            
            if (m >= 2) {
                carry = 1;
                m -= 2;
            } else {
                carry = 0;
            }
            
            ans.insert(ans.begin(), m > 0 ? '1' : '0');
        }
        
        return ans;
    }

int main()
{
    string a = "1";
    string b = "1";
    cout<<addBinary(a, b)<<endl;

    return 0;
}

