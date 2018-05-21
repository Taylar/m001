#ifndef			M001_APP_H_
#define			M001_APP_H_

typedef enum 
{
	SYS_POWEROFF_MODE = 0,
	SYS_WORK_MODE,
	SYS_FACTORY_MODE,
}sys_mode_e;


typedef enum
{
	APP_NORMAL_MODE = 0,
	APP_UPGRADE_MODE,
	APP_SLEEP_MODE,
	APP_DEEPSLEEP_MODE,
}app_mode_e;

typedef enum
{
	PHONE_NORMAL_MODE = 0,
	PHONE_TAKE_PIC_MODE,
	PHONE_UPGRADE_MODE,
	PHONE_TRANS_BIG_DATA_MODE,
}phone_mode_e;

typedef enum 
{
	BLE_SLEEP_MODE = 0,
	BLE_BROADCAST_MODE,
	BLE_CONNECT_MODE,
	BLE_PEER_MODE,
}ble_mode_e;

extern uint16_t	sysMode;
extern uint16_t	appMode;
extern uint16_t	phoneMode;
extern uint16_t	bleMode;


void  M001_AppInit(void);


#endif   // M001_APP_H_
