#include "delay.h"

/*      ���뼶��ʱ���� */   
void delay_ms(unsigned int time)
{
      while(time--) usleep(1000);
}
