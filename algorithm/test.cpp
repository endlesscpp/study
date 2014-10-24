#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    vector<int> v = {1, 2, 2, 2, 3, 4};
    cout<<"distance = "<<distance(v.begin(), unique(v.begin(), v.end()))<<endl;
    v.erase(unique(v.begin(), v.end()), v.end());
    cout<<"size = "<<v.size()<<endl;

    return 0;
}
