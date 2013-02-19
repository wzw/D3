#ifndef _SCCB_H
#define _SCCB_H

#include"altera_avalon_pio_regs.h"
#include"system.h"
#include "VARIABLE.h"

#define DELAY_TIME 5
#define OUT 1
#define IN 0

#define SIO_C_SET		IOWR_ALTERA_AVALON_PIO_DATA(SCL_BASE, 1)//{SCCB_PORT|=(1<<SCCB_SIO_C);}
#define SIO_C_CLR		IOWR_ALTERA_AVALON_PIO_DATA(SCL_BASE, 0)//{SCCB_PORT&=~(1<<SCCB_SIO_C);}
#define SIO_D_SET		IOWR_ALTERA_AVALON_PIO_DATA(SDA_BASE, 1)//{SCCB_PORT|=(1<<SCCB_SIO_D);}
#define SIO_D_CLR		IOWR_ALTERA_AVALON_PIO_DATA(SDA_BASE, 0)//{SCCB_PORT&=~(1<<SCCB_SIO_D);}

#define SIO_D_IN		IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, IN)//{SCCB_DDR&=~(1<<SCCB_SIO_D);}
#define SIO_D_OUT		IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, OUT)//{SCCB_DDR|=(1<<SCCB_SIO_D);}

#define SIO_D_STATE	    IORD_ALTERA_AVALON_PIO_DATA(SDA_BASE)  //((SCCB_PIN&(1<<SCCB_SIO_D))==(1<<SCCB_SIO_D))


///////////////////////////////////////////
//void DelaySCCB(void);
//void InitSCCB(void);
void startSCCB(void);

void stopSCCB(void);
void noAck(void);
void SCCB_Ack(void);
uchar SCCBwriteByte(uchar m_data);
uchar SCCBreadByte(void);


#endif /* _SCCB_H */
