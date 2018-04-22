#include "cam.h"
#define U8P(x) (uint8_t*)(x)
#define READWORD(x) (((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x)))

Cam::Cam()
{
	// Set CS on camera to 1 (chip select)
	//PORTD->PCR[7] |= PORT_PCR_MUX(1);
	//PORTD->PCR[7] &= 1;
	
	// Now, configure Serial ports
	SPI_init();
	// Test if it's working
	SPI_write((uint8_t*)0xAA, sizeof(0xAA), (uint8_t)0x00);
	uint8_t * buff;
	SPI_read(buff, sizeof(uint8_t), (uint8_t)0x00);
	if(*buff != (uint8_t)0xAA)
	{
		return;
	}
	SPI_write((uint8_t*)0xFF, sizeof(0xFF), 0x01);
	SPI_write((uint8_t*)0x12, sizeof(0x12), 0x80);
	Delay(1);
	WriteWord(OV2640_JPEG_INIT);
	WriteWord(OV2640_YUV422);
	WriteWord(OV2640_JPEG);
	WriteWord(OV2640_320x240_JPEG);
}

void Cam::WriteWord(const struct sensor_reg reglist[])
{
	uint16_t addr = 0;
	uint16_t val = 0;
	const struct sensor_reg *r = reglist;
	while((addr != 0xFF) | (val != 0xFF))
	{
		addr = READWORD(&r->reg);
		val = READWORD(&r->val);
		SPI_write((uint8_t*)(val & 0xFF), sizeof(val & 0xFF), addr);
	}
}

void Cam::FlushFIFO()
{
	SPI_write((uint8_t*)FIFO_RDPTR_RST_MASK, sizeof(FIFO_RDPTR_RST_MASK), ARDUCHIP_FIFO);
	SPI_write((uint8_t*)FIFO_CLEAR_MASK, sizeof(FIFO_CLEAR_MASK), ARDUCHIP_FIFO);
}
//void Cam::GetBit(uint8_t addr, uint8_t bit)
//{
//}
void Cam::Capture()
{
	FlushFIFO();
	SPI_write((uint8_t*)FIFO_START_MASK, sizeof(FIFO_START_MASK), ARDUCHIP_FIFO);
}
