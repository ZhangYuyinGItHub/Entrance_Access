#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
#include "stm32f10x.h"

#define IIC_GPIO       GPIOC
#define IIC_SCL        PCout(8) //SCL
#define IIC_SDA_OUT    PCout(9) //SDA   
#define IIC_SDA_IN     PCin(9)  //����SDA 

//IO��������
#define SDA_IN()  {IIC_GPIO->CRH&=0XFFFFFF0F;IIC_GPIO->CRH|=8<<4;}
#define SDA_OUT() {IIC_GPIO->CRH&=0XFFFFFF0F;IIC_GPIO->CRH|=3<<4;}

//IO��������
//#define IIC_SCL    PBout(8) //SCL
//#define IIC_SDA_OUT    PBout(9) //SDA
//#define IIC_SDA_IN   PBin(9)  //����SDA

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);               //����IIC��ʼ�ź�
void IIC_Stop(void);                //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);         //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
void IIC_Ack(void);                 //IIC����ACK�ź�
void IIC_NAck(void);                //IIC������ACK�ź�

#endif
















