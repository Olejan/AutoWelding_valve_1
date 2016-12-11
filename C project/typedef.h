//#define _DEBUG_
#define _DEMO_VERSION_
#define WDT_ENABLE
#define LED_COMMON_CATHODE	/* ���������� ���������� � ����� ������� */


typedef signed char			i8;
typedef unsigned char		u8;
typedef signed short		i16;
typedef unsigned short		u16;
typedef signed int			i32;
typedef unsigned long		u32;
typedef signed long long	i64;
typedef unsigned long long	u64;
typedef u8					BOOL;

#define FALSE				0
#define TRUE				1

enum tag
{
	OFF,
	ON,
	pinTrans	= 0, // PORTD.0
	pinValve1	= 0, // PORTB.0
	pinValve2	= 1, // PORTB.1
	pinPedal1	= 6, // PORTB.6
	pinPedal2	= 7, // PORTB.7
	firstPrg	= 0, // ������ ���������
#ifdef _DEMO_VERSION_
	lastPrg		= 9,
#else
	lastPrg		= 9, // ��������� ��������
#endif
	programNumber = lastPrg + 1,
	TIME_FOR_MENU	= 30000, // ����� (��), ����� �������� ����� �������� � ������� ����
	TIME_FOR_SAVE	= 30000, // ����� ������ ��� ���������� �������������� ���������
	TIME_PER_UNIT	= 10, // ����� ������� ��������� ����������: ������, ��������
	SCAN_KEY_TIME	= 20, // ����� ������������ ������, ��
	TIME_TO_WRITE	= 30, // �����, ����� �������� ����� ����� �������� ���-�� �� �����, ��
};

enum tagHL
{
	pinPrePressingHL	= 7,
	pinPressingHL		= 6,
	pinHeatingHL		= 5,
	pinForgingHL		= 4,
	pinPauseHL			= 3,
	pinSimpleHL			= 2,
	pinAutoHL			= 1,
	pinCurrentHL		= 0,
#ifdef LED_COMMON_CATHODE
	ALL_LEDS_OFF		= 0xff,
#else
	ALL_LEDS_OFF		= 0,
#endif
};

#define PINPEDAL1	PINB	/* ��� ������ ���������������� ������ */
#define PINPEDAL2	PINB	/* ��� ������ */
#define DDRPEDAL1	DDRB	/* direct ���� ������ ���������������� ������ */
#define DDRPEDAL2	DDRB	/* direct ���� ������ */

#define DDRBUTTONS	DDRB	/* */
#define PINBUTTONS	PINB
#define PORTBUTTONS	PORTB

#define DDRTRANS	DDRD
#define PORTTRANS	PORTD	/* ���� �������������� */
#define DDRVALVE1	DDRB	/* direct ���� ������� ���������������� ������ */
#define DDRVALVE2	DDRB	/* direct ���� ������� */
#define PORTVALVE1	PORTB	/* ���� ������� ���������������� ������*/
#define PORTVALVE2	PORTB	/* ���� ������� */
#define DDRLED		DDRC
#define PORTLED		PORTC	/* ���� ����������� */

enum tagParams
{
	paramPrePressing	= 0,// ��������������� ������ !!! 1-� �������� ������ ���� ����� 0 !!!
	paramPressing,			// ������
	paramHeating,			// ������
	paramForging,			// ��������
	paramModulation,		// ����������� ���������
	paramCurrent,			// �������� ����
	paramMode,				// ����� ������
	paramPause,				// ����� ����� ������� ������
	paramNum,				// ���������� ���������� !!! ������ ������ ����� ����� ���������� ��������� !!!
	cmnprmStartPrg,			// ��������� ���������

	minPrePressing	= 1,
	minPressing		= 1,
	minHeating		= 1,
	minForging		= 1,
	minModulation	= 0,
	minCurrent		= 0,
	MIN_PAUSE		= 1,

	maxPrePressing	= 250,
	maxPressing		= 99,
	maxHeating		= 200,
	maxForging		= 250,
	maxModulation	= 9,
	maxCurrent		= 9,
	MAX_PAUSE		= 250,

	defPrePressing	= 30,
	defPressing		= 3,
	defHeating		= 50,
	defForging		= 50,
	defModulation	= 5,
	defCurrent		= 5,
	DEF_PAUSE		= 7,
};
//!!// addr... � param... ��������������, ������ welding.c GetValue()
enum tagEEPROMAddr
{
	addrEmpty		= 0,
	addrPrePressing	= 1, // ��������������� ������
	addrPressing, // ������
	addrHeating, // ������
	addrForging, // ��������
	addrModulation, // ����������� ���������
	addrCurrent, // �������� ����
	addrMode, // ������� �����
	addrPause, // ����� ����� ������� ������
	addrStartPrg	= 1 + paramNum * programNumber,	// ����� ������� ��������� (������������� �� ����� �����������)
};

enum tagLCD
{
	lcdstr1	= 0, // first string
	lcdstr2, // second string
	lcdstr3, // third string
	lcdstr4, // fourth string
};

enum tagScreens
{
	scrViewParams,	// ����������� ���������� ��������
	scrPrePressing,	// ��������������� ������
	scrPressing,	// ������� ������
	scrHeating,		// ������
	scrForging,		// ��������
	scrWeldingCompleted,	// ���� ������ ��������
	scrPause,		// �����
};

enum tagButtons
{
	keyEmpty	= 0,
	keyUp,
	keyDown,
	keyLeft,
	keyRight,
};

enum tagDimentionLCD
{
	numOfStrings	= 2,
	numOfColumn		= 16,
};

typedef struct
{
	u16 time40us	:1;
	u16 dirty		:1; // ������ � ������� LCD ��������
	u16 halfPeriod	:1; // ���� ������� ����������� �������� ���������� �� int0
	u16 heating		:1; // flag_nagrev
	u16 scanKey		:1; // ����� ����������� ������
	u16 currentIsEnable	:1; // ����� ���� ������/������ (1/0)
}tagFlags;

enum tagIds
{
	idInfo			= 0,
	idPrograms,
	idChoosePrgStngs,
	idChooseCmnStngs,
	idChooseMode,
	idChoosePause,
	idChooseStartPrg,
	idChoosePrePressing,
	idChoosePressing,
	idChooseHeating,
	idChooseForging,
	idChooseModulation,
	idChooseCurrent,
	idEditPrePressing,
	idEditPressing,
	idEditHeating,
	idEditForging,
	idEditModulation,
	idEditCurrent,
	idEditStartPrg,
	idEditMode,
	idEditPause,
};

enum tagMode
{
	AUTO_MODE	= 0,
	SIMPLE_MODE,
	LAST_MODE = SIMPLE_MODE,
	
	WELD_IS_RUNNIG,
	SIMPLE_WELD_HAS_DONE,
	WELD_HAS_BROKEN,
};

typedef struct PROGMEM
{
	const u8 id;	// id ����
	const u8* str1;	// 1-� ������
	const u8* str2; // 2-� ������
	void (*pf)();	// ������� ������� ����
} MenuItem;

typedef struct
{
	void (*set)(u8);
	u8 (*get)();
}CURPRG, CURMODE;

enum tagWDT
{
	wdt_15ms	= 0,
	wdt_30ms	= 1,
	wdt_60ms	= 2,
	wdt_120ms	= 3,
	wdt_250ms	= 4,
	wdt_500ms	= 5,
	wdt_1s		= 6,
	wdt_2s		= 7,
};