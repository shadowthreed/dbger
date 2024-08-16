/**
 * @file 	dbger.c
 * @author	shadowthreed@gmail.com
 * @date	20240714
 *			20240809 update: 
 *						1. add stdout_putchar() for RTT;
 *						2. add log_test();
 */
#include "dbger.h"

#if LOG_ENABLE

#if LOG_BY_UART

#include "usart.h"
int stdout_putchar (int ch)
{
	const uint8_t cha = ch;
	HAL_UART_Transmit(&huart1, &cha, 1, 10);
	return ch;
}

#elif LOG_BY_RTT

int stdout_putchar (int ch)
{
	SEGGER_RTT_printf(0, "%c", ch);
	return ch;
}

#endif

#if LOG_TEST
void log_test(void)
{
	float valf = 3.14;
	char str[] = "LOT TEST";
	
	LOG_INIT();
	for(uint8_t i = 0; i < 2; i++) {
		LOG_AST("AST LOG: int[%02d], float[%6.3f], str[%10s]\n", i, valf, str);
		LOG_ERR("ERR LOG: int[%2d], float[%+6.3f], str[%10s]\n", i, valf, str);
		LOG_WAR("WAR LOG: int[%-2d], float[%-6.3f], str[%-10s]\n", i, valf, str);
		LOG_INF("INF LOG: int[%d], float[%f], str[%s]\n", i, valf, str);
		LOG_DBG("DBG LOG: int[%d], float[%f], str[%s]\n", i, valf, str);
		LOG_VBS("VBS LOG: int[%d], float[%f], str[%s]\n", i, valf, str);
		printf("\n");
	}
}
#endif

#endif
