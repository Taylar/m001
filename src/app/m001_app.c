#include "general.h"


uint16_t	sysMode;
uint16_t	appMode;
uint16_t	phoneMode;
uint16_t	bleMode;



void rtcisr(void)
{
    SetRtcEvent();
    nrf_gpio_pin_toggle(BSP_LED_1);
}



void  M001_AppInit(void)
{
	sysMode   = SYS_POWEROFF_MODE;
	appMode   = APP_NORMAL_MODE;
	phoneMode = PHONE_NORMAL_MODE;
	bleMode   = BLE_SLEEP_MODE;

	SinglePortDriveInit();

	MovtAppInit();

	bspAccel.BspInterfaceEnable();
	bspAccel.Sleep();

	rtcApp.Init();
    rtcApp.Cb_SecIsrInit(rtcisr);


}


