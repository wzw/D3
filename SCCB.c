#include "SCCB.h"
#include <stdio.h>
#include <sys/unistd.h>
#include <io.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
//#include "delay.h"
//#include "unistd.h"

void startSCCB(void)
{
    IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, OUT);
    SIO_D_SET;     //数据线高电平
    usleep(DELAY_TIME);
    SIO_C_SET;     //在时钟线高的时候数据线由高至低
    usleep(DELAY_TIME);
 
    SIO_D_CLR;
    usleep(DELAY_TIME);

    SIO_C_CLR;   //数据线恢复低电平，单操作函数必要
    usleep(DELAY_TIME);
}
/*
-----------------------------------------------
   功能: stop命令,SCCB的停止信号
   参数: 无
 返回值: 无
-----------------------------------------------
*/
 /*   SDA _________--------
      SCL ____------------- */
void stopSCCB(void)
{
    IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, OUT);  
    SIO_D_CLR;
    usleep(DELAY_TIME);
    SIO_C_SET;
    usleep(DELAY_TIME);
    SIO_D_SET;
    usleep(DELAY_TIME);
}
/*
-----------------------------------------------
   功能: noAck,用于连续读取中的最后一个结束周期
   参数: 无
 返回值: 无
-----------------------------------------------
*/
/*   SDA ____zzzzzzzzzzzzz
      SCL ____------_______ */
void noAck(void)
{
    IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, IN);
    
    SIO_D_SET;
    usleep(DELAY_TIME);
    
    SIO_C_SET;
    usleep(DELAY_TIME);
    
    SIO_C_CLR;
   usleep(DELAY_TIME);
    
    SIO_D_CLR;
    usleep(DELAY_TIME);
}
void SCCB_Ack(void)
{
	SIO_D_OUT;

	SIO_D_CLR;
    usleep(DELAY_TIME);

    SIO_C_SET;
    usleep(DELAY_TIME);

    SIO_C_CLR;
    usleep(DELAY_TIME);

    SIO_D_IN;
    usleep(DELAY_TIME);
}
/*
-----------------------------------------------
   功能: 写入一个字节的数据到SCCB
   参数: 写入数据
    return: 0=success; 1=fail
-----------------------------------------------
*/
/*                 MSB
    SDA  ______-------------__________
  
    SCL  _________-------_____________ */ 
uchar   SCCBwriteByte( uchar m_data )
{
    unsigned char j,tem;

    for(j=0;j<8;j++) //循环8次发送数据
    {
        if((m_data<<j)&0x80)
        {
            SIO_D_SET;
        }
        else
        {
            SIO_D_CLR;
        }
        usleep(DELAY_TIME);
        SIO_C_SET;
        usleep(DELAY_TIME);
        SIO_C_CLR;
        usleep(DELAY_TIME);

    }
    usleep(DELAY_TIME);
    
    SIO_D_IN;/*设置SDA为输入*/
    usleep(DELAY_TIME);
    SIO_C_SET;
    usleep(DELAY_TIME);
    tem = SIO_D_STATE;
    SIO_C_CLR;
    usleep(DELAY_TIME);  
    SIO_D_OUT;/*设置SDA为输出*/

    return(tem); 
}

/*
-----------------------------------------------
   功能: 一个字节数据读取并且返回
   参数: 无
 返回值: 读取到的数据
-----------------------------------------------
*/
uchar SCCBreadByte(void)
{
    unsigned char read,j;
    read=0x00;
    
    SIO_D_IN;/*设置SDA为输入*/
    usleep(DELAY_TIME);
    for(j=8;j>0;j--) //循环8次接收数据
    {            
        usleep(DELAY_TIME);
        SIO_C_SET;
        usleep(DELAY_TIME);
        read=read<<1;
        if(SIO_D_STATE) 
        {
            read=read+1;
        }
        SIO_C_CLR;
        usleep(DELAY_TIME);
    }   
    return(read);
}
