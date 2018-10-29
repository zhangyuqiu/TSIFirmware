/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "app_uart.h"
#include "app_can.h"
#include "app_driver_state_fsm.h"
#include "system_definitions.h"
#include "../../TSIconfig.h"
// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
 
 uint32_t timerCount = 0;

 
void __ISR(_TIMER_1_VECTOR, ipl1AUTO) IntHandlerDrvTmrInstance0(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_1);
    
    timerCount++;
    if (timerCount == TIMER0_INT_MULT) {
        BSP_LEDToggle(BSP_LED_1);
        can_send_bytes(0x300,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF);
        timerCount = 0;
    }
    
    //uart_write_string(" Timer1 Triggered3.\n\r");
    //can_send_bytes(0x123,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF);
    //can_send_bytes(0x201,0x11,0x22,0x33,0x44,0x55,0x66);
}
 
void __ISR(_CAN1_VECTOR, IPL1AUTO) _IntHandlerDrvCANInstance0(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CAN_1);
    uart_write_string(" Canbus1 Triggered.\n\r");
    
    uint8_t TestMessage1[6]; //Test message to transmit on CAN
    uint8_t TestMessage2[6]; //Test message to transmit on CAN
    uint8_t TestMessage3[6]; //Test message to transmit on CAN
    uint8_t TestMessage4[6]; //Test message to transmit on CAN
    
    if((PLIB_CAN_ModuleEventGet(CAN_ID_1) & (CAN_RX_EVENT)) != 0)
    {

       if(DRV_CAN0_ChannelMessageReceive(CAN_CHANNEL1, 0x201, 4, &TestMessage1[0])){
           can_send_bytes(0x123,TestMessage1[0],TestMessage1[1],TestMessage1[2],TestMessage1[3],TestMessage1[4],TestMessage1[5],rand() % 0xFF,rand() % 0xFF);
       };
       if(DRV_CAN0_ChannelMessageReceive(CAN_CHANNEL2, 0x301, 4, &TestMessage2[0]));
       if(DRV_CAN0_ChannelMessageReceive(CAN_CHANNEL3, 0x401, 4, &TestMessage3[0]));
       if(DRV_CAN0_ChannelMessageReceive(CAN_CHANNEL4, 0x501, 4, &TestMessage4[0]));
       PLIB_CAN_ModuleEventClear(CAN_ID_1,  CAN_RX_EVENT); //Clear CAN Interrupt flag
    }
    
    
}



 /*******************************************************************************
 End of File
*/
