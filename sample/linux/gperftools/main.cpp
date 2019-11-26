#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <list>

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

    std::list<BigNumber*> list;
    std::list<BigNumber*>::iterator it = list.begin();
    list.erase(it);

    return 0;
}