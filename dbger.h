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
 * @note	1. if LOG_BY_RTT, you can get the LOG in J-Link RTT Viewer;
 *			2. if LOG_BY_UART, you should enable the STDOUT in MDK-ARM -> RTE -> Compiler -> I/O -> STDOUT(user);
 *			3. if only LOG_BY_RTT or LOG_BY_UART, you can output the LOG by LOG_xxx() micro;
 *			4. if LOG_BY_RTT and LOG_BY_UART, you can output the LOG to RTT by LOG_xxx(), and output the LOG to UART by printf();
 *			5. if LOG_ENABLE is 0, you should disable STDOUT in MDK-ARM -> RTE -> Compiler -> I/O -> STDOUT.
 *
 * @author	shadowthreed@gmail.com
 * @date	20240714
 */

#ifndef __DBGER_H__
#define __DBGER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define LOG_ENABLE 	1
#define LOG_BY_RTT 	0
#define LOG_BY_UART 1
#define LOG_LEVEL 	4 		// the priority less than or queal to LOG_LEVEL will be output
#define LOG_COLOR_ENABLE 1

#if LOG_ENABLE
	#include <string.h>
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) 	// strrchr(str, ch): return the last position of ch in str, or NULL
#endif

#if LOG_ENABLE && LOG_COLOR_ENABLE // set LOG color
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

#if LOG_ENABLE && LOG_BY_UART
	#include <stdio.h>
	#include "RTE_Components.h"
	#ifndef RTE_Compiler_IO_STDOUT_User
		#error	must enable STDOUT in MDK-ARM -> RTE -> Compiler -> I/O -> STDOUT(user).
	#endif
#endif

#if LOG_ENABLE
#if LOG_BY_RTT
// SEGGER_RTT_SetTerminal(2); 	SEGGER_RTT_SetTerminal(3);  keep for user, eg:
// #define LOG_DAT(...)	do { if(LOG_LEVEL >= 1) { SEGGER_RTT_SetTerminal(2); SEGGER_RTT_printf(0, ##__VA_ARGS__); SEGGER_RTT_SetTerminal(1); }} while(0)
	#include "SEGGER_RTT.h"
	#define LOG_INIT()			SEGGER_RTT_Init()
	#define LOG_AST(...)    do { if(LOG_LEVEL >= 1) { SEGGER_RTT_SetTerminal(0); SEGGER_RTT_printf(0, COLOR_RED 		"[AST:%s:%d] ", __FILENAME__, __LINE__); SEGGER_RTT_printf(0, ##__VA_ARGS__); SEGGER_RTT_printf(0, COLOR_DEFAULT ""); SEGGER_RTT_SetTerminal(1); }} while(0)
	#define LOG_ERR(...)    do { if(LOG_LEVEL >= 2) { SEGGER_RTT_SetTerminal(0); SEGGER_RTT_printf(0, COLOR_PINK 		"[ERR:%s:%d] ", __FILENAME__, __LINE__); SEGGER_RTT_printf(0, ##__VA_ARGS__); SEGGER_RTT_printf(0, COLOR_DEFAULT ""); SEGGER_RTT_SetTerminal(1); }} while(0)
	#define LOG_WAR(...)    do { if(LOG_LEVEL >= 3) { SEGGER_RTT_SetTerminal(0); SEGGER_RTT_printf(0, COLOR_YELLOW 	"[WAR:%s:%d] ", __FILENAME__, __LINE__); SEGGER_RTT_printf(0, ##__VA_ARGS__); SEGGER_RTT_printf(0, COLOR_DEFAULT ""); SEGGER_RTT_SetTerminal(1); }} while(0)
	#define LOG_INF(...)    do { if(LOG_LEVEL >= 4) { SEGGER_RTT_printf(0, ##__VA_ARGS__); }} while(0)
	#define LOG_DBG(...)    do { if(LOG_LEVEL >= 5) { SEGGER_RTT_printf(0, ##__VA_ARGS__); }} while(0)
	#define LOG_VBS(...)    do { if(LOG_LEVEL >= 6) { SEGGER_RTT_printf(0, ##__VA_ARGS__); }} while(0)
#elif LOG_BY_UART
	#include <stdio.h>
	#define LOG_INIT()
	#define LOG_AST(...)    do { if(LOG_LEVEL >= 1) { printf(COLOR_RED 		"[AST:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); }} while(0)
	#define LOG_ERR(...)    do { if(LOG_LEVEL >= 2) { printf(COLOR_PINK 	"[ERR:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); }} while(0)
	#define LOG_WAR(...)    do { if(LOG_LEVEL >= 3) { printf(COLOR_YELLOW "[WAR:%s:%d] ", __FILENAME__, __LINE__); printf(__VA_ARGS__); printf(COLOR_DEFAULT ""); }} while(0)
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

#endif // __DBGER_H__