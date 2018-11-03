/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _TSI_CONFIG    /* Guard against multiple inclusion */
#define _TSI_CONFIG

/*CAN bus TSI parameter*/
#define CAN_MESSAGE_SEND_ARRAY_LENGTH 10 // numbers of maximum CAN message to be transmitted that wait in queue
#define CAN_MESSAGE_SEND_BYTES 8 // Length of sending can message. Minimum 1, Maximum 8;

/*Watchdog timer period*/
#define TIMER0_INT_PERIOD 78125 // int time = (TIMER0_INT_PERIOD/clk_feq) * prescaler. 78125 for 0.1s
#define TIMER0_INT_MULT 30 // final interrupt time = int time * TIMER0_INT_MULT.

/*I2C TSI parameter*/
#define I2C_MESSAGE_SEND_ARRAY_LENGTH 10 // numbers of maximum CAN message to be transmitted that wait in queue
#define I2C_MESSAGE_SEND_BYTES 8 // Length of sending can message. Minimum 1, Maximum 8;

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
