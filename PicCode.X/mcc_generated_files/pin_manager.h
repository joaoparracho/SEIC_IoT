/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F25K50
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set __AN0 aliases
#define __AN0_TRIS                 TRISAbits.TRISA0
#define __AN0_LAT                  LATAbits.LATA0
#define __AN0_PORT                 PORTAbits.RA0
#define __AN0_ANS                  ANSELAbits.ANSA0
#define __AN0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define __AN0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define __AN0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define __AN0_GetValue()           PORTAbits.RA0
#define __AN0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define __AN0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define __AN0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define __AN0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set LED3 aliases
#define LED3_TRIS                 TRISAbits.TRISA3
#define LED3_LAT                  LATAbits.LATA3
#define LED3_PORT                 PORTAbits.RA3
#define LED3_ANS                  ANSELAbits.ANSA3
#define LED3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define LED3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define LED3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define LED3_GetValue()           PORTAbits.RA3
#define LED3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define LED3_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define LED3_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set DHT aliases
#define DHT_TRIS                 TRISBbits.TRISB0
#define DHT_LAT                  LATBbits.LATB0
#define DHT_PORT                 PORTBbits.RB0
#define DHT_WPU                  WPUBbits.WPUB0
#define DHT_ANS                  ANSELBbits.ANSB0
#define DHT_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define DHT_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define DHT_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define DHT_GetValue()           PORTBbits.RB0
#define DHT_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define DHT_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define DHT_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define DHT_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define DHT_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define DHT_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set PIR aliases
#define PIR_TRIS                 TRISBbits.TRISB1
#define PIR_LAT                  LATBbits.LATB1
#define PIR_PORT                 PORTBbits.RB1
#define PIR_WPU                  WPUBbits.WPUB1
#define PIR_ANS                  ANSELBbits.ANSB1
#define PIR_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define PIR_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define PIR_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define PIR_GetValue()           PORTBbits.RB1
#define PIR_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define PIR_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define PIR_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define PIR_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define PIR_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define PIR_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set RB3 procedures
#define RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define RB3_SetPullup()             do { WPUBbits.WPUB3 = 1; } while(0)
#define RB3_ResetPullup()           do { WPUBbits.WPUB3 = 0; } while(0)
#define RB3_SetAnalogMode()         do { ANSELBbits.ANSB3 = 1; } while(0)
#define RB3_SetDigitalMode()        do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/