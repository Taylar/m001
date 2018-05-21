#include "am_mcu_apollo.h"
#include "usertype.h"
#include "interrupt.h"
#include "key.h"


// key status
#define     KEY_STANDBY             0X0000
#define     KEY_DELAY               0x0001
#define     KEY_HOLE                0x0002

// hold key time
#define     HOLD_3S                 32*3
#define     HOLD_6S                 32*6

// touch
#define		KEY_S0_TOUCH			0X0001
#define		KEY_S1_TOUCH			0X0002
#define		KEY_S2_TOUCH			0X0004
#define		KEY_S3_TOUCH			0X0008
#define		KEY_S4_TOUCH			0X0010

// key pin
#ifndef		BSP_KEY_PIN
#define		BSP_KEY_PIN

#define		KEY_S0_PIN					29
#define		KEY_S1_PIN					28
#define		KEY_S2_PIN					30
#define		KEY_S3_PIN					31
#define		KEY_S4_PIN					32

#endif





// pin press
#define		KEY_PRESSING			0





static unsigned short   keyDelayFlag;      //0x0000: idle 	0x0001: keydelay     0x0002:keyhold
static unsigned short   validKeyNum;      //S0:0	S1:1	S2:2
static unsigned short   holdKeyCnt;



// callback key function
bsp_key_define_s		bspDefineKey[KEY_MAX_NUM];

// set key timer 31.25ms
void BspKeyTimerInit(void)
{
	BspTimerInitCom(1, AM_HAL_CTIMER_TIMERB, AM_HAL_CTIMER_INT_TIMERB1, 
					(AM_HAL_CTIMER_FN_REPEAT | AM_HAL_CTIMER_INT_ENABLE | AM_HAL_CTIMER_XT_256HZ), 
					(unsigned int)(7));	
}


void BspKeyTimerStart(void)
{
	am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERB1);
	am_hal_ctimer_start(1, AM_HAL_CTIMER_TIMERB);	
}

void BspKeyTimerStop(void)
{
	am_hal_ctimer_stop(1, AM_HAL_CTIMER_TIMERB);	
	am_hal_ctimer_int_disable(AM_HAL_CTIMER_INT_TIMERB1);
}

void BspKeyTimerReset(void)
{
	am_hal_ctimer_clear(1, AM_HAL_CTIMER_TIMERB);
}


void BspKeyInit(void)
{
	unsigned char	i;
	am_hal_gpio_pin_config(KEY_S0_PIN, AM_HAL_PIN_INPUT | AM_HAL_GPIO_PULL24K);
	am_hal_gpio_int_set(AM_HAL_GPIO_BIT(KEY_S0_PIN));
	am_hal_gpio_int_polarity_bit_set(KEY_S0_PIN,AM_HAL_GPIO_FALLING);
	am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(KEY_S0_PIN));
	am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(KEY_S0_PIN));

	am_hal_gpio_pin_config(KEY_S1_PIN, AM_HAL_PIN_INPUT | AM_HAL_GPIO_PULL24K);
	am_hal_gpio_int_set(AM_HAL_GPIO_BIT(KEY_S1_PIN));
	am_hal_gpio_int_polarity_bit_set(KEY_S1_PIN,AM_HAL_GPIO_FALLING);
	am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(KEY_S1_PIN));
	am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(KEY_S1_PIN));

	am_hal_gpio_pin_config(KEY_S2_PIN, AM_HAL_PIN_INPUT | AM_HAL_GPIO_PULL24K);
	am_hal_gpio_int_set(AM_HAL_GPIO_BIT(KEY_S2_PIN));
	am_hal_gpio_int_polarity_bit_set(KEY_S2_PIN,AM_HAL_GPIO_FALLING);
	am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(KEY_S2_PIN));
	am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(KEY_S2_PIN));

	am_hal_gpio_pin_config(KEY_S3_PIN, AM_HAL_PIN_INPUT | AM_HAL_GPIO_PULL24K);
	am_hal_gpio_int_set(AM_HAL_GPIO_BIT(KEY_S3_PIN));
	am_hal_gpio_int_polarity_bit_set(KEY_S3_PIN,AM_HAL_GPIO_FALLING);
	am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(KEY_S3_PIN));
	am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(KEY_S3_PIN));

	am_hal_gpio_pin_config(KEY_S4_PIN, AM_HAL_PIN_INPUT | AM_HAL_GPIO_PULL24K);
	am_hal_gpio_int_set(AM_HAL_GPIO_BIT(KEY_S4_PIN));
	am_hal_gpio_int_polarity_bit_set(KEY_S4_PIN,AM_HAL_GPIO_FALLING);
	am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(KEY_S4_PIN));
	am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(KEY_S4_PIN));

	am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_CTIMER, AM_HAL_INTERRUPT_PRIORITY(1));	//the timer should set high




	BspKeyTimerInit();

	keyDelayFlag			= 0;
	validKeyNum				= 0;
	holdKeyCnt				= 0;

	bspDefineKey[KEY_S0].keyPin	= KEY_S0_PIN;
	bspDefineKey[KEY_S1].keyPin	= KEY_S1_PIN;
	bspDefineKey[KEY_S2].keyPin	= KEY_S2_PIN;
	bspDefineKey[KEY_S3].keyPin	= KEY_S3_PIN;
	bspDefineKey[KEY_S4].keyPin	= KEY_S4_PIN;

	for(i = 0; i < KEY_MAX_NUM; i++)
	{
		bspDefineKey[i].ShortKey	= null_isr;
		bspDefineKey[i].Hold3sKey	= null_isr;
		bspDefineKey[i].Hold6sKey	= null_isr;
	}
}

void BspKeyTimerIsr(void)
{
	if(keyDelayFlag == KEY_HOLE)
	{
		if(am_hal_gpio_input_bit_read(bspDefineKey[validKeyNum].keyPin) == KEY_PRESSING)
		{
			holdKeyCnt++;
			if(holdKeyCnt == HOLD_3S)	//3s keyhold function
			{
				bspDefineKey[validKeyNum].Hold3sKey();
			}
			if(holdKeyCnt == HOLD_6S)	//6s keyhold function
			{
				BspKeyTimerStop();
				BspKeyTimerReset();
				keyDelayFlag 	= KEY_STANDBY;
				bspDefineKey[validKeyNum].Hold6sKey();
			}
		}
		else
		{
			// short key fuction
			BspKeyTimerStop();
			BspKeyTimerReset();
			keyDelayFlag 	= KEY_STANDBY;
			if(holdKeyCnt < HOLD_3S)
				bspDefineKey[validKeyNum].ShortKey();
		}
	}

	if(keyDelayFlag == KEY_DELAY)
	{
		holdKeyCnt 		= 1;
		keyDelayFlag 	= KEY_HOLE;
	}
}




void BspKeyS0_Isr(void)
{
	if(keyDelayFlag == KEY_STANDBY)
	{
		keyDelayFlag 	= KEY_DELAY;
		validKeyNum		= KEY_S0;
		BspKeyTimerStart();
	}
}


void BspKeyS1_Isr(void)
{
	if(keyDelayFlag == KEY_STANDBY)
	{
		keyDelayFlag 	= KEY_DELAY;
		validKeyNum		= KEY_S1;
		BspKeyTimerStart();
	}
}


void BspKeyS2_Isr(void)
{
	if(keyDelayFlag == KEY_STANDBY)
	{
		keyDelayFlag 	= KEY_DELAY;
		validKeyNum		= KEY_S2;
		BspKeyTimerStart();
	}
}

void BspKeyS3_Isr(void)
{
	if(keyDelayFlag == KEY_STANDBY)
	{
		keyDelayFlag 	= KEY_DELAY;
		validKeyNum		= KEY_S3;
		BspKeyTimerStart();
	}
}

void BspKeyS4_Isr(void)
{
	if(keyDelayFlag == KEY_STANDBY)
	{
		keyDelayFlag 	= KEY_DELAY;
		validKeyNum		= KEY_S4;
		BspKeyTimerStart();
	}
}

uint8_t ReadState_S0(void)
{
	return am_hal_gpio_input_bit_read(KEY_S0_PIN);
}


uint8_t ReadState_S1(void)
{
	return am_hal_gpio_input_bit_read(KEY_S1_PIN);
}


uint8_t ReadState_S2(void)
{
	return am_hal_gpio_input_bit_read(KEY_S2_PIN);
}

uint8_t ReadState_S3(void)
{
	return am_hal_gpio_input_bit_read(KEY_S3_PIN);
}


uint8_t ReadState_S4(void)
{
	return am_hal_gpio_input_bit_read(KEY_S4_PIN);
}
