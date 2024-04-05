#include <lpc214x.h>
#include "delay.h"
#include "defines.h"
#include "lcd.h"
#include "dht11.h"
#include "uart0.h"
#include "kpm.h"
#include "uart_declarations.h"
#include "interrupt.h"
#include"kpmdefines.h"
#include <stdlib.h>


#define FOSC      12000000

#define CCLK  	  5*FOSC

#define PCLK  	  CCLK/4

#define PREINT_VAL ((PCLK/32768)-1)

#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))
extern int flag;
s32 num=0,cnt=0;
u8 keyv;

int main (void)
{
	unsigned char humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum;
		Init_UART0();  
	LCD_Init();
		rtc_init();
		InitKPM();
		Enable_EINT0();
		PREINT=PREINT_VAL;

		PREFRAC=PREFRAC_VAL;

		CCR=0x01;
		Write_str_LCD("data logger"); 
	delay_ms(5000);
		Write_CMD_LCD(0x01);

		while(1)
		{	   
			//UART_rtc();
			rtc_LCD();
				dht11_request();
			dht11_response();
			humidity_integer = dht11_data();
			humidity_decimal = dht11_data();
			temp_integer = dht11_data();
			temp_decimal = dht11_data();
			checksum = dht11_data();
			if((humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum )
			{
				Write_str_LCD("Checksum Error\r\n");
			}
			else
			{
				Write_CMD_LCD(0x80);
				Write_str_LCD("H : ");
					Write_int_LCD(humidity_integer);
					Write_DAT_LCD('.');
					Write_int_LCD(humidity_decimal);
					Write_str_LCD(" % RH ");
					Write_CMD_LCD(0xC0);
				Write_str_LCD("T : ");
					Write_int_LCD(temp_integer);
					Write_DAT_LCD('.');
					Write_int_LCD(temp_decimal);
					Write_int_LCD(223);
				Write_str_LCD("C");
					delay_ms(1000);
					Write_CMD_LCD(0x01);
					Write_CMD_LCD(0xc0);
				Write_str_LCD("Checksum : ");
					Write_int_LCD(checksum);
					//delay_ms(100);
					//Write_CMD_LCD(0x01); 
					//UART_rtc();
					UART0_Tx_str("H : ");
				UART0_Tx_int(humidity_integer);
					UART0_Tx_char('.');
					UART0_Tx_int(humidity_decimal);
					//	UART0_Tx_str(" % RH ");
					UART0_Tx_char(' ');
					UART0_Tx_str("T : ");
				UART0_Tx_int(temp_integer);
					UART0_Tx_char('.');
					UART0_Tx_int(temp_decimal);
					/*	UART0_Tx_int(223);
						UART0_Tx_str("C");
						UART0_Tx_str("Checksum : ");
						UART0_Tx_int(checksum);	*/
					UART0_Tx_char(' ');
					UART_rtc();
					UART0_Tx_str("\r\n");
					delay_ms(1000);
				if(flag==1)
				{
						u8 ch;
							Write_CMD_LCD(0x01);
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
					flag=0; 
				} 
			}
		}
}
