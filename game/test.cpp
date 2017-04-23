#include <iostream>

using namespace std;

void b(int i, int *a)
{
    cout << a << endl;
    *a = i*2;
}

int main ()
{
    int x;
    cout << &x << endl;
    b(9, &x);
}

