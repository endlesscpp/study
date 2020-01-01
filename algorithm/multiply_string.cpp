#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    string multiply(const string& str, int digit) {
        if (digit == 0)
            return "0";
        if (digit == 1)
            return str;
        
        string ans;
        int carry = 0;
        for (int i = str.length()-1; i >= 0; i--) {
            int curr = (str[i] - '0') * digit;
            curr += carry;
            carry = curr / 10;
            ans.insert(0, 1, (char)(curr % 10 + '0'));
        }
        if (carry > 0)
            ans.insert(0, 1, (char)(carry+'0'));
        
        return ans;
    }
    
    string add(const string& lhs, const string& rhs)
    {
        if (lhs.empty())
            return rhs;
        if (rhs.empty())
            return lhs;
        
        string ans;
        int i = lhs.length() - 1;
        int j = rhs.length() - 1;
        int carry = 0;
        
        while (i >= 0 || j >= 0) {
            int val = carry;
            val += (i >= 0 ? lhs[i] - '0' : 0);
            val += (j >= 0 ? rhs[j] - '0': 0);
            carry = val / 10;
            ans.insert(0, 1, (char)(val % 10 + '0'));
            
            i--;
            j--;
        }
        
        if (carry > 0)
            ans.insert(0, 1, (char)(carry+'0'));
        
        return ans;
    }
    
    string multiply(string num1, string num2) {
        if (num1.empty() || num2.empty())
            return "";
        
        string ans;
        
        bool positive = true;
        if (num1[0] == '-')
            positive = !positive;
        if (num2[0] == '-')
            positive = !positive;
        
        if (num1[0] == '-' || num1[0] == '+')
            num1 = num1.substr(1);
        if (num2[0] == '-' || num2[0] == '+')
            num2 = num2.substr(1);
        
        
        int move = 0;
        for (int i = num1.length()-1; i >= 0; i--) {
            int curr = num1[i] - '0';
            string str = multiply(num2, curr);

            if (!str.empty && str[0] != '0') {
                for (int j = 0; j<move; j++)
                    str.append(1, '0');
            }
            move++;
            cout<<"str = "<<str<<endl;
            ans = add(ans, str);
        }

        if (!positive)
            ans.insert(0, "-");
            
        return ans;
    }
};



int main()
{
    Solution s;
    string ans = s.multiply("98", "9");
    cout<<"ans = "<<ans<<endl;

    return 0;
}

