#include "delay.h"

/*      ºÁÃë¼¶ÑÓÊ±º¯Êı */   
void delay_ms(unsigned int time)
{
      while(time--) usleep(1000);
}
