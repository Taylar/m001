#ifndef		_OSAL_H_
#define		_OSAL_H




// osal task 
// rtc event
extern uint32_t rtcCntEvent;


// movt event
#define		MOVT_FORWARD_FINISH_EVENT		0x0001
#define		MOVT_RESVERSE_FINISH_EVENT		0x0002

extern uint32_t movtEvent;

// ble event 
#define		BLE_ADV_EVENT			0x0001
#define		BLE_CONNECT_EVENT		0x0002
#define		BLE_DATA_EVENT			0x0004


// key event
#define		KEY_3H_PUSH_EVENT			0X0001
#define		KEY_3H_RELEASE_EVENT		0X0002
#define		KEY_3H_3SHOLD_EVENT			0X0004
#define		KEY_3H_6SHOLD_EVENT			0X0008



void SetRtcEvent(void);
void SetMovtEvent(uint32_t event);


void OsalRun(void);

#endif