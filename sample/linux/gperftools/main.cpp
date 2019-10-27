#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

using namespace std;

class BigNumber
{
public:

    BigNumber(int i)
    {
        cout << "BigNumber(" << i  << ")" << endl;
        digits = new char[100];
    }

    ~BigNumber()
    {
        if (digits != NULL)
            delete[] digits;
    }

private:

    char* digits = NULL;

};

int main() {
    cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

    vector<BigNumber*> v;

    for(int i=0; i< 100; i++)
    {
        v.push_back(new BigNumber(i));
    }

    return 0;
}