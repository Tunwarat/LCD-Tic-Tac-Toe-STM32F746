#include <iostream>
#include <stdio.h>

using namespace std;

bool select(bool xturn, int cpos, char *gptr);
void print_grid(char *gptr);
void clean_grid(char *gptr);

int main()
{
    char grid[9];
    char *gptr = grid;
    clean_grid(gptr);
    int cpos = 0;

    bool moved = false;
    bool xturn = false;

    while (true)
    {
        char tmp;
        cin >> tmp;
        while (!moved)
        {
            if (tmp == 'a')
            {
                if ((cpos - 1) < 0)
                {
                    break;
                }
                else
                {
                    cpos--;
                    moved = !moved;
                }
            }
            else if (tmp == 'd')
            {
                if ((cpos + 1) > 8)
                {
                    break;
                }
                else
                {
                    cpos++;
                    moved = !moved;
                }
            }
            else if (tmp == 'w')
            {
                if ((cpos - 3) < 0)
                {
                    break;
                }
                else
                {
                    cpos -= 3;
                    moved = !moved;
                }
            }
            else if (tmp == 's')
            {
                if ((cpos + 3) > 8)
                {
                    break;
                }
                else
                {
                    cpos += 3;
                    moved = !moved;
                }
            }
            else if (tmp == 'j')
            {
                xturn = select(xturn, cpos, gptr);
                moved = !moved;
            }

            if (moved)
            {
                break;
            }
        }

        print_grid(gptr);

        if (moved)
        {
            cout << endl << cpos << endl;
            moved = !moved;
            continue;
        }
    }
}

bool select(bool xturn, int cpos, char *gptr)
{
    if (xturn)
    {
        *(gptr + cpos) = 'x';
    }
    else
    {
        *(gptr + cpos) = 'o';
    }
    return !xturn;
}

void print_grid(char *gptr)
{
    int i = 0;
    for (i = 0; i < 9; i++)
    {
        if ((i == 2) || (i==5) || (i==8))
        {
            cout << *(gptr + i);            
        }
        else
        {
            cout << *(gptr + i) << "|";
        }
        if ((i==2) || (i==5))
        {
            cout << endl;
            cout << "_|_|_" << endl;
        }
        if (i==8)
        {
            cout << endl;
            cout << " | |" << endl;
        }
    }
}

void clean_grid(char *gptr)
{
    int i = 0;
    for (i = 0; i < 9; i++)
    {
        *(gptr + i) = '\0';
    }
}