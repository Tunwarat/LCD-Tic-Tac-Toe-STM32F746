#include "mbed.h"
#include "LCD_DISCO_F746NG.h"
#include "TS_DISCO_F746NG.h"

LCD_DISCO_F746NG lcd;
LCD_DISCO_F746NG cursor;
//DigitalOut myled(LED1);

Serial pc(USBTX, USBRX);
AnalogIn AinK(A0);
AnalogIn AinX(A1);
AnalogIn AinY(A2);

bool select(bool xturn, int cpos, char *gptr);
bool is_x_win(char *gptr, bool xturn);
bool is_win(char *g, char a);
bool game_over(char *gptr, char a);
uint8_t get_dir();
void print_grid(char *gptr);
void clean_grid(char *gptr);
void lcdDisplayXO(uint16_t x, uint16_t y, char *g);
void cursorDisplay(uint16_t x, uint16_t y);
void print_cursor(int pos);

int main()
{
    char grid[9];
    char *gptr = grid;
    clean_grid(gptr);
    int cpos = 0;
    uint8_t text[30];

    bool moved = false;
    bool xturn = true;

    lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"TIC TAC TOE", LEFT_MODE);
    wait(2.0);

    lcd.Clear(LCD_COLOR_DARKGREEN);
    lcd.SetBackColor(LCD_COLOR_DARKGREEN);
    lcd.SetTextColor(LCD_COLOR_YELLOW);

    lcd.DrawLine(160, 0, 160, 272);
    lcd.DrawLine(160 * 2, 0, 160 * 2, 272);
    lcd.DrawLine(0, 90, 480, 90);
    lcd.DrawLine(0, 180, 480, 180);

    float AK, AX, AY;
    // uint16_t ADCData;

    pc.baud(9600);
    pc.format(8, SerialBase::None, 1);
    pc.printf("\n\rTest ADC Value\n\r");

    while (1)
    {
        wait(1);
        AK = AinK.read();
        AX = AinX.read();
        AY = AinY.read();
        uint8_t dir;
        if (AX > 0.9)
        {
            dir = 1;
        }
        else if (AY > 0.9)
        {
            dir = 2;
        }
        else if (AX < 0.1)
        {
            dir = 3;
        }
        else if (AY < 0.1)
        {
            dir = 4;
        }
        else if (AK < 0.2)
        {
            dir = 0;
        } else 
				{
					dir = '5';
				}
				
				pc.printf("\n\r%d\n\r", dir);

        pc.printf("AK = %1.3f\n\r", AK);
        pc.printf("AX = %1.3f\n\r", AX);
        pc.printf("AY = %1.3f\n\r", AY);
        print_cursor(cpos);
        while (!moved)
        {
            if (dir == 1)
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
            else if (dir == 3)
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
            else if (dir == 2)
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
            else if (dir == 4)
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
            else if (dir == 0)
            {
                xturn = select(xturn, cpos, gptr);
                moved = !moved;
            } else 
						{
								break;
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
                while (1)
                {
                    //                    cin >> dir;
                    if (dir == 0)
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
                while (1)
                {
                    //                    cin >> dir;
                    if (dir == 0)
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
        //		pc.printf("ADCData = 0x%04X\n\r", ADCData);
  
				pc.printf("please wait\n");
				wait(2.0);
        cursor.Clear(LCD_COLOR_DARKGREEN);
				print_grid(gptr);
    }
}

bool game_over(char *gptr, char a)
{
    if (is_win(gptr, a) == 1)
    {
        //       cout << "GAME OVER" << endl
        //            << "Winner is " << a << endl;
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

void lcdDisplayXO(uint16_t x, uint16_t y, char *g)
{
    if (*g == 'o')
    {
				lcd.DisplayChar(x, y, 'o');
       // lcd.DisplayStringAt(x, y, (uint8_t *)"o", CENTER_MODE);
    }
    else if (*g == 'x')
    {
				lcd.DisplayChar(x, y, 'x');
       // lcd.DisplayStringAt(x, y, (uint8_t *)"x", CENTER_MODE);
    }
}

void print_grid(char *gptr)
{
		lcd.DrawLine(160, 0, 160, 272);
    lcd.DrawLine(160 * 2, 0, 160 * 2, 272);
    lcd.DrawLine(0, 90, 480, 90);
    lcd.DrawLine(0, 180, 480, 180);
    int i = 0;
    for (i = 0; i < 9; i++)
    {
        if (i == 0)
        {
            lcdDisplayXO(20, 20, (gptr + i));
        }
        else if (i == 1)
        {
            lcdDisplayXO(40, 20, (gptr + i));
        }
        else if (i == 2)
        {
            lcdDisplayXO(60, 20, (gptr + i));
        }
        else if (i == 3)
        {
            lcdDisplayXO(20, 40, (gptr + i));
        }
        else if (i == 4)
        {
            lcdDisplayXO(40, 40, (gptr + i));
        }
        else if (i == 5)
        {
            lcdDisplayXO(60, 40, (gptr + i));
        }
        else if (i == 6)
        {
            lcdDisplayXO(20, 60, (gptr + i));
        }
        else if (i == 7)
        {
            lcdDisplayXO(40, 60, (gptr + i));
        }
        else if (i == 8)
        {
            lcdDisplayXO(60, 60, (gptr + i));
        }
    }
		
		for (i = 0; i < 9; i++)
    {
        if ((i == 2) || (i == 5) || (i == 8))
        {
					pc.printf("%c", *(gptr + i));
        }
        else
        {
					pc.printf("%c|", *(gptr + i));
        }
        if ((i == 2) || (i == 5))
        {
					pc.printf("\n\r");
					pc.printf("_|_|_", *(gptr + i));
					pc.printf("\n\r");
        }
        if (i == 8)
        {
					pc.printf("\n\r");
					pc.printf(" | |", *(gptr + i));
					pc.printf("\n\r");
        }
    }
}

void cursorDisplay(uint16_t x, uint16_t y)
{
    cursor.DrawRect(x, y, 10, 10);
}

void print_cursor(int pos)
{
    int i = pos;
    if (i == 0)
    {
        cursorDisplay(20, LINE(1));
    }
    else if (i == 1)
    {
        cursorDisplay(40, LINE(1));
    }
    else if (i == 2)
    {
        cursorDisplay(60, LINE(1));
    }
    else if (i == 3)
    {
        cursorDisplay(20, LINE(2));
    }
    else if (i == 4)
    {
        cursorDisplay(40, LINE(2));
    }
    else if (i == 5)
    {
        cursorDisplay(60, LINE(2));
    }
    else if (i == 6)
    {
        cursorDisplay(20, LINE(3));
    }
    else if (i == 7)
    {
        cursorDisplay(40, LINE(3));
    }
    else if (i == 8)
    {
        cursorDisplay(60, LINE(3));
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
