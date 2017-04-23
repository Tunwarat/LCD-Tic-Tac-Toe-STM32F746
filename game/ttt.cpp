#include <iostream>
#include <stdio.h>

using namespace std;

bool select(bool xturn, int cpos, char *gptr);
bool is_x_win(char *gptr, bool xturn);
bool is_win(char *g, char a);
bool game_over(char *gptr, char a);
void print_grid(char *gptr);
void clean_grid(char *gptr);

int main()
{
    char grid[9];
    char *gptr = grid;
    clean_grid(gptr);
    int cpos = 0;

    bool moved = false;
    bool xturn = true;

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
            if (game_over(gptr, 'x'))
            {
                while (1) {
                    cin >> tmp;
                    if (tmp == 'j')
                    {
                        cpos = 0;
                        clean_grid(gptr);
                        xturn = true;
                        break;
                    }
                }
            }
            else if (game_over(gptr, 'o'))
            {
                while (1) {
                    cin >> tmp;
                    if (tmp == 'j')
                    {
                        cpos = 0;
                        clean_grid(gptr);
                        xturn = true;
                        break;
                    }
                }
            }
            moved = !moved;
            continue;
        }
    }
}

bool game_over(char *gptr, char a)
{
    if (is_win(gptr, a) == 1)
    {
        cout << "GAME OVER" << endl
             << "Winner is " << a << endl;
        return true;
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

// bool is_x_win(char *gptr, bool xturn)
// {
//     if (xturn)
//     {
//         char t = 'x';
//         return is_win(gptr, t);
//     }
//     else if (!xturn)
//     {
//         cout << "this is o turn" << endl;
//         char t = 'o';
//         return is_win(gptr, t);
//     }
// }

bool is_win(char *g, char a)
{
    if ((a == *(g + 0)) && (a == *(g + 3)) && (a == *(g + 6)))
    {
        return true;
    }
    else if ((a == *(g + 1)) && (a == *(g + 4)) && (a == *(g + 7)))
    {
        return true;
    }
    else if ((a == *(g + 2)) && (a == *(g + 5)) && (a == *(g + 8)))
    {
        return true;
    }
    else if ((a == *(g + 0)) && (a == *(g + 1)) && (a == *(g + 2)))
    {
        return true;
    }
    else if ((a == *(g + 3)) && (a == *(g + 4)) && (a == *(g + 5)))
    {
        return true;
    }
    else if ((a == *(g + 6)) && (a == *(g + 7)) && (a == *(g + 8)))
    {
        return true;
    }
    else if ((a == *(g + 0)) && (a == *(g + 4)) && (a == *(g + 8)))
    {
        return true;
    }
    else if ((a == *(g + 2)) && (a == *(g + 4)) && (a == *(g + 6)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void print_grid(char *gptr)
{
    int i = 0;
    for (i = 0; i < 9; i++)
    {
        if ((i == 2) || (i == 5) || (i == 8))
        {
            cout << *(gptr + i);
        }
        else
        {
            cout << *(gptr + i) << "|";
        }
        if ((i == 2) || (i == 5))
        {
            cout << endl;
            cout << "_|_|_" << endl;
        }
        if (i == 8)
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