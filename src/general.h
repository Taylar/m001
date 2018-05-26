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



#define 	SUPPORT_UART_PRINTF 



#define		SYS_APP_HANDLE_NUM  1


extern uint16_t	sysAppHandle;






#endif	// GENERAL_H_
