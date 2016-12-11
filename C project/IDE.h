#include "typedef.h"
#include <avr/io.h>      // ���������� ����� ��� ������ �����-������
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
//#include <avr/eeprom.h>
#include <stdio.h>       // ����������� ������ �����-������
//#include <stdbool.h>
#include <util/delay.h>	 // ���������� ��������

#include "InlineFunctions.h"


//#define _ENGLISH_VERSION_


#ifdef WDT_ENABLE
extern void SetWdtTimeLabel();
extern void ResetWdtTimeLabel();
extern BOOL CheckWdtTime(u32 time); // Check, Reset And Note WdtTime
#endif
extern void wdt_start(u8 level);
extern void wdt_stop();
extern void wdt_feed();
extern void ResetProc();
