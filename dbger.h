/**
 * @file	dbger.h
 * @brief	log moduleThis file provides code for outputing the LOG by uart or RTT.
 *          The priority levels as below:
				1.[AST]:Assert      (Highest)
                2.[ERR]:Error
                3.[WAR]:Warnning
                4.[INF]:Info
                5.[DBG]:Debug
                6.[VBS]:Verbose     (Lowest)
 *
 * @note for Using this mode:
 *		1. MUST enable the STDOUT in MDK-ARM -> RTE -> Compiler -> I/O -> STDOUT(user);
 *		2. if LOG_BY_RTT, you can get the LOG in J-Link RTT Viewer;
 *		3. if LOG_BY_UART, you can get the LOG in any UART assistant, like Putty;
 *		4. you can output the LOG by LOG_xxx() micro for different LOG level, or just by printf();
 *
 * @author	shadowthreed@gmail.com
 * @date	20240714
 *			20240809	update: same API for UART and RTT
 */

#ifndef __DBGER_H__
#define __DBGER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define LOG_ENABLE 			1
#define LOG_BY_RTT 			1
#define LOG_BY_UART			(!LOG_BY_RTT)
#define LOG_LEVEL 			6 		// the priority less than or queal to LOG_LEVEL will be output
#define LOG_COLOR_ENABLE 	0
#define LOG_TEST			0

#if LOG_ENABLE
	#include <string.h>
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) 	// strrchr(str, ch): return the last position of ch in str, or NULL
#endif

#if LOG_ENABLE && LOG_COLOR_ENABLE 	// set LOG color
	#define COLOR_RED 		"\033[31m"
	#define COLOR_PINK 		"\033[35m"
	#define COLOR_YELLOW 	"\033[33m"
	#define COLOR_GREEN 	"\033[32m"
	#define COLOR_GRAY 		"\033[37m"
	#define COLOR_DEFAULT 	"\033[0m" 	// off, default white
#else
	#define COLOR_RED
	#define COLOR_PINK
	#define COLOR_YELLOW
	#define COLOR_GREEN
	#define COLOR_GRAY
	#define COLOR_DEFAULT
#endif

#if LOG_ENABLE
	#include <stdio.h>
	#include "RTE_Components.h"
	#ifndef RTE_Compiler_IO_STDOUT_User
		#error	must enable STDOUT in MDK-ARM -> RTE -> Compiler -> I/O -> STDOUT(user).
	#endif
#endif

#if LOG_ENABLE
#if LOG_BY_RTT
	// SEGGER_RTT_SetTerminal(2); 	SEGGER_RTT_SetTerminal(3);  keep for user, eg: terminal2 default for printing protocol data
	#include "SEGGER_RTT.h"
	#include <stdint.h>
	#define LOG_INIT()		SEGGER_RTT_Init()
	#define LOG_DAT(...)	do { if(LOG_LEVEL >= 1) { SEGGER_RTT_SetTerminal(2); printf(##__VA_ARGS__); SEGGER_RTT_SetTerminal(1); }} while(0)		// for print protocol data
	#define LOG_AST(...)    do { if(LOG_LEVEL >= 1) { SEGGER_RTT_SetTerminal(0); printf(COLOR_RED 		"[AST:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); SEGGER_RTT_SetTerminal(1); }} while(0)
	#define LOG_ERR(...)    do { if(LOG_LEVEL >= 2) { SEGGER_RTT_SetTerminal(0); printf(COLOR_PINK 		"[ERR:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); SEGGER_RTT_SetTerminal(1); }} while(0)
	#define LOG_WAR(...)    do { if(LOG_LEVEL >= 3) { SEGGER_RTT_SetTerminal(0); printf(COLOR_YELLOW 	"[WAR:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); SEGGER_RTT_SetTerminal(1); }} while(0)
	#define LOG_INF(...)    do { if(LOG_LEVEL >= 4) { printf(__VA_ARGS__); }} while(0)
	#define LOG_DBG(...)    do { if(LOG_LEVEL >= 5) { printf(__VA_ARGS__); }} while(0)
	#define LOG_VBS(...)    do { if(LOG_LEVEL >= 6) { printf(__VA_ARGS__); }} while(0)
	
#elif LOG_BY_UART
	#include <stdio.h>
	#define LOG_INIT()		MX_USART1_UART_Init()
	#define LOG_AST(...)    do { if(LOG_LEVEL >= 1) { printf(COLOR_RED 		"[AST:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); }} while(0)
	#define LOG_ERR(...)    do { if(LOG_LEVEL >= 2) { printf(COLOR_PINK 	"[ERR:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); }} while(0)
	#define LOG_WAR(...)    do { if(LOG_LEVEL >= 3) { printf(COLOR_YELLOW 	"[WAR:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); }} while(0)
	#define LOG_INF(...)    do { if(LOG_LEVEL >= 4) { printf(__VA_ARGS__); }} while(0)
	#define LOG_DBG(...)    do { if(LOG_LEVEL >= 5) { printf(__VA_ARGS__); }} while(0)
	#define LOG_VBS(...)    do { if(LOG_LEVEL >= 6) { printf(__VA_ARGS__); }} while(0)
#endif
#else
	#define LOG_INIT()
	#define LOG_AST(...)
	#define LOG_ERR(...)
	#define LOG_WAR(...)
	#define LOG_INF(...)
	#define LOG_DBG(...)
	#define LOG_VBS(...)
#endif

#ifdef __cplusplus
}
#endif

#if LOG_TEST
	void log_test(void);
#endif

#endif // __DBGER_H__
