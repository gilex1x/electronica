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
#use fast_io(B)
#define led1 pin_B0
#define led2 pin_B1
#define led3 pin_B2
#define led4 pin_B3
#define led5 pin_B4
#define led6 pin_B5
#define led7 pin_B6


//Definimos el nombre del pin especificado

// tipo_registro nombre  valor 


//Definimos el metodo principal
//configurar es establecer las entradas y salidas de los puertos

int i;
void main(){
   //set_tris_A(0X1F);//0001 1111 || 1000 1111
   set_tris_B(0X00);// 0000 0000
   
   for(i=0;i<20;i++){
      output_high(led1);
      delay_ms(200);
      output_high(led2);
      delay_ms(200);
      output_high(led3);
      delay_ms(200);
      output_low(led1);
      delay_ms(200);
      output_high(led4);
      delay_ms(200);
      output_low(led2);
      delay_ms(200);
      output_high(led5);
      delay_ms(200);
      output_low(led3);
      delay_ms(200);
      output_high(led6);
      delay_ms(200);
      output_low(led4);
      delay_ms(200);
      output_high(led7);
      delay_ms(200);
      output_low(led6);
      delay_ms(200);
      output_low(led5);
      delay_ms(200);
      output_high(led7);
      delay_ms(200);
      output_high(led6);
      delay_ms(200);
      output_high(led5);
      delay_ms(200);
      output_low(led7);
      delay_ms(200);
      output_high(led4);
      delay_ms(200);
      output_low(led6);
      delay_ms(200);
      output_high(led3);
      delay_ms(200);
      output_low(led5);
      delay_ms(200);
      output_high(led2);
      delay_ms(200);
      output_low(led4);
      delay_ms(200);
      output_high(led1);
      delay_ms(200);
      output_low(led3);
      delay_ms(200);
      output_low(led2);
      delay_ms(200);
   }

}


