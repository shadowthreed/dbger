/**
 * @file 	dbger.c
 * @author	shadowthreed@gmail.com
 * @date	20240714
 */
#include "dbger.h"

#if LOG_ENABLE && LOG_BY_UART
#include "usart.h"
int stdout_putchar (int ch)
{
	const uint8_t cha = ch;
	HAL_UART_Transmit(&huart1, &cha, 1, 10);
	return ch;
}
#endif