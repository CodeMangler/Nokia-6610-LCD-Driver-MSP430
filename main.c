//******************************************************************************
//  Dharampal H S
//  October 12, 2010
//******************************************************************************

#include "nokia_6610_lcd.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  lcd_initialize();
  
  // Test lcd + code - Turn on all pixels, then turn them off. Repeat 5 times..
//  int i;
//  for (i = 0; i < 5; i++)
  while(1)
  {
  	lcd_write_command(DAL); // All pixels on
  	wait(65535);
  	lcd_write_command(DALO); // All pixels off
  	wait(65535);
  }
}
