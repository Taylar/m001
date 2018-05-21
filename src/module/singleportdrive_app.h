#ifndef			SINGLEPORTDRIVE_APP_H
#define			SINGLEPORTDRIVE_APP_H


#define     SINGLEPORTDRIVE_PERIOD_CLOCK_TIME_MS       10


#define 	LED_PORT_ACTIVE_STATE			0
#define 	MOTO_PORT_ACTIVE_STATE			1

#ifndef		PORT_TYPE_T
#define		PORT_TYPE_T
typedef enum
{
	RED_LED	= 0,
	GREEN_LED,
	MOTO,
	PORT_MAX,
} port_type_t;
#endif



typedef struct 
{
	uint16_t		highTime;
	uint16_t		lowTime;
	uint16_t		driveTimes;
	uint16_t		portType;
	uint8_t			state;
}single_port_set_para_s;


typedef struct
{
	func *		Init;
	func *		MotoPeriodProcess;
	func *		GreenLedPeriodProcess;
	func *		RedLedPeriodProcess;
	void		(*FinishCbInit)(void (*Cb)(uint16_t portType));
	void		(*PortSet)(single_port_set_para_s *setPara);
	void		(*PortOn)(uint16_t portType);
	void		(*PortOff)(uint16_t portType);
    uint16_t    (*ReadState)(void);
}single_port_s;

extern const single_port_s singlePort;



void SetSinglePort(single_port_set_para_s *setPara);

void SinglePortDriveInit(void);

void SinglePortFinishCbInit(void (*Cb)(uint16_t portType));

void SinglePortPeriodProcessMoto(void);

void SinglePortPeriodProcessGreenLed(void);

void SinglePortPeriodProcessRedLed(void);

void SinglePortOn(uint16_t portType);

void SinglePortOff(uint16_t portType);

uint16_t ReadSinglePortState(void);
#endif			// SINGLEPORTDRIVE_APP_H
