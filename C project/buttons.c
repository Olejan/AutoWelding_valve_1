/** \file buttons.c
 * \brief ������ ��������� ������
 * �������� ������� ������ ��������� ������
 * \par
 * \author ARV
 * Copyright 2008 � ARV. All rights reserved. </b>
 * \par
 * ��� ������ ������� ���������:
 * 	-# WinAVR-20080411 ��� ����� ����� ������
 *
 */

#include "IDE.h"
#include "buttons.h"

/** ������� ����� ������� ������
 * @return - ���������� ����, ��������������� ������� ������� ��� 0, ���� �� ������ �� �����
 * \note ��� ������� ������ ���� ����������� ��� ���������� ���������� ���������. ��� �����
 * ���� ������������ �������, ���� ��������� ����� ����� � �.�. ������� ��� �� ���������� ��������
 * � ���� ������� ���� �� ������!
 */
static u8 get_key_code(void)
{
	u8 buf;
	buf = ~PINBUTTONS;
	buf >>= 2;
	/*if (!(PINB & (1 << 0)))
		buf |= 1 << 3;*/

	switch(buf)
	{
		case 1: buf = keyUp; break;
		case 2: buf = keyLeft; break;
		case 4: buf = keyRight; break;
		case 8: buf = keyDown; break;
		//case 0x0f: reset(); break;  // LEFT + DOWN + RIGHT + UP
		default: buf = keyEmpty; break;
	}
	return buf;
}

/** ������� ��������� ������ �������� �����
 *
 * @param key - ��� ������, ��������� ������� ������ ����������������
 * @param delay10ms - ������������ ��������� � �������� �����������
 * @return - ��� ���������� ������ ��� 0, ���� ������ ��������� �� ��������� ��������
 */
static u8 wait_key(u8 key, u16 delay10ms)
{
	delay10ms *= 10;
	for(; delay10ms > 0; delay10ms--)
	{
		_delay_ms(1);
		if (key != get_key_code())
			return keyEmpty;
		wdt_feed();
	}
	return key;
}

/** ��������� ���� ������� ������ � ��������� �����������
 * ���� ������ � ���������� ���������� ������,
 * �� ������� ������� �������� FIRST_RPT �������� �����������, � �����
 * ���������� ��������� ����� ������ RPT_DELAY �������� �����������
 * @return - ������������ ��������: ����, ��������������� ������� �������
 */
u8 get_key(void)
{
//return keyLeft;
	static u8 oldkey = keyEmpty;
	static u8 first = 1;
	static u8 repeat = 0;
	u8 key, delay;

	key = wait_key(get_key_code(), 1);		// ���� 10 �� ��� ���������� ��������
	if (key)
	{								// ���� ���� �������
		if (oldkey == keyEmpty)
		{						// ���� ���������� ��� ������� - ��� ����� ����������
			oldkey = key;					// ���������� ���������� � �� �����
			repeat = 0;
		}
		else
		{							// ���� ���������� �� ���� - ��� ����������
			if (first)
			{						// ������ ��� ����� �������� ������ ��������
				delay = FIRST_RPT;
				first = 0;					// ����� ��������� ��� ���������� �����
				repeat = 1;
			}
			else
			{
				if (repeat++ >= 30)
				{
					repeat = 30;
					delay = FAST_RPT_DELAY;		// ����� 30 �������� ��������� ��������
				}					
				else
					delay = RPT_DELAY;			// ������ �� ������ ������ � ������ ���������
			}
			key = wait_key(oldkey, delay);	// ���� ��������� ������ �����
			if (key == keyUp || key == keyDown) // ���������� ������ ����� � ���� �� �����)
				return keyEmpty;
		}
	}
	if (!key)
	{								// ���� � ����� ������ ����� ����
		first = 1;							// ��� �������� ������
		oldkey = 0;
	}
	return key;								// ����������� �������������� ���
}
