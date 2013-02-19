#include "tft.h"
#include "delay.h"
#include "font.h"

#define USE_HORIZONTAL  //�����Ƿ�ʹ�ú���

alt_u16 BACK_COLOR, POINT_COLOR;
alt_u16 DeviceCode;

void LCD_WR_REG(alt_u16 data)   //��������д�뺯��
{   
    IOWR_ALTERA_AVALON_PIO_DATA(LVC245_DIR_BASE,1); //����LVC245��ʹ���ݴ�FPGA�����TFT
    //IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,1);    //ʹFPGA���ģ�����������TFT��������
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_RS_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_WR_BASE,0);
    usleep(5);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_DATA_BASE,data);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_WR_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,1);
}
void LCD_WR_DATA(alt_u16 data)
{
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_RS_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_DATA_BASE,data);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_WR_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_WR_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,1);
} 

void LCD_WriteReg(alt_u16 index,alt_u16 data)
{    
     LCD_WR_REG(index);
     LCD_WR_DATA(data);
}
//���Ĵ���
alt_u16 LCD_ReadReg(alt_u16 LCD_Reg)
{                                          
    alt_u16 t;
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(LVC245_DIR_BASE,1); //����LVC245��ʹ���ݴ�FPGA�����TFT
    //IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,1);    //ʹFPGA���ģ�����������TFT��������

    LCD_WR_REG(LCD_Reg);
    IOWR_ALTERA_AVALON_PIO_DATA(LVC245_DIR_BASE,0); //FPGA��������
   // IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,1);    //ʹFPGA���ģ���TFT�������϶�ȡ����

    IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_WR_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_RS_BASE,1);
    
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_RD_BASE,0);//LCD_RD_CLR;
    usleep(5);//FOR 8989,��ʱ5us
     t = IORD_ALTERA_AVALON_PIO_DATA(TFT_DATA_BASE);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_RD_BASE,1);
    usleep(5);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_CS_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(LVC245_DIR_BASE,1);//FPGA������ݸ�TFT
    return t;  
} 
//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
    LCD_WR_REG(0x0022);
}    
//LCDдGRAM
void LCD_WriteRAM(alt_u16 RGB_Code)
{                               
    LCD_WR_DATA(RGB_Code);//дʮ��λGRAM
}

//LCD������ʾ
void LCD_DisplayOn(void)
{                      
    LCD_WriteReg(0x07, 0x0173); //26��ɫ��ʾ����
}    
//LCD�ر���ʾ
void LCD_DisplayOff(void)
{      
    LCD_WriteReg(0x07, 0x0);//�ر���ʾ 
} 
//��������
//Color:Ҫ���������ɫ
void LCD_Clear(alt_u16 Color)
{
    alt_u32 index=0;      
    LCD_SetCursor(0x00,0x0000);//���ù��λ�� 
    LCD_WriteRAM_Prepare();     //��ʼд��GRAM        
    for(index=0;index<76800;index++)
    {
        LCD_WR_DATA(Color);    
    }
} 
// LCD show gray
void LCD_Gray(void)
{
    alt_u32 point_index=0;      
    alt_u32 row_index=0;      
    alt_u32 block_index=0;      
    alt_u16 gray=0X1F;
    alt_u16 color;
    
    LCD_SetCursor(0x00,0x0000);//���ù��λ�� 
    LCD_WriteRAM_Prepare();     //��ʼд��GRAM        
    for(row_index=0;row_index<240;row_index++)
    {
        for(block_index=0;block_index<64;block_index++)
        {
            for(point_index=0;point_index<5;point_index++)
            {
                color = ((gray>>1) << 11)|(gray << 5)|(gray>>1);
                LCD_WR_DATA(color);
            }
			gray++;
			gray &= 0x3F;
        }
    }
} 

//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(alt_u16 Xpos, alt_u16 Ypos)
{
#ifdef USE_HORIZONTAL
    if(DeviceCode==0X8989)
    {
        LCD_WriteReg(0X4E, Ypos);
        LCD_WriteReg(0X4F, 319-Xpos);
    }else
    {
        LCD_WriteReg(R32, /*239-*/Ypos);
        LCD_WriteReg(R33, /*319-*/Xpos);
    }                              
#else
    if(DeviceCode==0X8989)
    {
        LCD_WriteReg(0X4E, Xpos);
        LCD_WriteReg(0X4F, Ypos);
    }else
    {
        LCD_WriteReg(R32, Xpos);
        LCD_WriteReg(R33, Ypos);
    }                           
#endif
}  
//����
//x:0~239
//y:0~319
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(alt_u16 x,alt_u16 y)
{
    LCD_SetCursor(x,y);//���ù��λ�� 
    LCD_WR_REG(R34);//��ʼд��GRAM
    LCD_WR_DATA(POINT_COLOR); 
}


//��ָ�����������ָ����ɫ
//�����С:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(alt_u16 xsta,alt_u16 ysta,alt_u16 xend,alt_u16 yend,alt_u16 color)
{          
    alt_u16 i,j;
    alt_u16 xlen=0;
#ifdef USE_HORIZONTAL
    xlen=yend-ysta+1;      
    for(i=xsta;i<=xend;i++)
    {
        LCD_SetCursor(i,ysta);      //���ù��λ�� 
        LCD_WriteRAM_Prepare();     //��ʼд��GRAM    
        for(j=0;j<xlen;j++)
            LCD_WR_DATA(color);//���ù��λ��    
    }
#else
    xlen=xend-xsta+1;      
    for(i=ysta;i<=yend;i++)
    {
        LCD_SetCursor(xsta,i);      //���ù��λ�� 
        LCD_WriteRAM_Prepare();     //��ʼд��GRAM    
        for(j=0;j<xlen;j++)
            LCD_WR_DATA(color);//���ù��λ��      
    }
#endif                              
}
/*===========================================================================
** ��������: LCD_reset()
** ��������: ��λLCD��ע�⣬��ʱ�����ǰ������delay()������ֵ��С
============================================================================*/
void LCD_reset(void)
{
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_REST_BASE,1);
    delay_ms(1);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_REST_BASE,0);
    delay_ms(10);
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_REST_BASE,1);
    delay_ms(50);
}

void LCD_Init(void)
{   //unsigned int DeviceCode;
	delay_ms(100);

//    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(LVC245_DIR_BASE,1); //����LVC245��ʹ���ݴ�FPGA�����TFT
//    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,0);
    LCD_WriteReg(0x0000,0x0001);
    delay_ms(5); // delay 50 ms
    DeviceCode = LCD_ReadReg(0x0000);
    printf(" LCD ID:%x\n",DeviceCode); //��ӡLCD ID

   // if(DeviceCode==0x9320||DeviceCode==0x9300)
    //{
    	LCD_WriteReg(0x00,0x0000);
        LCD_WriteReg(0x01,0x0100);  //Driver Output Contral.
        LCD_WriteReg(0x02,0x0700);  //LCD Driver Waveform Contral.
        LCD_WriteReg(0x03,0x1038);  //Entry Mode Set.
        //LCD_WriteReg(0x03,0x1028);    //Entry Mode Set.

        LCD_WriteReg(0x04,0x0000);  //Scalling Contral.
        LCD_WriteReg(0x08,0x0202);  //Display Contral 2.(0x0207)
        LCD_WriteReg(0x09,0x0000);  //Display Contral 3.(0x0000)
        LCD_WriteReg(0x0a,0x0000);  //Frame Cycle Contal.(0x0000)
        LCD_WriteReg(0x0c,(1<<0));  //Extern Display Interface Contral 1.(0x0000)
        LCD_WriteReg(0x0d,0x0000);  //Frame Maker Position.
        LCD_WriteReg(0x0f,0x0000);  //Extern Display Interface Contral 2.
        delay_ms(50);
        LCD_WriteReg(0x07,0x0101);  //Display Contral.
        delay_ms(50);
/*
        LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4)); //Power Control 1.(0x16b0)
        LCD_WriteReg(0x11,0x0007);                              //Power Control 2.(0x0001)
        LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));                //Power Control 3.(0x0138)
        LCD_WriteReg(0x13,0x1C00);                              //Power Control 4.
        LCD_WriteReg(0x29,0x000C);                              //Power Control 7.
*/
        LCD_WriteReg(0x10,0x0000); 		//Power Control 1.(0x16b0)
        LCD_WriteReg(0x11,0x0007);                              //Power Control 2.(0x0001)
        LCD_WriteReg(0x12,0x0000);                //Power Control 3.(0x0138)
        LCD_WriteReg(0x13,0x0000);                              //Power Control 4.
        delay_ms(200);
        LCD_WriteReg(0x10,0x17B0);	//(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4)); //Power Control 1.(0x16b0)
        LCD_WriteReg(0x11,0x0037);                              //Power Control 2.(0x0001)
        delay_ms(50);
        LCD_WriteReg(0x12,0x013E);	//(1<<8)|(1<<4)|(0<<0));                //Power Control 3.(0x0138)
        delay_ms(50);
        LCD_WriteReg(0x13,0x1C00);                              //Power Control 4.
        LCD_WriteReg(0x29,0x000C);                              //Power Control 7.
        delay_ms(50);

        LCD_WriteReg(0x20,0x0000); //
        LCD_WriteReg(0x21,0x0000); //

        // ----------- Adjust the Gamma Curve ----------//
        LCD_WriteReg(0x0030, 0x0007);
        LCD_WriteReg(0x0031, 0x0403);
        LCD_WriteReg(0x0032, 0x0404);
        LCD_WriteReg(0x0035, 0x0002);
        LCD_WriteReg(0x0036, 0x0707);
        LCD_WriteReg(0x0037, 0x0606);
        LCD_WriteReg(0x0038, 0x0106);
        LCD_WriteReg(0x0039, 0x0007);
        LCD_WriteReg(0x003C, 0x0700);
        LCD_WriteReg(0x003D, 0x0707);

        //LCD_WriteReg(0x2b,(1<<14)|(1<<4));
        LCD_WriteReg(0x50,0x0000);   //Set X Star
        //ˮƽGRAM��ֹλ��Set X End.
        LCD_WriteReg(0x51,0x00EF); //Set Y Star
        LCD_WriteReg(0x52,0x0000);   //Set Y End.t.
        LCD_WriteReg(0x53,0x013F); //

        LCD_WriteReg(0x60,0x2700);  //Driver Output Control.
        LCD_WriteReg(0x61,0x0001);  //Driver Output Control.
        LCD_WriteReg(0x6a,0x0000);  //Vertical Srcoll Control.

        LCD_WriteReg(0x80,0x0000);  //Display Position? Partial Display 1.
        LCD_WriteReg(0x81,0x0000);  //RAM Address Start? Partial Display 1.
        LCD_WriteReg(0x82,0x0000);  //RAM Address End-Partial Display 1.
        LCD_WriteReg(0x83,0x0000);  //Displsy Position? Partial Display 2.
        LCD_WriteReg(0x84,0x0000);  //RAM Address Start? Partial Display 2.
        LCD_WriteReg(0x85,0x0000);  //RAM Address End? Partial Display 2.

        LCD_WriteReg(0x90,0x0010);	//(0<<7)|(16<<0));  //Frame Cycle Contral.(0x0013)
        LCD_WriteReg(0x92,0x0000);  //Panel Interface Contral 2.(0x0000)
        LCD_WriteReg(0x93,0x0003);  //Panel Interface Contral 3.
        LCD_WriteReg(0x95,0x0110);  //Frame Cycle Contral.(0x0110)
        LCD_WriteReg(0x97,0x0000);	//(0<<8));  //
        LCD_WriteReg(0x98,0x0000);  //Frame Cycle Contral.
        LCD_WriteReg(0x07,0x0173);  //(0x0173)
  //  }else
   // printf(" LCD IS NOT ILI9320!" );
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(alt_u16 x1, alt_u16 y1, alt_u16 x2, alt_u16 y2)
{
    alt_u16 t; 
    int xerr=0,yerr=0,delta_x,delta_y,distance; 
    int incx,incy,uRow,uCol; 

    delta_x=x2-x1; //������������ 
    delta_y=y2-y1; 
    uRow=x1; 
    uCol=y1; 
    if(delta_x>0)incx=1; //���õ������� 
    else if(delta_x==0)incx=0;//��ֱ�� 
    else {incx=-1;delta_x=-delta_x;} 
    if(delta_y>0)incy=1; 
    else if(delta_y==0)incy=0;//ˮƽ�� 
    else{incy=-1;delta_y=-delta_y;} 
    if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
    else distance=delta_y; 
    for(t=0;t<=distance+1;t++ )//������� 
    {  
        LCD_DrawPoint(uRow,uCol);//���� 
        xerr+=delta_x ; 
        yerr+=delta_y ; 
        if(xerr>distance) 
        { 
            xerr-=distance; 
            uRow+=incx; 
        } 
        if(yerr>distance) 
        { 
            yerr-=distance; 
            uCol+=incy; 
        } 
    }  
}    
//������
void LCD_DrawRectangle(alt_u16 x1, alt_u16 y1, alt_u16 x2, alt_u16 y2)
{
    LCD_DrawLine(x1,y1,x2,y1);
    LCD_DrawLine(x1,y1,x1,y2);
    LCD_DrawLine(x1,y2,x2,y2);
    LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(alt_u16 x0,alt_u16 y0,alt_u8 r)
{
    int a,b;
    int di;
    a=0;b=r;      
    di=3-(r<<1);             //�ж��¸���λ�õı�־
    while(a<=b)
    {
        LCD_DrawPoint(x0-b,y0-a);             //3           
        LCD_DrawPoint(x0+b,y0-a);             //0           
        LCD_DrawPoint(x0-a,y0+b);             //1       
        LCD_DrawPoint(x0-b,y0-a);             //7           
        LCD_DrawPoint(x0-a,y0-b);             //2             
        LCD_DrawPoint(x0+b,y0+a);             //4               
        LCD_DrawPoint(x0+a,y0-b);             //5
        LCD_DrawPoint(x0+a,y0+b);             //6 
        LCD_DrawPoint(x0-b,y0+a);             
        a++;
        //ʹ��Bresenham�㷨��Բ     
        if(di<0)di +=4*a+6;   
        else
        {
            di+=10+4*(a-b);   
            b--;
        } 
        LCD_DrawPoint(x0+a,y0+b);
    }
} 
//��ָ��λ����ʾһ���ַ�
//x:0~234
//y:0~308
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
//��ָ��λ����ʾһ���ַ�
//x:0~234
//y:0~308
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(alt_u16 x,alt_u16 y,alt_u8 num,alt_u8 size,alt_u8 mode)
{  
#ifdef USE_HORIZONTAL
#define MAX_CHAR_POSX 312
#define MAX_CHAR_POSY 232 
#else     
#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 312
#endif 
    alt_u8 temp;
    alt_u8 pos,t;
    alt_u16 x0=x;
    alt_u16 colortemp=POINT_COLOR;

    if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;     
    //���ô���         

    num=num-' ';//�õ�ƫ�ƺ��ֵ
    if(!mode) //�ǵ��ӷ�ʽ
    {
        for(pos=0;pos<size;pos++)
        {
            if(size==12)temp=asc2_1206[num][pos];//����1206����
            else temp=asc2_1608[num][pos];       //����1608����
            for(t=0;t<size/2;t++)
            {                 
                if(temp&0x01)POINT_COLOR=colortemp;
                else POINT_COLOR=BACK_COLOR;
                LCD_DrawPoint(x,y); 
                temp>>=1; 
                x++;
            }
            x=x0;
            y++;
        }   
    }else//���ӷ�ʽ
    {
        for(pos=0;pos<size;pos++)
        {
            if(size==12)temp=asc2_1206[num][pos];//����1206����
            else temp=asc2_1608[num][pos];       //����1608����
            for(t=0;t<size/2;t++)
            {                 
                if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����     
                temp>>=1; 
            }
        }
    }
    POINT_COLOR=colortemp;                    
}   
//m^n����
alt_u32 mypow(alt_u8 m,alt_u8 n)
{
    alt_u32 result=1;    
    while(n--)result*=m;    
    return result;
}            
//��ʾ2������
//x,y :�������  
//len :���ֵ�λ��
//size:�����С
//color:��ɫ
//num:��ֵ(0~4294967295);  
void LCD_ShowNum(alt_u16 x,alt_u16 y,alt_u32 num,alt_u8 len,alt_u8 size)
{           
    alt_u8 t,temp;
    alt_u8 enshow=0;                           
    for(t=0;t<len;t++)
    {
        temp=(num/mypow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
                continue;
            }else enshow=1; 
             
        }
        LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
    }
} 
//��ʾ2������
//x,y:�������
//size:�����С
//mode:ģʽ   0,���ģʽ;1,����ģʽ
//num:��ֵ(0~99);  
void LCD_Show2Num(alt_u16 x,alt_u16 y,alt_u16 num,alt_u8 len,alt_u8 size,alt_u8 mode)
{           
    alt_u8 t,temp;                         
    for(t=0;t<len;t++)
    {
        temp=(num/mypow(10,len-t-1))%10;
        LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode); 
    }
} 
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
void LCD_ShowString(alt_u16 x,alt_u16 y,const char *p)
{         
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;LCD_Clear(WHITE);}
        LCD_ShowChar(x,y,*p,16,0);
        x+=8;
        p++;
    }  
}
void Address_set(uint x1,uint y1,uint x2,uint y2)
{
    LCD_WR_REG(0x0020);LCD_WR_DATA(x1);    //����X����λ��
    LCD_WR_REG(0x0021);LCD_WR_DATA(y1);   //����Y����λ��
    LCD_WR_REG(0x0050);LCD_WR_DATA(x1);   //��ʼX
    LCD_WR_REG(0x0052);LCD_WR_DATA(y1);    //��ʼY
    LCD_WR_REG(0x0051);LCD_WR_DATA(x2);   //����X
    LCD_WR_REG(0x0053);LCD_WR_DATA(y2);   //����Y
    LCD_WR_REG(0x0022);                            
}
