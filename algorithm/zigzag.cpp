#include <iostream>
#include <string>
using namespace std;

int getOldIndex(int i, int j, int nRows)
{
    int index = (j/2) * (nRows + nRows/2);
    if (j%2 == 1) {
        index += nRows;
        index += (i/2);
    }
    else
        index += i;

    return index;
}

    string convert(string s, int nRows) {
        string ans;
        int len = s.length();
        
        int step = 2;
        int i = 0, j = 0;
        for (int k = 0; k<len; k++) {
            int index = getOldIndex(i, j, nRows);
            //printf("i = %d, j = %d, index = %d\n", i, j, index);
            if (index >= len) {
                i++;
                j = 0;
                step = (step == 1) ? 2 : 1;
            } 
            
            int oldIndex = getOldIndex(i, j, nRows); 

            //printf("2, i = %d, j = %d, index = %d\n", i, j, oldIndex);

            ans += s[oldIndex];
            j += step;
        }
        
        return ans;
    }

int main()
{
    //string input = "PAYPALISHIRING";
    //string ans = "PAHNAPLSIIGYIR"

    string input = "ABC";
    string ans = "ACB";
    string output = convert(input, 3);

    cout<<output<<endl;
    if (ans == output)
        cout<<"equal"<<endl;

    return 0;
}


