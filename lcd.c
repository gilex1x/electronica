/*
Este es el programa de la primera clase
*/
/* Fuses: PLL1,PLL2,PLL3,PLL4,PLL5,PLL6,PLL10,PLL12,CPUDIV1,CPUDIV2
 Fuses: CPUDIV3,CPUDIV4,NOUSBDIV,USBDIV,XT,XTPLL,EC_IO,EC,ECPLL_IO
 Fuses: ECPLL,INTRC_IO,INTRC,INTXT,INTHS,HS,HSPLL,NOFCMEN,FCMEN
 Fuses: NOIESO,IESO,PUT,NOPUT,NOBROWNOUT,BROWNOUT_SW,BROWNOUT_NOSL
 Fuses: BROWNOUT,BORV45,BORV43,BORV27,BORV21,NOVREGEN,VREGEN,NOWDT
 Fuses: WDT,WDT1,WDT2,WDT4,WDT8,WDT16,WDT32,WDT64,WDT128,WDT256
 Fuses: WDT512,WDT1024,WDT2048,WDT4096,WDT8192,WDT16384,WDT32768
 Fuses: CCP2B3,CCP2C1,NOPBADEN,PBADEN,NOLPT1OSC,LPT1OSC,NOMCLR,MCLR
 Fuses: NOSTVREN,STVREN,NOLVP,LVP,ICSP1,ICSP2,NOXINST,XINST,DEBUG
 Fuses: NODEBUG,PROTECT,NOPROTECT,CPB,NOCPB,CPD,NOCPD,WRT,NOWRT,WRTC
 Fuses: NOWRTC,WRTB,NOWRTB,WRTD,NOWRTD,EBTR,NOEBTR,EBTRB,NOEBTRB
*/ 

#include <18F4550.h>
#fuses HS,NOWDT,NOPROTECT,NOCPD,PUT,NOMCLR,NOLVP,NODEBUG
#use delay(clock=20000000)
#include <stdlib.h>
#include <math.h>
#define LCD_E PIN_E2 //PIN 6 DEL LCD
#define LCD_CK PIN_E1 // AL 74S164
#define LCD_DAT PIN_E0 //AL 74S164
#include <LCD4x20_3PIN.c>
//#include <KBD18F.c>
//#include <DS1307.c>
#use fast_io(B)



//Definimos el nombre del pin especificado

// tipo_registro nombre  valor 


//Definimos el metodo principal
//configurar es establecer las entradas y salidas de los puertos

void main(){
   //set_tris_A(0X1F);//0001 1111 || 1000 1111
   set_tris_B(0X00);// 0000 0000
   set_tris_E(0x00);
   lcd_init();//Iniciamos la libreria del lcd
   output_E(0x00);
   lcd_putc('\f');//Limpiamos la salida del lcd
   lcd_gotoxy(1,1);//Le damos las coordenadas del lcd
   lcd_putc("  BIENVENIDO\n  ARQUITECTURA");
   delay_ms(5000);
   lcd_putc('\f');//Limpiamos la salida del lcd
   lcd_gotoxy(1,1);//Le damos las coordenadas del lcd
   lcd_putc("  GILBERTO\n SANTAMARIA");
   delay_ms(5000);
   lcd_putc('\f');
   
   
   
   
   
   
}
