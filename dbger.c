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
#if LOG_PLATFORM == 0		// MDK_ARM
int stdout_putchar (int ch)
{
	uint8_t cha = ch;
	HAL_UART_Transmit(&huart1, &cha, 1, 10);
	return ch;
}
#elif LOG_PLATFORM == 1		// Linux
int __io_putchar(int ch, FILE *f) {
	(void)f;
	uint8_t cha = ch;
	HAL_UART_Transmit(&huart1, &cha, 1, 10);
	return ch;
}
#endif

#elif LOG_BY_RTT

#if LOG_PLATFORM == 0		// MDK_ARM
int stdout_putchar (int ch)
{
	SEGGER_RTT_PutChar(0, ch);
	return ch;
}
#elif LOG_PLATFORM == 1		// Linux
int __io_putchar(int ch, FILE *f) {
	(void)f;
	SEGGER_RTT_PutChar(0, ch);
	return ch;
}
#endif

#endif

#if LOG_TEST_EN
void log_test(void)
{
	float valf = 3.14;
	char str[] = "LOG TEST";
	
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
