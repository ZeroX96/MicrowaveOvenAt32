/*
 * Disp.c
 *
 * Created: 8/21/2021 7:49:37 PM
 *  Author: ZeroX96
 */ 
#include "Disp.h"

/*******************************************************************************/
/* Internal variables to hold the displays and their values                    */
/*******************************************************************************/
static SevenSegT InternalDispModule;
static uint8_t   InternalDispValues[MUX_NUMBER_OF_DISPS];

/*******************************************************************************/
/* DispInit: Function initializes the Display hardware module and it's sw data */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= NON                                                                 */
/*******************************************************************************/
void DispInit(void){
    //init the hardware module
    DisplayMuxInit(&InternalDispModule,DISPLAY_DATA_BASE,
                   DISPLAY_CTRL_BASE,DIPSLAY_MODULE_TYPE);
    //zero the data
    for (int i = 0; i< MUX_NUMBER_OF_DISPS; i++){
        InternalDispValues[i] = 0;
    }
}

/***********************************************************************************/
/* DispSetVal: Function updates the Display value as needed                        */
/* Params:                                                                         */
/* Input = DataVal = the required value to be set that will be extracted to digits */
/* Output= NON                                                                     */
/***********************************************************************************/
void DispSetVal(uint16_t DataVal){
    InternalDispValues[0] = (DataVal / 1   ) % 10;
    InternalDispValues[1] = (DataVal / 10  ) % 10;
    InternalDispValues[2] = (DataVal / 100 ) % 10;
    InternalDispValues[3] = (DataVal / 1000) % 10;
}

/*******************************************************************************/
/* DispUpdate: Function updates the display data current shown on the segments */
/* Params:                                                                     */
/* Input = Id defines which seven segment to turn on and show the data on      */
/* Output= NON                                                                 */
/*******************************************************************************/
void DispUpdate(uint8_t Id){
    //update the display data to present on the hardware
    DispSetVal( TimeGetTime() );
    DisplayMuxWrite(&InternalDispModule, InternalDispValues, Id);
}