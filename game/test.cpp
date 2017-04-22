#include <iostream>
using namespace std;
int main ()
{
    bool a = false;
    while(1)
    {
        cout << a << endl;
        a = !a;
    }
}