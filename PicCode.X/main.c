#include "mcc_generated_files/mcc.h"

#include "variaveisGLobal1.h"
/* header file para as bibliotecas de XC8 */
#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pic18.h>


#define MAX_LENGTH_UART 32     // Max lenght of a string send or received with UART

volatile  float Vout=0;
volatile  float lux=0;
volatile char msg1[50];
volatile int dutyValue=0;

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();

void main(void){
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();   
    UARTSendString("Hey\r\n", MAX_LENGTH_UART);
    char RH_Decimal, RH_Integral, T_Decimal, T_Integral;
    char Checksum;
    char value[10];
    while (1){ 
        if (flag1){
            ADC_SelectChannel(AN0);
            ADC_StartConversion();
            Vout=  ADC_GetConversionResult()*0.00488;
            lux =500/(10.0*((5-Vout)/Vout));  
            sprintf(msg1,"FirstMQ6_%.2f\0",lux);
            UARTSendString(msg1,MAX_LENGTH_UART);
            flag1=0;
        }
        if (flag2){   
            sprintf(msg1,"SecondMQ_%d\0",PIR_GetValue());
            UARTSendString(msg1,MAX_LENGTH_UART);
            flag2=0;
        }
        if (flag3) {
            DHT11_Start(); /* send start pulse to DHT11 module */
            /* read 40-bit data from DHT11 module */
            RH_Integral = DHT11_ReadData(); /* read Relative Humidity's integral value */
            RH_Decimal = DHT11_ReadData(); /* read Relative Humidity's decimal value */
            T_Integral = DHT11_ReadData(); /* read Temperature's integral value */
            T_Decimal = DHT11_ReadData(); /* read Relative Temperature's decimal value */
            Checksum = DHT11_ReadData(); /* read 8-bit checksum value */         
            sprintf(msg1, "ThirdMQ_%d\0",T_Integral );
            UARTSendString(msg1, MAX_LENGTH_UART);
            flag3 = 0;
        }
        if (flag4) {
            sprintf(msg1, "FourthdMQ_%d\0",RH_Integral);
            UARTSendString(msg1, MAX_LENGTH_UART);
            flag4 = 0;
        }

    }
}
char DHT11_ReadData() {
    char i = 0;
    char data = 0;
    for (i = 0; i < 8; i++) {
        while (!(DHT_PORT & 1)); 
        __delay_us(30);
        if (DHT_PORT & 1) data = ((data << 1) | 1);
        else data = (data << 1);
        while (DHT_PORT & 1);
    }
    return data;
}
void DHT11_Start() {
    DHT_TRIS = 0;
    DHT_LAT = 0; /* send low pulse of min. 18 ms width */
    __delay_ms(18);
    DHT_LAT = 1; /* pull data bus high */
    __delay_us(40);
    DHT_TRIS = 1; /* set as input port */   
    while (DHT_PORT & 1); /* wait till bus is High */
    while (!(DHT_PORT & 1)); /* wait till bus is Low */
    while (DHT_PORT & 1); /* wait till bus is High */
}


