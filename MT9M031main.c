/*
 * 摄像头显示程序，该程序将摄像头采集的数据，通过DMA传输到SDRAM，再从SDRAM 显示到TFT上。
 * 版权：
 * 2013.02.19
 * V1.0
 Author: wkf lmr
 Modification:

 02/19/2013  V1.0    wkf, lmr
 */
#include "altera_avalon_pio_regs.h"
#include "delay.h"
#include "alt_types.h"
#include "unistd.h"
//#include "image.h"
//#include "english_16x8.h"
#include <stdio.h>
#include "system.h"
#include "tft.h"
#include "MT9M031.h"

typedef struct {
	unsigned long int DATA;
	unsigned long int DIRECTION;
	unsigned long int INTERRUPT_MASK;
	unsigned long int EDGE_CAPTURE;
	unsigned long int OUTSET;
	unsigned long int OUTCLEAR;
} TRIGGER;
#define TRIGGER_PTR ((TRIGGER*)TRIGGER_BASE)

typedef struct {
	unsigned long int status;
	unsigned long int readaddress;
	unsigned long int writeaddress;
	unsigned long int length;
	unsigned long int reserve1;
	unsigned long int reserve2;
	unsigned long int control;
} DMA;
#define DMA_0 ((DMA*)DMA_0_BASE)

#define DMADES  ((uchar *)(&MT0M031_image[0]))
#define BYTENUM    1228799          //153599
//153600

#define TRIGGER_SET()  TRIGGER_PTR->OUTSET|=0x01
#define TRIGGER_CLR()  TRIGGER_PTR->OUTCLEAR|=0x01

//Global variable 
uint x_offset; /*0-1279*/
uint y_offset; /*0-959*/
uint factor;
uchar MT0M031_image[1228800/*153600*/];

//
/**********************************
 function:
 input: void
 output void
 */
void IOtest(void) {
	TRIGGER_PTR->DIRECTION = 0x01;
}

/**********************************
 function:
 input: void
 output void
 */
void Display_frame(uchar * base, uint x_offset, uint y_offset, uint factor) {
	int i, j;
	uint imaged, colord;
	uint x_address, y_address, address;

	Address_set(0, 0, 240, 320); //设置显示区域

	for (j = 0; j < 240; j++) {
		y_address = (j + y_offset) * 1280;
		for (i = 0; i < 320; i++) {
			x_address = i + x_offset;
			address = (x_address + y_address) * factor;
			imaged = *(base + address) >> 2;
			colord = ((imaged >> 1) << 11) | (imaged << 5) | (imaged >> 1); // bin to GRB_565
			LCD_WR_DATA(colord); //将一帧图像数据输出到TFT显示
		}
	}
}

/**********************************
 function:
 input: uchar * DMAdes_base, DMA data write address
 output void
 */
void DMA_init(uchar * DMAdes_base) {
	DMA_0->control |= 0x1000; //reset
	DMA_0->control |= 0x1000; //reset
	DMA_0->readaddress = CLOCKEDPIO_0_BASE;
	DMA_0->writeaddress = (unsigned long int) DMAdes_base;
	DMA_0->length = BYTENUM;
	DMA_0->control = 0x00000181;
	DMA_0->status &= (~0x01); //clear DONE
	TRIGGER_CLR(); //Trigger
	DMA_0->control |= 0x08; //Enable DMA
	delay_ms(1);
	TRIGGER_SET();
	TRIGGER_CLR(); //Trigger
}

/**********************************
 function:
 input: void
 output void
 */
uint get_number(void) {
	uint number = 0;
	uchar temp;

	printf("Input number: ");
	number = 0;
	while (1) {
		temp = getchar();
		if (temp == '\n')
			break;
		if ((temp >= '0') & (temp <= '9')) {
			number = (number * 10) + (temp & 0x0f);
		}
	}
	return number;
}

/**********************************
 function:
 input: void
 output void
 */
void MT9M031_get_frame(uchar * DMAdes_base) {
	DMA_init(DMAdes_base);
	while ((DMA_0->status & 0x02) && !(DMA_0->status & 0x01))
		;
}

/**********************************
 function:
 input: void
 output void
 */
void MT9M031_Master_Mode(void) {
	uint ii, count;
	uchar * DMAdes_base;

	DMAdes_base = (uchar*) DMADES;
	printf("MT9M031_Master_Mode(Continue running.)\n");
	count = get_number();
	if (!count)
		count = count - 1;

	for (ii = 0; ii < count; ii++) {
		MT9M031_get_frame(DMAdes_base);
		Display_frame(DMAdes_base, x_offset, y_offset, factor);
		printf("%d ", ii);
	}
	printf("\n MT9M031_Master_Mode stop.\n");
}

void MT0M031_trigger_mode(void) {
	printf("MT0M031_trigger_Mode.\n");
	MT0M031_trigger();
}

/**********************************
 function:
 input: void
 output void
 */
void MT0M031_exposure(void) {
}

/**********************************
 function:
 input: void
 output: uchar command inputted.
 */
uchar get_command(void) {
	uchar command;

	command = getchar();
	if (command == '\n')
		return 0;
	while (1) {
		if (getchar() == '\n')
			break;
	}
	return command;
}

/**********************************
 function:
 input: void
 output void
 */
void MT9M031_test_pattern_Mode(void) {
	uchar test_pattern_mode_h, test_pattern_mode_l;

	printf("Set test pattern mode reg 0x3070h): \n");
	printf("Input test_pattern_mode_h): \n");
	printf("\t 0 = No test pattern (normal operation).\n");
	printf("\t 1 = Walking 1s test pattern (12-bit).\n");
	printf("input: ");
	test_pattern_mode_h = get_command() & 0x03;

	printf("Input test_pattern_mode_l): \n");
	printf("\t 0 = No test pattern (normal operation).\n");
	printf("\t 1 = Solid color test pattern.\n");
	printf("\t 2 = 100 percent color bar test pattern.\n");
	printf("\t 3 = Fade-to-grey color bar test pattern.\n");
	printf("input: ");
	test_pattern_mode_l = get_command() & 0x03;

	printf("test_pattern_mode reg should be set to %02X%02X\n",
			test_pattern_mode_h, test_pattern_mode_l);
	wrMT9M031Reg(0x30, 0x70, 2, test_pattern_mode_h, test_pattern_mode_l);
	return;
}

/**********************************
 function:
 input: void
 output void
 */
void help(void) {
	printf("-----------------------------------------------\n");
	printf("MT9M031 test command: \n");
	printf("  0 -- MT9M031_Master_Mode(Continue running.)\n");
	printf("  1 -- Exposure\n");
	printf("  2 -- \n");
	printf("  9 -- MT9M031_test_pattern_Mode.\n");
	printf("  o -- LCD_display_option.\n");
	printf("  h -- help\n");
	printf("-----------------------------------------------\n");
	printf("input command(h for help): ");
}

/**********************************
 function:
 input: void
 output void
 */
void LCD_display_option(void) {
	uint temp;

	printf("Input x_offset:");
	temp = get_number();
	if (temp)
		x_offset = temp;
	if (x_offset > (image_W - LCD_W - 1))
		x_offset = image_W - LCD_W - 1;
	printf("Input y_offset:");
	temp = get_number();
	if (temp)
		y_offset = temp;
	if (y_offset > (image_H - LCD_H - 1))
		x_offset = image_H - LCD_H - 1;
	printf("Input factor:");
	temp = get_number();
	if (temp == 3)
		temp = 4;
	if (temp)
		factor = temp;
	if (factor > 4)
		factor = 4;
}

/**********************************
 function: Main Program
 input: void
 output void
 */
int main() {
	uchar command;

	printf("Start Main %d\n", SYSID_TIMESTAMP);

	IOWR_ALTERA_AVALON_PIO_DATA(TFT_RS_BASE,1);
	IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,1);
	IOWR_ALTERA_AVALON_PIO_DATA(TFT_WR_BASE,1);
	IOWR_ALTERA_AVALON_PIO_DATA(TFT_RD_BASE,1);
	IOWR_ALTERA_AVALON_PIO_DATA(TFT_REST_BASE,1);
	IOWR_ALTERA_AVALON_PIO_DATA(LVC245_DIR_BASE,1); //将扩展板子上的74LVC245设置成FPGA到TFT 的输出方向
	IOWR_ALTERA_AVALON_PIO_DATA(LVC245_OE_BASE,0); //输出打开
	IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,0); //打开片选使能
	LCD_reset(); //LCD复位
	LCD_Init(); //初始化LCD

	POINT_COLOR = RED;
	IOWR_ALTERA_AVALON_PIO_DATA(LVC245_DIR_BASE,1); //控制LVC245，使数据从FPGA输出给TFT
	LCD_SetCursor(0, 0); //将坐标设置到0，0位置
	LCD_WriteRAM_Prepare();
	LCD_Clear(BLUE); //全屏显示蓝色
	POINT_COLOR = RED;
	LCD_ShowString(30, 50, "FPGA TFT MT0M031 Ver 5 ^_^ ");
	LCD_ShowString(30, 70, "MT9M031 DMA TFT TEST");
	LCD_ShowString(30, 90, "wkf@eelay.com");
	LCD_ShowString(30, 110, "2013/02/18");
	Draw_Circle(100, 100, 80); //显示第一个圆
	Draw_Circle(150, 100, 80); //显示第二个圆
	Draw_Circle(200, 100, 80); //显示第三个圆

	delay_ms(1000);

	// Show gray
	LCD_Gray();

	delay_ms(1000);

	IOWR_ALTERA_AVALON_PIO_DATA(LVC245_DIR_BASE,1); //控制LVC245，使数据从FPGA输出给TFT
	LCD_SetCursor(0, 0); //将坐标设置到0，0位置
	LCD_WriteRAM_Prepare();

	while (MT9M031_init())
		;
	IOWR_ALTERA_AVALON_PIO_DATA(MT9M031_SHUTTER_BASE,1);

	IOtest();

	x_offset = 0;
	y_offset = 0;
	factor = 1;

	help();
	while (1) {
		command = get_command();
		switch (command) {
		case '1':
			MT0M031_trigger_mode();
			break;

		case '2':
			MT0M031_exposure();
			break;

		case '3':
			break;

		case '4':
			break;

		case '5':
			break;

		case '0':
			MT9M031_Master_Mode();
			break;

		case 'o':
			LCD_display_option();
			break;

		case '9':
			printf("MT9M031_test_pattern_Mode set. \n");
			MT9M031_test_pattern_Mode();
			break;

		case 'h':
			help();
			break;
		default:
			break;
		}
	}
	return 0;
}
