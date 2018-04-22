#include "incs.h"
void Delay(unsigned int time_del)
{
	volatile int t;
	while(time_del--)
		for(t = 4800; t > 0; t--);
}
