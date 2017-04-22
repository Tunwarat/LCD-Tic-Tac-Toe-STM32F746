#include "mbed.h"
#include "LCD_DISCO_F746NG.h"

LCD_DISCO_F746NG lcd;
DigitalOut myled(LED1);

Serial pc(USBTX, USBRX);
AnalogIn Ain(A0);


int main()
{
	lcd.DisplayStringAt(0,LINE(1),(uint8_t *)"LCD GRAPHIC",CENTER_MODE);
	wait(1);
	
				lcd.Clear(LCD_COLOR_DARKGREEN);
        lcd.SetBackColor(LCD_COLOR_DARKGREEN);
        lcd.SetTextColor(LCD_COLOR_YELLOW);
	
	lcd.DrawLine(160,0,160,272);
	lcd.DrawLine(160*2,0,160*2,272);
	
		
		float ADCDataFloat;
	uint16_t ADCData;
	
	pc.baud(9600);
	pc.format(8, SerialBase::None, 1);
	pc.printf("\n\rTest ADC Value\n\r");
	
	while(1)
		{
			ADCData = Ain.read_u16();
			ADCDataFloat = Ain.read();
			
	pc.printf("ADCData = 0x%04X\n\r", ADCData);
	pc.printf("ADCDataFloat = %1.3f\n\r", ADCDataFloat);
	pc.printf("Voltage in = %1.3fV\n\r\n\r", ADCDataFloat*3.3L);
			
	wait_ms(800);
	
		}

}
