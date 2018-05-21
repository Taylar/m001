#include "usertype.h"
#include "key.h"
#include "sys_variable.h"
#include "key_app.h"


func *ShortKeySysModeS0[SYS_APP_HANDLE_NUM];
func *ShortKeySysModeS1[SYS_APP_HANDLE_NUM];
func *ShortKeySysModeS2[SYS_APP_HANDLE_NUM];
func *ShortKeySysModeS3[SYS_APP_HANDLE_NUM];
func *ShortKeySysModeS4[SYS_APP_HANDLE_NUM];

func *Hold3sKeySysModeS0[SYS_APP_HANDLE_NUM];
func *Hold3sKeySysModeS1[SYS_APP_HANDLE_NUM];
func *Hold3sKeySysModeS2[SYS_APP_HANDLE_NUM];
func *Hold3sKeySysModeS3[SYS_APP_HANDLE_NUM];
func *Hold3sKeySysModeS4[SYS_APP_HANDLE_NUM];

func *Hold6sKeySysModeS0[SYS_APP_HANDLE_NUM];
func *Hold6sKeySysModeS1[SYS_APP_HANDLE_NUM];
func *Hold6sKeySysModeS2[SYS_APP_HANDLE_NUM];
func *Hold6sKeySysModeS3[SYS_APP_HANDLE_NUM];
func *Hold6sKeySysModeS4[SYS_APP_HANDLE_NUM];





void ShortKeyAppS0(void)
{
	ShortKeySysModeS0[sysAppHandle]();
}

void ShortKeyAppS1(void)
{
	ShortKeySysModeS1[sysAppHandle]();
}

void ShortKeyAppS2(void)
{
	ShortKeySysModeS2[sysAppHandle]();
}

void ShortKeyAppS3(void)
{
	ShortKeySysModeS3[sysAppHandle]();
}

void ShortKeyAppS4(void)
{
	ShortKeySysModeS4[sysAppHandle]();
}


void Hold3sKeyAppS0(void)
{
	Hold3sKeySysModeS0[sysAppHandle]();
}

void Hold3sKeyAppS1(void)
{
	Hold3sKeySysModeS1[sysAppHandle]();
}

void Hold3sKeyAppS2(void)
{
	Hold3sKeySysModeS2[sysAppHandle]();
}

void Hold3sKeyAppS3(void)
{
	Hold3sKeySysModeS3[sysAppHandle]();
}

void Hold3sKeyAppS4(void)
{
	Hold3sKeySysModeS4[sysAppHandle]();
}

void Hold6sKeyAppS0(void)
{
	Hold6sKeySysModeS0[sysAppHandle]();
}

void Hold6sKeyAppS1(void)
{
	Hold6sKeySysModeS1[sysAppHandle]();
}

void Hold6sKeyAppS2(void)
{
	Hold6sKeySysModeS2[sysAppHandle]();
}

void Hold6sKeyAppS3(void)
{
	Hold6sKeySysModeS3[sysAppHandle]();
}

void Hold6sKeyAppS4(void)
{
	Hold6sKeySysModeS4[sysAppHandle]();
}

void KeyAppInit(void)
{
	uint8_t	i;
	bspKey.Init();

	bspKey.key[KEY_S0].ShortKey		= ShortKeyAppS0;
	bspKey.key[KEY_S1].ShortKey		= ShortKeyAppS1;
	bspKey.key[KEY_S2].ShortKey		= ShortKeyAppS2;
	bspKey.key[KEY_S3].ShortKey		= ShortKeyAppS3;
	bspKey.key[KEY_S4].ShortKey		= ShortKeyAppS4;

	bspKey.key[KEY_S0].Hold3sKey	= Hold3sKeyAppS0;
	bspKey.key[KEY_S1].Hold3sKey	= Hold3sKeyAppS1;
	bspKey.key[KEY_S2].Hold3sKey	= Hold3sKeyAppS2;
	bspKey.key[KEY_S3].Hold3sKey	= Hold3sKeyAppS3;
	bspKey.key[KEY_S4].Hold3sKey	= Hold3sKeyAppS4;

	bspKey.key[KEY_S0].Hold6sKey	= Hold6sKeyAppS0;
	bspKey.key[KEY_S1].Hold6sKey	= Hold6sKeyAppS1;
	bspKey.key[KEY_S2].Hold6sKey	= Hold6sKeyAppS2;
	bspKey.key[KEY_S3].Hold6sKey	= Hold6sKeyAppS3;
	bspKey.key[KEY_S4].Hold6sKey	= Hold6sKeyAppS4;

	for(i = 0; i < SYS_APP_HANDLE_NUM; i++)
	{
		ShortKeySysModeS0[i]	= NullFunc;
		ShortKeySysModeS1[i]	= NullFunc;
		ShortKeySysModeS2[i]	= NullFunc;
		ShortKeySysModeS3[i]	= NullFunc;
		ShortKeySysModeS4[i]	= NullFunc;

		Hold3sKeySysModeS0[i]	= NullFunc;
		Hold3sKeySysModeS1[i]	= NullFunc;
		Hold3sKeySysModeS2[i]	= NullFunc;
		Hold3sKeySysModeS3[i]	= NullFunc;
		Hold3sKeySysModeS4[i]	= NullFunc;
		
		Hold6sKeySysModeS0[i]	= NullFunc;
		Hold6sKeySysModeS1[i]	= NullFunc;
		Hold6sKeySysModeS2[i]	= NullFunc;
		Hold6sKeySysModeS3[i]	= NullFunc;
		Hold6sKeySysModeS4[i]	= NullFunc;
	}
}


void ShortKeyIsrInit_S0(uint16_t appHandle, func *Cb)
{
	ShortKeySysModeS0[appHandle] = Cb;
}

void ShortKeyIsrInit_S1(uint16_t appHandle, func *Cb)
{
	ShortKeySysModeS1[appHandle] = Cb;
}

void ShortKeyIsrInit_S2(uint16_t appHandle, func *Cb)
{
	ShortKeySysModeS2[appHandle] = Cb;
}

void ShortKeyIsrInit_S3(uint16_t appHandle, func *Cb)
{
	ShortKeySysModeS3[appHandle] = Cb;
}

void ShortKeyIsrInit_S4(uint16_t appHandle, func *Cb)
{
	ShortKeySysModeS4[appHandle] = Cb;
}


void HoldKey3sIsrInit_S0(uint16_t appHandle, func *Cb)
{
	Hold3sKeySysModeS0[appHandle] = Cb;
}

void HoldKey3sIsrInit_S1(uint16_t appHandle, func *Cb)
{
	Hold3sKeySysModeS1[appHandle] = Cb;
}

void HoldKey3sIsrInit_S2(uint16_t appHandle, func *Cb)
{
	Hold3sKeySysModeS2[appHandle] = Cb;
}

void HoldKey3sIsrInit_S3(uint16_t appHandle, func *Cb)
{
	Hold3sKeySysModeS3[appHandle] = Cb;
}

void HoldKey3sIsrInit_S4(uint16_t appHandle, func *Cb)
{
	Hold3sKeySysModeS4[appHandle] = Cb;
}

void HoldKey6sIsrInit_S0(uint16_t appHandle, func *Cb)
{
	Hold6sKeySysModeS0[appHandle] = Cb;
}

void HoldKey6sIsrInit_S1(uint16_t appHandle, func *Cb)
{
	Hold6sKeySysModeS1[appHandle] = Cb;
}

void HoldKey6sIsrInit_S2(uint16_t appHandle, func *Cb)
{
	Hold6sKeySysModeS2[appHandle] = Cb;
}

void HoldKey6sIsrInit_S3(uint16_t appHandle, func *Cb)
{
	Hold6sKeySysModeS3[appHandle] = Cb;
}

void HoldKey6sIsrInit_S4(uint16_t appHandle, func *Cb)
{
	Hold6sKeySysModeS4[appHandle] = Cb;
}


uint8_t	ReadKey_S0(void)
{
	return bspKey.ReadState_S0();
}

uint8_t	ReadKey_S1(void)
{
	return bspKey.ReadState_S1();
}

uint8_t	ReadKey_S2(void)
{
	return bspKey.ReadState_S2();
}

uint8_t	ReadKey_S3(void)
{
	return bspKey.ReadState_S3();
}

uint8_t	ReadKey_S4(void)
{
	return bspKey.ReadState_S4();
}
