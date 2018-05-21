#include "am_mcu_apollo.h"
#include "usertype.h"
#include "interrupt.h"
#include "accel_sensor.h"


//kx022 pin
#define			KX022_CS_PIN			11

// *************************************************
#define		Kx022_CS_Enable()				nrf_gpio_pin_write(KX022_CS_PIN, 0)
#define		Kx022_CS_Disable()				nrf_gpio_pin_write(KX022_CS_PIN, 1)



// register macro
#define XHPL			(0x00)		// R
#define XHPH			(0x01)		// R
#define YHPL			(0x02)		// R
#define YHPH			(0x03)		// R
#define ZHPL			(0x04)		// R
#define ZHPH			(0x05)		// R
#define XOUTL			(0x06)		// R
#define XOUTH			(0x07)		// R
#define YOUTL			(0x08)		// R
#define YOUTH			(0x09)		// R
#define ZOUTL			(0x0A)		// R
#define ZOUTH			(0x0B)		// R
#define COTR			(0x0C)		// R

#define WHO_AM_I		(0x0F)		// RW
#define TSCP			(0x10)		// R
#define TSPP			(0x11)		// R
#define INS1			(0x12)		// R
#define INS2			(0x13)		// R
#define INS3			(0x14)		// R
#define STAT			(0x15)		// R

#define INT_REL			(0x17)		// R
#define CNTL1			(0x18)		// RW
#define CNTL2			(0x19)		// RW
#define CNTL3			(0x1A)		// RW
#define ODCNTL			(0x1B)		// RW
#define INC1			(0x1C)		// RW
#define INC2			(0x1D)		// RW
#define INC3			(0x1E)		// RW
#define INC4			(0x1F)		// RW
#define INC5			(0x20)		// RW
#define INC6			(0x21)		// RW
#define TILT_TIMER		(0x22)		// RW
#define WUFC			(0x23)		// RW
#define TDTRC			(0x24)		// RW
#define TDTC			(0x25)		// RW
#define TTH				(0x26)		// RW
#define TTL				(0x27)		// RW
#define FTD				(0x28)		// RW
#define STD				(0x29)		// RW
#define TLT				(0x2A)		// RW
#define TWS				(0x2B)		// RW

#define ATH				(0x30)		// RW
#define TILT_ANGLE_LL	(0x32)		// RW
#define TILT_ANGLE_HL	(0x33)		// RW
#define HYST_SET		(0x34)		// RW
#define LP_CNTL			(0x35)		// RW

#define BUF_CNTL1		(0x3A)		// RW
#define BUF_CNTL2		(0x3B)		// RW
#define BUF_STATUS_1	(0x3C)		// R
#define BUF_STATUS_2	(0x3D)		// R
#define BUF_CLEAR		(0x3E)		// W
#define BUF_READ		(0x3F)		// R
#define SELF_TEST		(0x60)		// RW


static am_hal_iom_config_t SPI_0_Config = {
    .ui32InterfaceMode = AM_HAL_IOM_SPIMODE,
    .ui32ClockFrequency = AM_HAL_IOM_8MHZ,
    .bSPHA = 0,
    .bSPOL = 0,
    .ui8WriteThreshold = 0,
    .ui8ReadThreshold = 120,
};


void BspSpi_0_Init(void)
{
    am_hal_gpio_pin_config(5,AM_HAL_PIN_5_M0SCK);
    am_hal_gpio_pin_config(6,AM_HAL_PIN_6_M0MISO);
    am_hal_gpio_pin_config(7,AM_HAL_PIN_7_M0MOSI);
    am_hal_gpio_pin_config(KX022_CS_PIN,AM_HAL_PIN_OUTPUT);
    nrf_gpio_pin_write(KX022_CS_PIN, 1);

    am_hal_iom_config(0, &SPI_0_Config);

    am_hal_iom_enable(0);
}


static void SPI_WriteData(uint8_t regAddr, uint8_t* data_Point, uint16_t length )
{
	Kx022_CS_Enable();
	am_hal_iom_spi_write(0, 0, (uint32_t*)data_Point, length, AM_HAL_IOM_OFFSET(regAddr));
	am_hal_iom_poll_complete(0);
	Kx022_CS_Disable();
}


static void SPI_ReadData(uint8_t regAddr, uint8_t* data_Point, uint16_t length)
{
	regAddr |= 0x80;
	Kx022_CS_Enable();
	am_hal_iom_spi_read(0, 0, (uint32_t*)data_Point, length, AM_HAL_IOM_OFFSET(regAddr));
	Kx022_CS_Disable();
}

//disable hw SPI 1 of ambiq 
void BspSpi_0_Disable(void)
{
    am_hal_iom_disable(0);
    nrf_gpio_cfg_output(5);
    nrf_gpio_cfg_output(6);
    nrf_gpio_cfg_output(7);
    nrf_gpio_cfg_output(KX022_CS_PIN);
    nrf_gpio_pin_write(KX022_CS_PIN, 1);
    am_hal_gpio_out_bit_clear(5);
    am_hal_gpio_out_bit_clear(6);
    am_hal_gpio_out_bit_clear(7);
}


void BspKx022SetRegister(uint8_t regAddr, uint8_t data)
{
	SPI_WriteData(regAddr, &data, 1);
}



void BspKx022Set_25HzSample_Buf(void)
{
	BspKx022SetRegister(CNTL1, 	0x00);
	BspKx022SetRegister(ODCNTL, 	0x81);
	BspKx022SetRegister(LP_CNTL,	0x2b);
	BspKx022SetRegister(BUF_CNTL2, 0x81);
	BspKx022SetRegister(BUF_CLEAR, 0x00);
	BspKx022SetRegister(INC1, 		0x10);
	BspKx022SetRegister(INC2, 		0x3f);
	BspKx022SetRegister(CNTL1, 	0x80);
}

void BspKx022Set_100HzSample_Buf(void)
{
	BspKx022SetRegister(CNTL1, 	0x00);
	BspKx022SetRegister(ODCNTL, 	0x83);
	BspKx022SetRegister(LP_CNTL,	0x2b);
	BspKx022SetRegister(BUF_CNTL2, 0x81);
	BspKx022SetRegister(BUF_CLEAR, 0x00);
	BspKx022SetRegister(INC1, 		0x10);
	BspKx022SetRegister(INC2, 		0x3f);
	BspKx022SetRegister(CNTL1, 	0x80);
}




void BspKx022_Readbuf(uint16_t* length, uint8_t* dataAddr)
{
	uint8_t data;
	SPI_ReadData(0xbc, &data, 1);
	*length = data;

	// 防止读取溢出
	if(data > 256)
		*length	= 256;
	if(data == 0)
		return;
	
	SPI_ReadData(0xbf, dataAddr, *length);
}


void BspKx022_Sleep(void)
{
	BspKx022SetRegister(CNTL1, 	0x00);
}



uint16_t BspKx022_Selftest(void)
{
	uint16_t comparedata;

	BspKx022SetRegister(CNTL1, 	0x80);
	SPI_ReadData(CNTL1, (uint8_t *)&comparedata, 1);

	if(comparedata != 0x80)
	{
		return 0xff;
	}

	BspKx022SetRegister(CNTL1, 	0x00);
	SPI_ReadData(CNTL1, (uint8_t *)&comparedata, 1);

	if(comparedata != 0x00)
	{
		return 0xff;
	}

	return 0;
}






