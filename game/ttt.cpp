#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    char grid[9];
    char* gptr = grid;
    int cposition = 0;

    bool moved = false;
    bool xturn = false;
    
    while (true)
    {
        char tmp;
        cin >> tmp;
        while(true)
        {
            switch(tmp)
            {
                case 'a':
                    if (*(cposition-1 < 0))
                    {
                        break;
                    } else
                    {
                        cposition--;
                    }
                    break;
            }
        }
    }
}