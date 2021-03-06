/*
Module: MT9M031 register operation.
Author: wkf
Modify:
V1.00 20130117
*/
#include "SCCB.h"
#include "delay.h"
#include "MT9M031.h"

/*[MT9M031 full size 45fps setting 24M input, 74.25output 20120227] */

/* sensor reset,HW or SW */
uchar MT9M031_reset_reg[1][5]=
{
                        //dealy=200
    {0x30, 0x1A, 2, 0x00, 0xD9}    //REG= 0x301A, 0x00D9 	// RESET_REGISTER
};

//firmware setting registers
uchar firmware_setting_reg[134][5]=
{
    {0x30, 0x88, 2, 0x80, 0x00},   //REG= 0x3088, 0x8000 	// SEQ_CTRL_PORT
    {0x30, 0x86, 2, 0x32, 0x27},   //REG= 0x3086, 0x3227 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x01, 0x01},   //REG= 0x3086, 0x0101 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0F, 0x25},   //REG= 0x3086, 0x0F25 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x08},   //REG= 0x3086, 0x0808 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x02, 0x27},   //REG= 0x3086, 0x0227 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x01, 0x01},   //REG= 0x3086, 0x0101 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x37},   //REG= 0x3086, 0x0837 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x00},   //REG= 0x3086, 0x2700 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x01, 0x38},   //REG= 0x3086, 0x0138 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x01},   //REG= 0x3086, 0x2701 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x01, 0x3A},   //REG= 0x3086, 0x013A 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x00},   //REG= 0x3086, 0x2700 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x01, 0x25},   //REG= 0x3086, 0x0125 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x20},   //REG= 0x3086, 0x0020 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x3C, 0x25},   //REG= 0x3086, 0x3C25 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x40},   //REG= 0x3086, 0x0040 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x34, 0x27},   //REG= 0x3086, 0x3427 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x3F},   //REG= 0x3086, 0x003F 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x00},   //REG= 0x3086, 0x2500 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x20, 0x37},   //REG= 0x3086, 0x2037 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x40},   //REG= 0x3086, 0x2540 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x40, 0x36},   //REG= 0x3086, 0x4036 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x00},   //REG= 0x3086, 0x2500 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x40, 0x31},   //REG= 0x3086, 0x4031 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x40},   //REG= 0x3086, 0x2540 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x40, 0x3D},   //REG= 0x3086, 0x403D 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x64, 0x25},   //REG= 0x3086, 0x6425 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x20, 0x20},   //REG= 0x3086, 0x2020 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x3D, 0x64},   //REG= 0x3086, 0x3D64 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x10},   //REG= 0x3086, 0x2510 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x10, 0x37},   //REG= 0x3086, 0x1037 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x20},   //REG= 0x3086, 0x2520 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x20, 0x10},   //REG= 0x3086, 0x2010 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x10},   //REG= 0x3086, 0x2510 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x10, 0x0F},   //REG= 0x3086, 0x100F 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x08},   //REG= 0x3086, 0x2708 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x02},   //REG= 0x3086, 0x0802 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x40},   //REG= 0x3086, 0x2540 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x40, 0x2D},   //REG= 0x3086, 0x402D 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x26, 0x08},   //REG= 0x3086, 0x2608 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x28, 0x0D},   //REG= 0x3086, 0x280D 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x17, 0x09},   //REG= 0x3086, 0x1709 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x26, 0x00},   //REG= 0x3086, 0x2600 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x28, 0x05},   //REG= 0x3086, 0x2805 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x26, 0xA7},   //REG= 0x3086, 0x26A7 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x28, 0x07},   //REG= 0x3086, 0x2807 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x80},   //REG= 0x3086, 0x2580 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x80, 0x29},   //REG= 0x3086, 0x8029 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x17, 0x05},   //REG= 0x3086, 0x1705 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x00},   //REG= 0x3086, 0x2500 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x40, 0x27},   //REG= 0x3086, 0x4027 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x22, 0x22},   //REG= 0x3086, 0x2222 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x16, 0x16},   //REG= 0x3086, 0x1616 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x26},   //REG= 0x3086, 0x2726 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x26, 0x17},   //REG= 0x3086, 0x2617 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x36, 0x26},   //REG= 0x3086, 0x3626 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0xA6, 0x17},   //REG= 0x3086, 0xA617 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x03, 0x26},   //REG= 0x3086, 0x0326 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0xA4, 0x17},   //REG= 0x3086, 0xA417 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x1F, 0x28},   //REG= 0x3086, 0x1F28 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x05, 0x26},   //REG= 0x3086, 0x0526 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x20, 0x28},   //REG= 0x3086, 0x2028 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x04, 0x25},   //REG= 0x3086, 0x0425 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x20, 0x20},   //REG= 0x3086, 0x2020 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x00},   //REG= 0x3086, 0x2700 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x26, 0x25},   //REG= 0x3086, 0x2625 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x00},   //REG= 0x3086, 0x0000 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x17, 0x1E},   //REG= 0x3086, 0x171E 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x00},   //REG= 0x3086, 0x2500 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x04, 0x25},   //REG= 0x3086, 0x0425 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x20},   //REG= 0x3086, 0x0020 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x21, 0x17},   //REG= 0x3086, 0x2117 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x12, 0x1B},   //REG= 0x3086, 0x121B 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x17, 0x03},   //REG= 0x3086, 0x1703 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x26},   //REG= 0x3086, 0x2726 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x26, 0x17},   //REG= 0x3086, 0x2617 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x28, 0x28},   //REG= 0x3086, 0x2828 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x05, 0x17},   //REG= 0x3086, 0x0517 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x1A, 0x26},   //REG= 0x3086, 0x1A26 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x60, 0x17},   //REG= 0x3086, 0x6017 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0xAE, 0x25},   //REG= 0x3086, 0xAE25 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x80},   //REG= 0x3086, 0x0080 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x00},   //REG= 0x3086, 0x2700 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x26, 0x26},   //REG= 0x3086, 0x2626 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x18, 0x28},   //REG= 0x3086, 0x1828 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x2E},   //REG= 0x3086, 0x002E 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x2A, 0x28},   //REG= 0x3086, 0x2A28 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x1E},   //REG= 0x3086, 0x081E 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x41, 0x27},   //REG= 0x3086, 0x4127 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x10, 0x10},   //REG= 0x3086, 0x1010 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x02, 0x14},   //REG= 0x3086, 0x0214 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x60, 0x60},   //REG= 0x3086, 0x6060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0A, 0x14},   //REG= 0x3086, 0x0A14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x60, 0x60},   //REG= 0x3086, 0x6060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0B, 0x14},   //REG= 0x3086, 0x0B14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x60, 0x60},   //REG= 0x3086, 0x6060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0C, 0x14},   //REG= 0x3086, 0x0C14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x60, 0x60},   //REG= 0x3086, 0x6060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0D, 0x14},   //REG= 0x3086, 0x0D14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x60, 0x60},   //REG= 0x3086, 0x6060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x02, 0x17},   //REG= 0x3086, 0x0217 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x3C, 0x14},   //REG= 0x3086, 0x3C14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x60},   //REG= 0x3086, 0x0060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0A, 0x14},   //REG= 0x3086, 0x0A14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x60},   //REG= 0x3086, 0x0060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0B, 0x14},   //REG= 0x3086, 0x0B14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x60},   //REG= 0x3086, 0x0060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0C, 0x14},   //REG= 0x3086, 0x0C14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x60},   //REG= 0x3086, 0x0060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0D, 0x14},   //REG= 0x3086, 0x0D14 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x60},   //REG= 0x3086, 0x0060 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x11},   //REG= 0x3086, 0x0811 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x00},   //REG= 0x3086, 0x2500 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x10, 0x27},   //REG= 0x3086, 0x1027 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x10},   //REG= 0x3086, 0x0010 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x2F, 0x6F},   //REG= 0x3086, 0x2F6F 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x0F, 0x3E},   //REG= 0x3086, 0x0F3E 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x00},   //REG= 0x3086, 0x2500 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x27},   //REG= 0x3086, 0x0827 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x08},   //REG= 0x3086, 0x0008 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x30, 0x66},   //REG= 0x3086, 0x3066 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x32, 0x25},   //REG= 0x3086, 0x3225 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x00, 0x08},   //REG= 0x3086, 0x0008 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x27, 0x00},   //REG= 0x3086, 0x2700 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x30},   //REG= 0x3086, 0x0830 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x66, 0x31},   //REG= 0x3086, 0x6631 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x3D, 0x64},   //REG= 0x3086, 0x3D64 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x25, 0x08},   //REG= 0x3086, 0x2508 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x3D},   //REG= 0x3086, 0x083D 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0xFF, 0x3D},   //REG= 0x3086, 0xFF3D 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x2A, 0x27},   //REG= 0x3086, 0x2A27 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x08, 0x3F},   //REG= 0x3086, 0x083F 	// SEQ_DATA_PORT
    {0x30, 0x86, 2, 0x2C, 0x00}    //REG= 0x3086, 0x2C00 	// SEQ_DATA_PORT
};
//Column Correction ReTriggering
uchar Column_Correction_ReTriggering_reg[6][5]=
{
    {0x30, 0x1A, 2, 0x00, 0xD8},   //REG= 0x301A, 0x00D8 	// RESET_REGISTER
    {0x30, 0xD4, 2, 0x60, 0x07},   //REG= 0x30D4, 0x6007 	// COLUMN_CORRECTION
    {0x30, 0x1A, 2, 0x00, 0xDC},   //REG= 0x301A, 0x00DC 	// RESET_REGISTER
    {0x30, 0x1A, 2, 0x00, 0xD8},   //REG= 0x301A, 0x00D8 	// RESET_REGISTER
    {0x30, 0xD4, 2, 0xE0, 0x07},   //REG= 0x30D4, 0xE007 	// COLUMN_CORRECTION
    {0x30, 0x1A, 2, 0x00, 0xDC}    //REG= 0x301A, 0x00DC 	// RESET_REGISTER
};

//A-1000GS REV2 Optimized Settings
uchar A_1000GS_REV2_Optimized_Settings_reg[15][5]=
{
    {0x30, 0x7A, 2, 0x00, 0x00},   //REG= 0x307A, 0x0000 	// TEST_RAW_MODE
    {0x30, 0xEA, 2, 0x0C, 0x00},   //REG= 0x30EA, 0x0C00 	// RESERVED_MFR_30EA
    {0x30, 0x44, 2, 0x04, 0x04},   //REG= 0x3044, 0x0404 	// DARK_CONTROL
    {0x30, 0x1E, 2, 0x01, 0x2C},   //REG= 0x301E, 0x012C 	// DATA_PEDESTAL
    {0x31, 0x80, 2, 0x80, 0x00},   //REG= 0x3180, 0x8000 	// RESERVED_MFR_3180
    {0x30, 0xD4, 2, 0xE0, 0x07},   //REG= 0x30D4, 0xE007 	// COLUMN_CORRECTION
    {0x30, 0x14, 2, 0x03, 0x80},   //REG= 0x3014, 0x0380 	// FINE_INTEGRATION_TIME
    {0x3E, 0xD6, 2, 0x00, 0xFD},   //REG= 0x3ED6, 0x00FD 	// RESERVED_MFR_3ED6
    {0x3E, 0xD8, 2, 0x0F, 0xFF},   //REG= 0x3ED8, 0x0FFF 	// RESERVED_MFR_3ED8
    {0x3E, 0xDA, 2, 0x00, 0x03},   //REG= 0x3EDA, 0x0003 	// RESERVED_MFR_3EDA
    {0x3E, 0xDC, 2, 0xF8, 0x7A},   //REG= 0x3EDC, 0xF87A 	// RESERVED_MFR_3EDC
    {0x3E, 0xDE, 2, 0xE0, 0x75},   //REG= 0x3EDE, 0xE075 	// RESERVED_MFR_3EDE
    {0x3E, 0xE0, 2, 0x07, 0x7C},   //REG= 0x3EE0, 0x077C 	// RESERVED_MFR_3EE0
    {0x3E, 0xE2, 2, 0xA4, 0xEB},   //REG= 0x3EE2, 0xA4EB 	// RESERVED_MFR_3EE2
    {0x3E, 0xE4, 2, 0xD2, 0x08}    //REG= 0x3EE4, 0xD208 	// RESERVED_MFR_3EE4
};
uchar PLL_Settings_reg[5][5]=
{
//PLL 27M input, 74.25 output
    {0x30, 0x2C, 2, 0x00, 0x02},   //REG= 0x302C, 0x0001 	// VT_SYS_CLK_DIV
    {0x30, 0x2A, 2, 0x00, 0x08},   //REG= 0x302A, 0x0008 	// VT_PIX_CLK_DIV
    {0x30, 0x2E, 2, 0x00, 0x02},   //REG= 0x302E, 0x0002 	// PRE_PLL_CLK_DIV
    {0x30, 0x30, 2, 0x00, 0x2C},   //REG= 0x3030, 0x002C 	// PLL_MULTIPLIER
    {0x30, 0xB0, 2, 0x00, 0x80}    //REG= 0x30B0, 0x0080 	// DIGITAL_TEST

//[PLL 26M input, 26M output]
//    {0x30, 0x2A, 2, 0x00, 0x09},   //REG = 0x302A, 0x0009	//VT_PIX_CLK_DIV = 9
//    {0x30, 0x2C, 2, 0x00, 0x03},   //REG = 0x302C, 0x0003	//VT_SYS_CLK_DIV = 3
//    {0x30, 0x2E, 2, 0x00, 0x02},   //REG = 0x302E, 0x0002	//PRE_PLL_CLK_DIV = 2
//    {0x30, 0x30, 2, 0x00, 0x34},   //REG = 0x3030, 0x0034	//PLL_MULTIPLIER = 52
//    {0x30, 0xB0, 2, 0x00, 0x80}    //REG = 0x30B0, 0x0080 	// DIGITAL_TEST
                                   // delay=100
};

//Full Resolution 1280x960 45fps
uchar Full_Resolution_reg[10][5]=
{
    {0x30, 0x02, 2, 0x00, 0x00},   //REG= 0x3002, 0x0000 	// Y_ADDR_START
    {0x30, 0x04, 2, 0x00, 0x00},   //REG= 0x3004, 0x0000 	// X_ADDR_START
    {0x30, 0x06, 2, 0x03, 0xBF},   //REG= 0x3006, 0x03BF 	// Y_ADDR_END
    {0x30, 0x08, 2, 0x04, 0xFF},   //REG= 0x3008, 0x04FF 	// X_ADDR_END
    {0x30, 0x0A, 2, 0x03, 0xE5},   //REG= 0x300A, 0x03E5 	// FRAME_LENGTH_LINES
    {0x30, 0x0C, 2, 0x06, 0x72},   //REG= 0x300C, 0x0672 	// LINE_LENGTH_PCK
    {0x30, 0x12, 2, 0x01, 0xC2},   //REG= 0x3012, 0x01C2 	// COARSE_INTEGRATION_TIME
    {0x30, 0xA2, 2, 0x00, 0x01},   //REG= 0x30A2, 0x0001 	// X_ODD_INC
    {0x30, 0xA6, 2, 0x00, 0x01},   //REG= 0x30A6, 0x0001 	// Y_ODD_INC
    {0x30, 0x40, 2, 0x00, 0x00}    //REG= 0x3040, 0x0000 	// READ_MODE
};

//other setting
uchar other_reg[3][5]=
{
    {0x30, 0x32, 2, 0x00, 0x20},   //REG= 0x3032, 0x0020 	// DIGITAL_BINNING
    {0x30, 0x28, 2, 0x00, 0x10},   //REG= 0x3028, 0x0010 	// ROW_SPEED
    {0x30, 0x1A, 2, 0x19, 0xD8}    //REG= 0x301A, 0x10DC 	// RESET_REGISTER
};
//test pattern setting
uchar test_pattern_reg[5][5]=
{
    {0x30, 0x70, 2, 0x00, 0x00},   //test_pattern_mode
    {0x30, 0x72, 2, 0x00, 0x80},   //test_data_red
    {0x30, 0x74, 2, 0x00, 0x80},   //test_data_greenr
    {0x30, 0x76, 2, 0x00, 0x80},   //test_data_blue
    {0x30, 0x78, 2, 0x00, 0x80}    //test_data_greenb
    //{0x30, 0x7A, 2, 0x10, 0xDC}    //test_raw_mode
};

////////////////////////////
//Function:write MTpM031 reg
//return: 0=success; 1=fail
uchar wrMT9M031Reg(uchar regID_h, uchar regID_l, uchar length, uchar regDat_h, uchar regDat_l)
{
	startSCCB();
	if(SCCBwriteByte(0x20))
	{
		stopSCCB();
		return(1);
	}
	usleep(DELAY_TIME);
  	if(SCCBwriteByte(regID_h))
	{
		stopSCCB();
		return(1);
	}
  	usleep(DELAY_TIME);
  	if(SCCBwriteByte(regID_l))
	{
		stopSCCB();
		return(1);
	}
  	usleep(DELAY_TIME);
  	if(SCCBwriteByte(regDat_h))
	{
		stopSCCB();
		return(1);
	}
    if(length == 2){
    	usleep(DELAY_TIME);
      	if(SCCBwriteByte(regDat_l))
    	{
    		stopSCCB();
    		return(1);
    	}
    }
  	stopSCCB();
	
  	return(0);
}
////////////////////////////
//Function:read MTpM031 reg
//return: 0=success; 1=fail
uchar rdMT9M031Reg(uchar regID_h, uchar regID_l, uchar length, uchar *regDat_h, uchar *regDat_l)
{
	//ͨ��д�������üĴ�����ַ
	startSCCB();
	if(SCCBwriteByte(0x20))
	{
		stopSCCB();
		return(1);
	}
	usleep(DELAY_TIME);
  	if(SCCBwriteByte(regID_h))
	{
		stopSCCB();
		return(1);
	}
  	usleep(DELAY_TIME);
  	if(SCCBwriteByte(regID_l))
	{
		stopSCCB();
		return(1);
	}
	stopSCCB();

	usleep(DELAY_TIME);
	
	//���üĴ�����ַ�󣬲��Ƕ�
	startSCCB();
	if(SCCBwriteByte(0x21))
	{
		stopSCCB();
		return(1);
	}
	usleep(DELAY_TIME);
  	*regDat_h=SCCBreadByte();
    if(length == 2){
    	usleep(DELAY_TIME);
    	SCCB_Ack();
      	*regDat_l=SCCBreadByte();
    }
  	noAck();
  	stopSCCB();
  	return(0);
}


//(140,16,640,480) is good for VGA
//(272,16,320,240) is good for QVGA
/* config_MT9M031_window */
void MT9M031_config_window(uint startx, uint starty,uint width, uint height)
{
	uint endx;
	uint endy;// "v*2"����
	uint temp_reg1, temp_reg2;
//	uchar state;
	uchar temp;
	
	endx=(startx+width);
	endy=(starty+height+height);// "v*2"����
//	state = rdMT9M031Reg(0x03, &temp_reg1 );
	temp_reg1 &= 0xf0;
//	state = rdMT9M031Reg(0x32, &temp_reg2 );
	temp_reg2 &= 0xc0;
	
	// Horizontal
	temp = temp_reg2|((endx&0x7)<<3)|(startx&0x7);
//	state = wrMT9M031Reg(0x32, temp );
	temp = (startx&0x7F8)>>3;
//	state = wrMT9M031Reg(0x17, temp );
	temp = (endx&0x7F8)>>3;
//	state = wrMT9M031Reg(0x18, temp );
	
	// Vertical
	temp = temp_reg1|((endy&0x3)<<2)|(starty&0x3);
//	state = wrMT9M031Reg(0x03, temp );
	temp = starty>>2;
//	state = wrMT9M031Reg(0x19, temp );
	temp = endy>>2;
//	state = wrMT9M031Reg(0x1A, temp );
}

//Function: MT9M031_reset
//return: 0=success; 1=fail
uchar MT9M031_reset(void)
{
	usleep(200);
	return(wrMT9M031Reg(0x30, 0x1A, 2, 0x19, 0xD9));
}

//Function: MT9M031_firmware_setting
//return: 0=success; 1=fail
uchar MT9M031_firmware_setting(void)
{
	uint i=0;

	for(i=0; i<134; i++)
	{
		if(wrMT9M031Reg(firmware_setting_reg[i][0], firmware_setting_reg[i][1], firmware_setting_reg[i][2], firmware_setting_reg[i][3], firmware_setting_reg[i][4])) return 1;
	}
	return 0;                       //ok.
}

//Function: MT9M031_Column_Correction_ReTriggering
//return: 0=success; 1=fail
uchar MT9M031_Column_Correction_ReTriggering(void)
{
	uint i=0;

	for(i=0; i<6; i++)
	{
		if(wrMT9M031Reg(Column_Correction_ReTriggering_reg[i][0], Column_Correction_ReTriggering_reg[i][1], Column_Correction_ReTriggering_reg[i][2], Column_Correction_ReTriggering_reg[i][3], Column_Correction_ReTriggering_reg[i][4])) return 1;
	}
	return 0;                       //ok.
}

//Function: MT9M031_A_1000GS_REV2_Optimized_Settings
//return: 0=success; 1=fail
uchar MT9M031_A_1000GS_REV2_Optimized_Settings(void)
{
	uint i=0;

	for(i=0; i<15; i++)
	{
		if(wrMT9M031Reg(A_1000GS_REV2_Optimized_Settings_reg[i][0], A_1000GS_REV2_Optimized_Settings_reg[i][1], A_1000GS_REV2_Optimized_Settings_reg[i][2], A_1000GS_REV2_Optimized_Settings_reg[i][3], A_1000GS_REV2_Optimized_Settings_reg[i][4])) return 1;
	}
	return 0;                       //reset ok.
}

//Function: MT9M031_PLL_Settings
//return: 0=success; 1=fail
uchar MT9M031_PLL_Settings(void)
{
	uint i=0;

	for(i=0; i<5; i++)
	{
		if(wrMT9M031Reg(PLL_Settings_reg[i][0], PLL_Settings_reg[i][1], PLL_Settings_reg[i][2], PLL_Settings_reg[i][3], PLL_Settings_reg[i][4])) return 1;
	}
	return 0;                       //reset ok.
}

//Function: MT9M031_Full_Resolution
//return: 0=success; 1=fail
uchar MT9M031_Full_Resolution(void)
{
	uint i=0;

	for(i=0; i<10; i++)
	{
		if(wrMT9M031Reg(Full_Resolution_reg[i][0], Full_Resolution_reg[i][1], Full_Resolution_reg[i][2], Full_Resolution_reg[i][3], Full_Resolution_reg[i][4])) return 1;
	}
	return 0;                       //reset ok.
}

//Function: MT9M031_other_setting
//return: 0=success; 1=fail
uchar MT9M031_other_setting(void)
{
	uint i=0;

	for(i=0; i<3; i++)
	{
		if(wrMT9M031Reg(other_reg[i][0], other_reg[i][1], other_reg[i][2], other_reg[i][3], other_reg[i][4])) return 1;
	}
	return 0;                       //reset ok.
}

//Function: MT9M031_test_pattern_setting
//return: 0=success; 1=fail
uchar MT9M031_test_pattern_setting(void)
{
	uint i=0;

	for(i=0; i<5; i++)
	{
		if(wrMT9M031Reg(test_pattern_reg[i][0], test_pattern_reg[i][1], test_pattern_reg[i][2], test_pattern_reg[i][3], test_pattern_reg[i][4])) return 1;
	}
	return 0;                       //reset ok.
}

//Function: MT9M031_trigger
//return: 0=success; 1=fail
uchar MT9M031_trigger(void)
{
    uchar gpi_status_h, gpi_status_l;
    uint ii;

    gpi_status_h = 0;
    gpi_status_l = 0;
    if(rdMT9M031Reg(0x30, 0x1A, 2, &gpi_status_h, &gpi_status_l)) return 1;
    printf("reset reg = 0x%02X%02X\n", gpi_status_h, gpi_status_l);
    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_SHUTTER_BASE,1);
    for(ii=0x0100; ii>0; ii--);
	if(rdMT9M031Reg(0x30, 0x26, 2, &gpi_status_h, &gpi_status_l)) return 1;
    printf("gpi_status = 0x%02X%02X\n", gpi_status_h, gpi_status_l);
    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_SHUTTER_BASE,0);
	if(rdMT9M031Reg(0x30, 0x26, 2, &gpi_status_h, &gpi_status_l)) return 1;
    printf("gpi_status = 0x%02X%02X\n", gpi_status_h, gpi_status_l);
    return 0;
}

//Function: MT9M031_init
//return: 0=success; 1=fail
uchar MT9M031_init(void)
{
    uchar chip_version_reg_h, chip_version_reg_l;
    uchar revision;
    
    printf("Start init MT9M031\n");

    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_RESETN_BASE,0);
	delay_ms(200);
    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_RESETN_BASE,1);
	delay_ms(200);

    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_SHUTTER_BASE,1);
    usleep(200);
    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_SHUTTER_BASE,0);

    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_STANDBY_BASE,1);
    usleep(200);
    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_STANDBY_BASE,0);

    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_OEN_BASE,1);
    usleep(200);
    IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_OEN_BASE,0);
	delay_ms(200);

    printf("Reset MT9M031\n");
    while(MT9M031_reset()){
        delay_ms(200);
    }
    delay_ms(200);
    
    printf("Read MT9M031 chip ID\n");
    while(rdMT9M031Reg(0x30, 0x00, 2, &chip_version_reg_h, &chip_version_reg_l));
    printf("Image sensor Chip Version = 0x%02x%02x.\n", chip_version_reg_h, chip_version_reg_l);
    while(rdMT9M031Reg(0x30, 0x0E, 1, &revision, &revision));
    printf("Image sensor Chip revision = 0x%02x.\n", revision);

    printf("Do init MT9M031\n");

	if(MT9M031_reset()) return 1;
	delay_ms(200);
	if(MT9M031_firmware_setting()) return 1;
	if(MT9M031_Column_Correction_ReTriggering()) return 1;
	if(MT9M031_A_1000GS_REV2_Optimized_Settings()) return 1;
	if(MT9M031_PLL_Settings()) return 1;
	if(MT9M031_Full_Resolution()) return 1;
	if(MT9M031_other_setting()) return 1;
	if(MT9M031_test_pattern_setting()) return 1;
  
    printf("MT9M031 Init OK!\n");
	return 0;                       //ok
} 

