#ifndef _MT9M031_H
#define _MT9M031_H

#include "system.h"
#include "VARIABLE.h"
#include "SCCB.h"
#include <STDIO.H> 
#include "unistd.h"
#include "altera_avalon_pio_regs.h"

#define image_W 1280
#define image_H 960
/////////////////////////////////////////
uchar wrMT9M031Reg(uchar regID_h, uchar regID_l, uchar length, uchar regDat_h, uchar regDat_l);
uchar rdMT9M031Reg(uchar regID_h, uchar regID_l, uchar length, uchar *regDat_h, uchar *regDat_l);
void MT9M031_config_window(uint startx, uint starty,uint width, uint height);
uchar MT9M031_reset(void);
uchar MT9M031_trigger(void);
uchar MT9M031_init(void);

#endif 
