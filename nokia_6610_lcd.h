//******************************************************************************
//  Nokia 6610 LCD Driver
//
//                MSP430G2231
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |             P1.0|-->LED/DIO {0000 0001}
//            |             P1.6|-->LED/SCK {0100 0000}
//            |             P1.3|-->S2/CS   {0000 1000}
//            |             P1.4|-->RST     {0001 0000}
//             -----------------
//
//               Nokia 6610 LCD
//             ------------------
//(3.3V)VCC|--|VDISPLAY(6) (4)SCLK|--P1.6
//(3.3V)VCC|--|VDIGITAL(1)  (3)DIO|--P1.0
//            |              (5)CS|--P1.3
//        7V--|VLED(10)           |
//            |           (2)RESET|--P1.4
//       GND--|LEDGND(9)          |
//       GND--|GND(8)             |
//			   -------------------
//
// Reference: http://www.sparkfun.com/tutorial/Nokia%206100%20LCD%20Display%20Driver.pdf - James P. Lynch
//
//  Dharampal H S
//  October 12, 2010
//******************************************************************************

#ifndef NOKIA_6610_LCD_H_
#define NOKIA_6610_LCD_H_

#include  <msp430g2231.h>
#include "utils.h"

// LCD Commands (Philips)
#define NOP 0x00
#define SWRESET 0x01 // Software Reset
#define SLEEPIN 0x10 // Sleep out
#define SLEEPOUT 0x11 // Sleep out
#define DALO 0x22 // All pixels off
#define DAL 0x23 // All pixels on
#define SETCON 0x25 // Set Contrast
#define DISPOFF 0x28 // Display Off
#define DISPON 0x29 // Display On
#define MADCTL 0x36 // Memory Access Control
#define COLMOD 0x3A // Pixel format/Color mode

// LCD Data Constants
#define TWELVE_BITS_PER_PIXEL 0x03
#define DEFAULT_LCD_ORIENTATION 0x08

// Other constants
#define DEFAULT_WAIT 10000 // Not in ms, not in sec, not in any time units. Just the number of sheeps to be counted before snapping out :D

void lcd_reset(void)
{
	P1OUT &= ~BIT4; // Pull down P1.4 which's tied to LCD's RST
	wait(DEFAULT_WAIT);
	P1OUT |= BIT4; // Pull back up P1.4 which's tied to LCD's RST
	wait(DEFAULT_WAIT);
}

// Assumes serial chip is initialized. Just writes out the byte of data to SPI, starting from the MSB (bit 7) to the LSB (bit 0).
void lcd_serial_write(volatile char byte)
{
	volatile int i;
	for(i = 7; i >= 0; i--)
	{
		// 1. Lower the clock
		P1OUT &= ~BIT6;
		// 2. Set the SDIN/DIO (Serial Data) bit
		if(IS_SET(byte, i))
			P1OUT |=  BIT0; // Turn on DIO
		else
			P1OUT &= ~BIT0; // Turn off DIO

		// 3. Raise the clock. (This is when the serial data is sampled)
		P1OUT |= BIT6;
		// 4. Wait
		wait(DEFAULT_WAIT);
		// 5. Lower the clock back (Redundant, but well)
		P1OUT &= ~BIT6;		
	}	
}

void lcd_write_command(volatile char command)
{
	// Enable serial chip
	P1OUT &= ~BIT3; // /CS -> Falling edge enables the Serial chip
	
	// ** In serial communications, SDIN/DIO (Serial Data -> P1.0) is sampled at the rising edge of SCLK (Serial Clock -> P1.6)
	
	// Send the command bit -> LOW to indicate command
	// 1. Lower the clock
	P1OUT &= ~BIT6;
	// 2. Set the SDIN/DIO (Serial Data) bit (to low for command)
	P1OUT &= ~BIT0;
	// 3. Raise the clock. (This is when the serial data is sampled)
	P1OUT |= BIT6;
	// 4. Wait
	wait(DEFAULT_WAIT);
	// 5. Lower the clock back
	P1OUT &= ~BIT6;
	
	lcd_serial_write(command);
	
	// Transmission done. Disable the Serial chip.
	P1OUT |= BIT3; // /CS -> Falling edge enables the Serial chip
}

void lcd_write_data(volatile char data)
{
	// Enable serial chip
	P1OUT &= ~BIT3; // /CS -> Falling edge enables the Serial chip
	
	// ** In serial communications, SDIN/DIO (Serial Data -> P1.0) is sampled at the rising edge of SCLK (Serial Clock -> P1.6)
	
	// Send the command bit -> HIGH to indicate data
	// 1. Lower the clock
	P1OUT &= ~BIT6;
	// 2. Set the SDIN/DIO (Serial Data) bit (to high for data)
	P1OUT |= BIT0;
	// 3. Raise the clock. (This is when the serial data is sampled)
	P1OUT |= BIT6;
	// 4. Wait
	wait(DEFAULT_WAIT);
	// 5. Lower the clock back
	P1OUT &= ~BIT6;
	
	lcd_serial_write(data);
	
	// Transmission done. Disable the Serial chip.
	P1OUT |= BIT3; // /CS -> Falling edge enables the Serial chip
}

void lcd_initialize(void)
{
	P1DIR |= 0x59; // Set P1.0, P1.3, P1.4 and P1.6 to output direction (0101 1001) (since they'd be used for sending out signals - CLK/DATA/...)

	lcd_reset();
	
	// P1.4 connected to RST
	P1OUT |= BIT4; // Keep RST high. Turning RST Low and then back to High resets the LCD.
	
	// P1.3 connected to CS (Chip Select)
	P1OUT |= BIT3; // CS -> Select parallel interface or Enable serial chip (Active Low). Falling edge of the pin enables Serial, and rising disables it..
	
	// Exit SLEEPIN
	lcd_write_command(SLEEPOUT);
	
	// Color interface pixel format
	lcd_write_command(COLMOD);
	lcd_write_data(TWELVE_BITS_PER_PIXEL);
	
	// Initialize Memory Access Controller for LCD Orientation
	lcd_write_command(MADCTL);
	lcd_write_data(DEFAULT_LCD_ORIENTATION);

	// Initialize LCD Contrast
	lcd_write_command(SETCON);
	lcd_write_data(0x30);
	wait(DEFAULT_WAIT);
	
	// Turn on the display
	lcd_write_command(DISPON);
}

#endif /*NOKIA_6610_LCD_H_*/
