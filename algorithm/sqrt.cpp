#include <vector>
#include <iostream>
using namespace std;


    int sqrt(int x) {
        if (x < 2)
            return x;
        
        int begin = 1;
        int end = x / 2 + 1;
        int last_mid;
        
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (mid == (x / mid))
                return mid;
            
            if (mid < x/mid) {
                last_mid = mid;
                begin = mid + 1;
            }
            else
                end = mid;
        }
        
        return last_mid;
    }


int main()
{
    int a = sqrt(6);
    cout<<"ans = "<<a<<endl;

    return 0;
}

