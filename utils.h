//******************************************************************************
//  Dharampal H S
//  October 12, 2010
//******************************************************************************

#ifndef UTILS_H_
#define UTILS_H_

#define IS_SET(BYTE, BIT) (BYTE & (0x01 << BIT))

/*
int is_set(volatile char byte, volatile int bit)
{
	return (byte & (0x01 << bit));
}
*/

void wait(volatile unsigned int sheepsToCount)
{
	do (sheepsToCount--);
	while (sheepsToCount != 0);
}

#endif /*UTILS_H_*/
