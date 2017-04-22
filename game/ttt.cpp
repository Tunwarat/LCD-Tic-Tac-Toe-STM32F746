#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    char grid[9];
    char *gptr = grid;
    int cposition = 0;

    bool moved = false;
    bool xturn = false;

    while (true)
    {
        cout << "1" ;
        char tmp;
        cin >> tmp;
        while (true && (!moved))
        {
            cout << "0" ;
            switch (tmp)
            {
            case 'a':
                if (cposition - 1 < 0)
                {
                    break;
                }
                else
                {
                    cposition--;
                    moved = !moved;
                }
                break;
            case 'd':
                if (cposition + 1 > 8)
                {
                    break;
                }
                else
                {
                    cposition++;
                    moved = !moved;
                }
                break;
            case 'w':
                if (cposition - 3 < 0)
                {
                    break;
                }
                else
                {
                    cposition -= 3;
                    moved = !moved;
                }
                break;
            case 's':
                if (cposition + 3 > 8)
                {
                    break;
                }
                else
                {
                    cposition += 3;
                    moved = !moved;
                }
                break;
            default:
                break;
            }
            if (moved) 
            {
                break;
            }
        }
        cout << cposition << endl;
        moved = !moved;
    }
}