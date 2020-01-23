/**************************************************************************
**�ļ����ƣ�stm_1602.c  for  STM32
**by zyy  2013-12-02
**************************************************************************/
#include "stm32f10x.h"
#include "1602.h"

#define LCD_RS_1 GPIOE->BSRR=GPIO_Pin_0 //PE.0--(LCD)RS
#define LCD_RS_0 GPIOE->BRR =GPIO_Pin_0
#define LCD_RW_1 GPIOE->BSRR=GPIO_Pin_1 //PE.1--(LCD)RW
#define LCD_RW_0 GPIOE->BRR =GPIO_Pin_1
#define LCD_EN_1 GPIOE->BSRR=GPIO_Pin_2 //PE.2--(LCD)E
#define LCD_EN_0 GPIOE->BRR =GPIO_Pin_2
#define DATAOUT  GPIOD->ODR             //PD[0..7]--(LCD)D0~D7

extern void delay_nms(unsigned long n);
extern void delay_nus(unsigned long n);

void LCD_Writecmd(uchar cmd);
void LCD_Writedata(uchar dat);
void LCD_write_char(uchar row, uchar col, char ch);
void LCD_write_str(uchar x, uchar y, char str[]);
void LCD_clear(void);
void LCD_Init(void);
//��ʱn us
void delay_nus(unsigned long n);
void delay_nms(unsigned long n);
void A1602_GPIO_Configuration(void);
void LCD_Init(void);

/**************************************************************************
**�ļ����ƣ�stm_1602.c  for  STM32
**by zyy  2013-12-02
**************************************************************************/



/*********************************************************************
*��    �ƣ�LCD_Writecmd()
*��    �ܣ�дָ�LCD1602,ָ������ռһ���ֽ�
*��ڲ�����cmd:��д���ָ��
*���ڲ�������
*********************************************************************/
void LCD_Writecmd(uchar cmd)
{
    LCD_RS_0;    //��ͬһ���Ĵ���������д�룬�м���ʱһ��
    delay_nus(1);
    LCD_RW_0;
    delay_nus(1);

    LCD_EN_1;
    DATAOUT = cmd;
    delay_nus(300);//��Ҫ����ʱ
    LCD_EN_0;    //�½��أ�LCD1602��ʼ����
}
/*********************************************************************
*��    �ƣ�LCD_Writedata()
*��    �ܣ�дһ�ֽ����ݵ�LCD1602
*��ڲ�����dat���޷����ֽ����ͣ�0~255  ��������ASCII���ַ�
*���ڲ�������
*********************************************************************/
void LCD_Writedata(uchar dat)
{
    LCD_RS_1;
    delay_nus(1);
    LCD_RW_0;
    delay_nus(1);
    LCD_EN_1;  //������
    DATAOUT = dat;
    delay_nus(300); //����Ҫ����ʱ�������ԣ���ʱ300us���ϲſ���
    LCD_EN_0;       //�½��أ���ʼд����Ч����
}
/*********************************************************************
*��  �ܣ���ָ��λ����ʾһ���ַ�
*��ڲ�����y:�� 0��1        x:�У�0~15��ch������ʾ���ַ�
*********************************************************************/
void LCD_write_char(uchar x, uchar y, char ch)
{
    if (y == 0)
    {
        LCD_Writecmd(0x80 + x);
    }
    else
    {
        LCD_Writecmd(0xC0 + x);
    }
    LCD_Writedata(ch);
}
/*********************************************************************
*��    �ƣ�LCD_write_str()
*��    �ܣ�ʹLCD1602��ʾһ���ַ���
*��ڲ�����y:�� 0��1        x:�У�0~15��str[]:����ʾ���ַ���
*���ڲ�������
*********************************************************************/
void LCD_write_str(uchar x, uchar y, char str[])
{
    uchar i = 0;
    if (y == 0)
    {
        LCD_Writecmd(0x80 + x);
    }
    else
    {
        LCD_Writecmd(0xC0 + x);
    }
    while (str[i] != '\0')
    {
        LCD_Writedata(str[i]);
        ++i;
    }
}
/******************************************************************/
/*                      ��������                                */
/******************************************************************/
void LCD_clear(void)
{
    LCD_Writecmd(0x01);
    delay_nms(5);
}

/*********************************************************************
*��    �ƣ�LCD_Init()
*��    �ܣ���ʼ��LCD1602
*��ڲ�������
*���ڲ�������
*�������0x38:16*2��ʾ��5*&������ʾ�ַ���8λ����;ָ��ִ��ʱ��40us
*          0x0C:����ʾ���ع��   40us
*          0x08:����ʾ���ع��   40us
*          0x0D:�ַ���˸���ع�꣬�����趨λ�ã���˸����0.4ms����
*          0x0F:�ַ���˸�������
*          0x06:д�������Զ����ƹ�꣬��ͨ���Σ�����������ʾ  40us
*          0x04:д�������Զ����ƹ�꣬���Դ���������ʾ  40us
*          0x01:�����ʾ���ݣ�������  1.64ms
*          0x02:ʹ��껹����ʼλ��   1.64ms
*          0x18:��Ļ�������ַ�ͬʱ����һ���ʺϹ�����ʾ 40us
*          0x1C:��Ļ�������ַ�ͬʱ����һ���ʺϹ�����ʾ 40us
*********************************************************************/
void LCD_Init(void)
{
    delay_nms(100);           //��ʱ20ms
    LCD_Writecmd(0x38);  //16*2��ʾ��5*7����8λ����
    delay_nms(10);
    LCD_Writecmd(0x38);  //16*2��ʾ��5*7����8λ����
    delay_nms(10);
    LCD_Writecmd(0x38);  //16*2��ʾ��5*7����8λ����
    delay_nms(10);
    LCD_Writecmd(0x38);  //16*2��ʾ��5*7����8λ����
    delay_nms(10);
    LCD_Writecmd(0x08);  //�ȹ���ʾ������ʾ
    delay_nms(10);
    LCD_Writecmd(0x01);  //���LCD����ʾ����
    delay_nms(10);
    LCD_Writecmd(0x06);  //�Զ����ƹ��,0x04Ϊ���ƹ��
    delay_nms(10);
    LCD_Writecmd(0x0c);  //��ʾ�����ع��;0x08Ϊ����ʾ
    delay_nms(10);
}
//��ʱn us
void delay_nus(unsigned long n)
{
    unsigned long j;
    while (n--)
    {
        j = 8;
        while (j--);
    }
}
//��ʱn ms
void delay_nms(unsigned long n)
{
    while (n--)
    {
        delay_nus(1100);
    }
}
/******************************************************************/
/*                      GPIO���ú���                            */
/******************************************************************/

void A1602_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); //�����˿�D��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //PD0~PD7 ���������������©�����,������������������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //�����˿�E��ʱ��
    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
    //PE.0~2 ���������������©�����,������������������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}





