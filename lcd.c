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
#define LED_RED PIN_A1
#define LED_YELLOW PIN_A2
#define LED_GREEN PIN_A3
#include <LCD4x20_3PIN.c>
#include <KBD18F.c>
#include <DS1307.c>
#include <24C512.C>
#ROM 0xf00000 = {0x3412}//Definimos la clave en la POSICION DE MEMORIA del micro EEPROM
//#use     i2c (MASTER, SDA=PIN_D7, SCL=PIN_D6,slow) //Define los puertos cx al DS1307

long auxsegundos,segundos;
int clave[4],a,b,i; 
int check1,check2; // datos para comparar el registro de nuevas claves
int datointerno[4],datoexterno[4];
char datom;
short bandera;
//mi clave 4559
//LEER EL TECLADO
void teclado(){
   output_high(LED_YELLOW);
   auxsegundos=0;
   segundos=0;
   b=6;
   lcd_putc('\f');
   for(i=0;i<4;i++){
      do{
         datom = kbd_getc();//Escanea el teclado
         delay_ms(60);
         if(datom != '\0'){//verificamos que el dato sea valido
            
            switch (i+1){
               
               case 1:
                  clave[0]= datom - 0x30;
                  swap(clave[0]);
                  lcd_gotoxy(6,2);
                  lcd_putc("*");
                  delay_ms(60);
                  break;
                  
               case 2:
                  clave[1]= datom - 0x30;
                  clave[0]= clave[1]+ clave[0];
                  lcd_putc("*");
                  delay_ms(60);
                  break;
                  
               case 3:
                  clave[2]= datom - 0x30;
                  swap(clave[2]);
                  lcd_putc("*");
                  delay_ms(60);
                  break;
                  
               case 4:
                  clave[1]= datom - 0x30;
                  clave[1]= clave[1]+ clave[2];
                  lcd_putc("*");
                  delay_ms(60);
                  break;
               
            }
         i++;
         delay_ms(500);
         auxsegundos=0;
         segundos=0;
         }
         auxsegundos++;    
         if(auxsegundos>20){
            segundos++;
            auxsegundos=0;
         }
      }while(segundos<6 && i<4);
      clave[i]='#';
      lcd_gotoxy(b,1);
      lcd_putc("*");
      b++;
      auxsegundos=0;
      segundos=0;
   }
   output_low(LED_YELLOW);
}
//LEER MEMORIA INTERNA Y EXTERNA
void leer_interna(){
   for (i=0;i<2;i++){
      datointerno[i]=read_eeprom(i);
      delay_ms(1);
   }
}

void leer_externa(){
   for(i=0;i<4;i++){
      datoexterno[i]= read_ext_eeprom(i);
      delay_ms(10);
   }
   
}
//ESCRIBIR MEMORIA INTERNA
 void escribir_interna(){
   for (i=0;i<2;i++)
   {
      write_eeprom(i,clave[i]);
      delay_ms(5);
      //a++;
   }
 } 
 //ESCRIBIR MEMORIA EXTERNA

 void escribir_externa(){
   for(i=0;i<2;i++)
   {
      write_ext_eeprom(i,clave[i]);
      delay_ms(5);
      //a++;
   }
 }
//METODO DE UN DIGITO

void digito(){
   output_high(LED_YELLOW);
   bandera=false;
   auxsegundos=0;
   segundos=0;
    do{
        datom = kbd_getc();//Escanea el teclado
        delay_ms(60);
        if(datom != '\0'){//verificamos que el dato sea valido
            lcd_gotoxy(1,1);
            lcd_putc('\f');
            lcd_gotoxy(8,1);
            lcd_putc(datom);
            delay_ms(2000);
            datom=datom - 0x30;//le quitamos el ASCII
            bandera = true;
         }
         auxsegundos++;    
         if(auxsegundos>20){
            segundos++;
            auxsegundos=0;
         }
      }while(segundos<6 && !bandera);
   auxsegundos=0;
   segundos=0;
   output_low(LED_YELLOW);
}
//METODO PRINCIPAL
void main(){
   //set_tris_A(0X1F);//0001 1111 || 1000 1111
   #zero_ram;
   set_tris_B(0X00);// 0000 0000
   set_tris_A(0x00);//usamos para losleds
   set_tris_E(0x00);
   output_low(LED_RED);
   output_low(LED_YELLOW);
   output_low(LED_GREEN);
   lcd_init();//Iniciamos la libreria del lcd
   output_E(0x00);
   lcd_putc('\f');//Limpiamos la salida del lcd
   lcd_gotoxy(1,1);//Le damos las coordenadas del lcd
   lcd_putc("  BIENVENIDO\n ARQUITECTURA");
   delay_ms(5000);
   lcd_putc("\f  GILBERTO\n SANTAMARIA");
   delay_ms(5000);
   lcd_putc("\fIngrese clave");
   delay_ms(1000);
   init_ext_eeprom();//Iniciamos la lectura de la memoria externa
   //LEEMOS LAS CLAVES DE LAS MEMORIAS
   leer_interna();
   leer_externa();
   teclado();
   if(clave[0]==0x45 & clave[1]==0x59){
      output_high(LED_GREEN);
      lcd_gotoxy(1,1);
      lcd_putc("\f  CLAVE\n CORRECTA");
      delay_ms(3000);
      output_low(LED_GREEN);
menu:
      lcd_putc("\f   BIENVENIDO\n ADMINISTRADOR");
      delay_ms(3000);
      lcd_putc("\fESTE ES EL MENU \n DEL DISENADOR");
      delay_ms(3000);
      lcd_putc("\f 1->GILBERTO \n 2->SANTAMARIA");
      delay_ms(3000);
      lcd_putc("\f 3->SALIR");
      delay_ms(3000);
      lcd_putc("\fDIGITE OPCION\n 1, 2 O 3");
      delay_ms(2000);
      digito();
      //revisamos el digito ingresado
      if(datom==0x01){
         goto gilberto;
      }
      if(datom==0x02){
         goto santamaria;
      }
      if(datom==0x03){
      //SALIR
         lcd_gotoxy(1,1);
         lcd_putc("\fGRACIAS POR USAR\n   EL PROGRAMA");
         delay_ms(2000);
         reset_cpu();
      }
         output_high(LED_RED);
         lcd_gotoxy(1,1);
         lcd_putc("\f OPCION NO\n VALIDA");
         goto menu;
   }
   if(clave[0]==datoexterno[0] & (clave[1]==datoexterno[1])){//INICIO MENU DE GILBERTO
 gilberto:
     // a=0;//me indica la posicion de la memoria que voy a leer
      lcd_gotoxy(1,1);
      lcd_putc("\f MENU DE \n GILBERTO");
      delay_ms(3000);
      lcd_putc("\f  1-> PARA:\n   CAMBIAR CLAVE");
      delay_ms(3000);
      lcd_putc("\f   2-> PARA:\n   FECHA Y HORA");
      delay_ms(3000);
      lcd_putc("\f   3-> PARA:\n   SALIR");
      delay_ms(2000);
      digito();
      if(datom==0x01){
         lcd_gotoxy(1,1);
         lcd_putc("\fDIGITE NUEVA\n CLAVE");
         delay_ms(2000);
         teclado();
         check1= clave[0];
         check2=clave[1];
         lcd_gotoxy(1,1);
         lcd_putc("\fDIGITE OTRA VEZ\n SU CLAVE");
         delay_ms(2000);
         teclado();
         if(clave[0]==check1 & clave[1]==check2){
            output_high(LED_GREEN);
            lcd_gotoxy(1,1);
            lcd_putc("\fCLAVE CAMBIADA \nCON EXITO");
            escribir_externa();
            delay_ms(2000);
            output_low(LED_GREEN);
            goto gilberto;
         }else{
            output_high(LED_RED);
            lcd_gotoxy(1,1);
            lcd_putc("\fCLAVE ERRONEA");
            delay_ms(2000);
            output_low(LED_RED);
            goto gilberto;
         }
         
      }else if(datom==0x02){
         output_high(LED_YELLOW);
         lcd_gotoxy(1,1);
         lcd_putc("\fEN CONSTRUCCION");
         delay_ms(2000);
         output_low(LED_YELLOW);
         goto gilberto;
      }else if(datom==0x03){
         goto menu;
      }else{
         output_high(LED_RED);
         lcd_gotoxy(1,1);
         lcd_putc("\n ERROR MENU\nOPCION NO VALIDA");
         delay_ms(2000);
         output_low(LED_RED);
         goto gilberto;
      }
 
   }/*FIN MENU DE GILBERTO*/
   if(clave[0]==datointerno[0] & clave[1]==datointerno[1]){//INICIO MENU DE SANTAMARIA
 santamaria:
     // a=0;//me indica la posicion de la memoria que voy a leer
      lcd_gotoxy(1,1);
      lcd_putc("\f MENU DE \nSANTAMARIA");
      delay_ms(3000);
      lcd_putc("\f  1-> PARA:\n   CAMBIAR CLAVE");
      delay_ms(3000);
      lcd_putc("\f   2-> PARA:\n   FECHA Y HORA");
      delay_ms(3000);
      lcd_putc("\f   3-> PARA:\n   SALIR");
      delay_ms(2000);
      digito();
      if(datom==0x01){
         lcd_gotoxy(1,1);
         lcd_putc("\fDIGITE NUEVA\n CLAVE");
         delay_ms(2000);
         teclado();
         check1= clave[0];
         check2=clave[1];
         lcd_gotoxy(1,1);
         lcd_putc("\fDIGITE OTRA VEZ\n SU CLAVE");
         delay_ms(2000);
         teclado();
         if(clave[0]==check1 & clave[1]==check2){
            output_high(LED_GREEN);
            escribir_interna();
            lcd_gotoxy(1,1);
            lcd_putc("\fCLAVE CAMBIADA \nCON EXITO");
            delay_ms(2000);
            output_low(LED_GREEN);
            goto santamaria;
         }else{
            output_high(LED_RED);
            lcd_gotoxy(1,1);
            lcd_putc("\fCLAVE ERRONEA");
            delay_ms(2000);
            output_low(LED_RED);
            goto santamaria;
         }
         
      }else if(datom==0x02){
         output_high(LED_YELLOW);
         lcd_gotoxy(1,1);
         lcd_putc("\fEN CONSTRUCCION");
         delay_ms(2000);
         output_low(LED_YELLOW);
         goto gilberto;
      }else if(datom==0x03){
         goto menu;
      }else{
         output_high(LED_RED);
         lcd_gotoxy(1,1);
         lcd_putc("\n ERROR MENU\nOPCION NO VALIDA");
         delay_ms(2000);
         output_low(LED_RED);
         goto gilberto;
      }
 
   }/*FIN MENU DE SANTAMARIA*/
 
      output_high(LED_RED);
      lcd_gotoxy(1,1);
      lcd_putc("\f  CLAVE\n INCORRECTA");
      delay_ms(2000);
      output_low(LED_RED);
      reset_cpu();

}
