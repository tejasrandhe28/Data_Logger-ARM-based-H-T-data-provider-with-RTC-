#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "uart_declarations.h"
#include "defines.h"
#include "kpmdefines.h"
#include "kpm.h"
#include "LCD_declarations.h"
#include"delay.h"
#include <stdlib.h>
void rtc_init(void);
//#define SW 16
#define FOSC      12000000
#define CCLK  	  5*FOSC
#define PCLK  	  CCLK/4
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))
//define EINT0_LED 16
//u8 keyv;
 int flag;
void eint0_isr(void) __irq;
void Enable_EINT0(void);
void interrupt(void);

unsigned int count;
//s32 num=0,cnt=0;
// void rtc_init(void);

//main()
/*void interrupt()
  {
u32 keyv;

LCD_Init();
rtc_init();
InitKPM();
Enable_EINT0();
//SETBIT(IODIR0,SW);


PREINT=PREINT_VAL;

PREFRAC=PREFRAC_VAL;
CCR=0x01;
while(1)
count++;
} */
u8 ch;
void eint0_isr(void) __irq
{
  flag=1;
	//u8 ch;
		//while(1)
		//SCLRBIT(EXTINT,0);//clear flag
	/*Write_CMD_LCD(0x01);
			Write_str_LCD("1.HOUR 2.MIN 3.SEC 7.exit");
			Write_CMD_LCD(0xc0);
			keyv=keyscan();
			Write_DAT_LCD(keyv);
			delay_ms(1000);
			if(keyv==7)
			{
				Write_CMD_LCD(0x01);
					exit(0);
			}
		Write_CMD_LCD(0x01);
			cnt=0;
			switch(keyv)
			{
				case '1':do
					 { 
						 ch=keyscan();
							 Write_DAT_LCD(ch);
							 delay_ms(1000);
							 
							 if(ch>='0'&&ch<='9')
							 {
								 num=(num*10)+(ch-48);
									 cnt++;
							 }
							 else if(ch>='A')
							 {
								 break;
							 }
					 }while(cnt<2);
					 if(num>=0&&num<24)
					 {
						 HOUR=num;
					 }
					 break;
						 
				case'2': do
					 { 
						 ch=keyscan();
							 Write_DAT_LCD(ch);
							 delay_ms(1000);
							 
							 if(ch>='0'&&ch<='9')
							 {
								 num=(num*10)+(ch-48);
									 cnt++;
							 }
							 else if(ch>='A')
							 {
								 break;
							 }
					 }while(cnt<2);
					 if(num>0&&num<=60)
					 {
						 MIN=num;
					 }
					 break;
				case '3':do
					 { 
						 ch=keyscan();
							 Write_DAT_LCD(ch);
							 delay_ms(1000);
							 
							 if(ch>='0'&&ch<='9')
							 {
								 num=(num*10)+(ch-48);
									 cnt++;
							 }
							 else if(ch>='A')
							 {
								 break;
							 }
					 }while(cnt<2);
					 if(num>0&&num<=60)
					 {
						 SEC=num;
					 }
					 break;
				case '4':do
					 { 
						 ch=keyscan();
							 Write_DAT_LCD(ch);
							 delay_ms(1000);
							 
							 if(ch>='0'&&ch<='9')
							 {
								 num=(num*10)+(ch-48);
									 cnt++;
							 }
							 else if(ch>='A')
							 {
								 break;
							 }
					 }while(cnt<2);
					 if(num>0&&(num<=30||num<=31))
					 {
						 DOM=num;
					 }
					 break;
				case '5':do
					 { 
						 ch=keyscan();
							 Write_DAT_LCD(ch);
							 delay_ms(1000);
							 
							 if(ch>='0'&&ch<='9')
							 {
								 num=(num*10)+(ch-48);
									 cnt++;
							 }
							 else if(ch>='A')
							 {
								 break;
							 }
					 }while(cnt<2);
					 if(num>0&&num<=12)
					 {
						 MONTH=num;
					 }
					 break;
				case '6':do
					 { 
						 ch=keyscan();
							 Write_DAT_LCD(ch);
							 delay_ms(1000);
							 
							 if(ch>='0'&&ch<='9')
							 {
								 num=(num*10)+(ch-48);
									 cnt++;
							 }
							 else if(ch>='A')
							 {
								 break;
							 }
					 }while(cnt<4);
					 if(num>0)
					 {
						 YEAR=num;
					 }
					 break;
			}
			
		  
		//rtc_LCD();
		//EXTINT=0x08;
		//EXTINT=0x00;
		count=1;
			SSETBIT(EXTINT,1);
			VICVectAddr=0;
			delay_ms(500);
		rtc_LCD();
		UART_rtc();	 */
			//dummy write;
		//	exit(0);
	}
//	Write_str_LCD("exit isr");	
//}
	
void Enable_EINT0(void)
{
	CFGPIN(PINSEL0,7,FUNC4);				//	CFGPIN(PINSEL1,16,FUNC2);
	SETBIT(IODIR0,10);
		SSETBIT(VICIntEnable,16);
		VICVectCntl0=0x20|16;
		VICVectAddr0=(unsigned)eint0_isr;
		SCLRBIT(EXTINT,2);
		SETBIT(EXTMODE,2);
}
		//	SETBIT(EXTPOLAR,2);
		//	SSETBIT(VICIntEnable,14);
		//VICIntEnable=1<<17;
		//VICVectCntl0=0x20|17;
		//	VICVectAddr0=(unsigned)eint0_isr;
		//  EXTINT=0x00;
		// EXTMODE=0x03;


/*void rtc_init()

  {
  SEC=20; 
  MIN=00; 
  HOUR=8;
  DOM=19;
  MONTH=1;
  YEAR=24;
//day=enum weak(0);


} */


