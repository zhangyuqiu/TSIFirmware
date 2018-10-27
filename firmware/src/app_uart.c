/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app_uart.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

#include "app_uart.h"

APP_UART_DATA app_uartData;


char app_uart_tx_buf[] = "Initial Buff4 \n\r";

typedef enum{
    HAVE_MESSAGE,
    NO_MESSAGE,
}UART_TX_STATE;

UART_TX_STATE uart_tx_state = HAVE_MESSAGE;
uint8_t length_tx = 0;

void APP_UART_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_uartData.state = APP_UART_STATE_INIT;
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_UART_Tasks ( void )

  Remarks:
    See prototype in app_uart.h.
 */

void APP_UART_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_uartData.state )
    {
        /* Application's initial state. */
        case APP_UART_STATE_INIT:
        {
            bool appInitialized = true;
       
        
            if (appInitialized)
            {
            
                app_uartData.state = APP_UART_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_UART_STATE_SERVICE_TASKS:
        {
            UART_TASK();
            //UART_BLOCKING_TASK();
            break;
        }

        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

UART_TASK() {
    if (uart_tx_state == HAVE_MESSAGE) {
        if (uart_write_ready() && length_tx < strlen(app_uart_tx_buf)) {
            U2TXREG = app_uart_tx_buf[length_tx];
            length_tx++;
        }
        if (length_tx == strlen(app_uart_tx_buf)) {
            length_tx = 0;
            app_uart_tx_buf[0] = '\0';
            uart_tx_state = NO_MESSAGE;
        }
    }
}

UART_BLOCKING_TASK() {
    if (uart_tx_state == HAVE_MESSAGE) {
        while(uart_write_ready() && length_tx < strlen(app_uart_tx_buf)) {
            U2TXREG = app_uart_tx_buf[length_tx];
            length_tx++;
        }
        if (length_tx == strlen(app_uart_tx_buf)) {
            length_tx = 0;
            app_uart_tx_buf[0] = '\0';
            uart_tx_state = NO_MESSAGE;
        }
    }
}

void uart_write_string(const char *towrite) {
    *app_uart_tx_buf = strcat(app_uart_tx_buf, towrite);
    uart_tx_state = HAVE_MESSAGE;
}

char uart_read() {
    while (!(uart_read_ready())) {} // check if URXDA is 1 (has data inside RX FIFO)
    char rx = U2RXREG;
    return rx;
}

int uart_read_ready() {
    int a = (U2STA & 1); // check if URXDA is 1 (has data inside RX FIFO)
    return a;
}

int uart_write_ready() {
    int a = !(U2STA & 0x200); // check UTXBF is equal to 0 (the TX FIFO is not full))
    return a;
}

char uart_read_nb() {
    if (!uart_read_ready()) {
        return '0';
    }
    else if (uart_read_ready()) {
        char rx = U2RXREG;
        return rx;
    }
}

void uart_write_nb(char towrite) {
    U2TXREG = towrite;
}

/*******************************************************************************
 End of File
 */
