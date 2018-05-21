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





void SetRtcEvent(void);

void SetMovtEvent(uint32_t event);

void SetBleEvent(uint32_t event);

void SetKeyEvent(uint32_t event);


void OsalRun(void);

#endif
