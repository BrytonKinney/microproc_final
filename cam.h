#ifndef CAM_H
#define CAM_H
#include "incs.h"
#else
#include "incs.h"
#endif


class Cam
{
public:
	Cam();
	void WriteWord(const struct sensor_reg reglist[]);
	void FlushFIFO();
	void Capture();
};	
