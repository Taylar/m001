#ifndef		GENERAL_H_
#define		GENERAL_H_

#include <stdint.h>
#include <string.h>



// bsp
#include "boards.h"

// mcu driver
#include "nrf_drv_spi.h"
#include "nrf_drv_gpiote.h"
// mcu lib
#include "app_timer.h"
#include "app_button.h"

// user driver
#include "movt.h"
#include "rtc.h"
#include "singleportdrive.h"
#include "accel_sensor.h"
#include "key.h"

// module
#include "movt_app.h"
#include "rtc_app.h"
#include "singleportdrive_app.h"

// osal
#include "osal.h"

// app
#include "m001_app.h"
#include "key_app.h"
#include "ble_app.h"
#include "key_app.h"
#include "actionrecongnition.h"
#include "accel_app.h"
#include "daily_sport.h"
#include "lis3dh.h"
#include "display.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"



#define 	SUPPORT_UART_PRINTF 



#define		SYS_APP_HANDLE_NUM  1

// ************************version**********************************
#define		FW_VERSION			0X0001
#define		BLE_PRO_VER			0X0001


extern uint16_t	sysAppHandle;

extern char m001BraodcastName[16];

typedef enum
{
	SYS_APP_HANDLE_DAILY		= 0,
} sys_app_handle_t;


#endif	// GENERAL_H_
