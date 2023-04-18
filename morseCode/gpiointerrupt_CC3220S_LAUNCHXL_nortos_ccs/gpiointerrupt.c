/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>

/* Driver configuration */
#include "ti_drivers_config.h"

//Zach mohler, added for purpose of timer 3/29/23
#include <ti/drivers/Timer.h>

//timer tick indicator
volatile unsigned char timerFlag = 0;

//signal switch to change between SOS (0) and OK (1)
volatile unsigned char signalSwitch = 0;




/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_0.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 *
 *  SETS SIGNAL TO SOS
 */
void gpioButtonFxn0(uint_least8_t index)
{
    signalSwitch = 0;
}




/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_1.
 *  This may not be used for all boards.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 *
 *  SETS SIGNAL TO OK
 */
void gpioButtonFxn1(uint_least8_t index)
{
    signalSwitch = 1;
}




//FUNCTION TO WAIT ONE TIMER CYCLE
void waitTicks(char numTicks)
{
    unsigned char i;

    for(i = 0; i < numTicks; i++)
    {
        while(!timerFlag) {}
        timerFlag = 0;
    }
}


//STATE MACHINE INITIALIZATION AND DEFINITIONS
enum Morse_States { MorseSM_Start, MorseSM_sos, MorseSM_ok } MorseSM_State;

void TickFct_Morse()
{

//============== TRANSITIONS ==============

    switch(MorseSM_State)
    {
        // Initial transition
        case MorseSM_Start:
            MorseSM_State = MorseSM_sos;
            break;

        //transitions from SOS state
        case MorseSM_sos:
            if(signalSwitch == 0)
            {
                MorseSM_State = MorseSM_sos;
            }
            else if(signalSwitch == 1)
            {
                MorseSM_State = MorseSM_ok;
            }
            break;

        //transitions from OK state
        case MorseSM_ok:
            if(signalSwitch == 0)
            {
                MorseSM_State = MorseSM_sos;
            }
            else if(signalSwitch == 1)
            {
                MorseSM_State = MorseSM_ok;
            }
            break;

        //safety default case
        default:
            MorseSM_State = MorseSM_Start;
            break;
    }

//============== ACTIONS ==============
    switch(MorseSM_State)
    {


    //========= SOS ===================
        case MorseSM_sos:

            //first letter S
            GPIO_toggle(CONFIG_GPIO_LED_0); //high
            waitTicks(1);
            GPIO_toggle(CONFIG_GPIO_LED_0); //low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_0); //high
            waitTicks(1);
            GPIO_toggle(CONFIG_GPIO_LED_0); //low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_0); //high
            waitTicks(1);
            GPIO_toggle(CONFIG_GPIO_LED_0); //low

            //between letters
            waitTicks(3);

            //second letter O
            GPIO_toggle(CONFIG_GPIO_LED_1); //high
            waitTicks(3);
            GPIO_toggle(CONFIG_GPIO_LED_1); //low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_1); //high
            waitTicks(3);
            GPIO_toggle(CONFIG_GPIO_LED_1); //low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_1); //high
            waitTicks(3);
            GPIO_toggle(CONFIG_GPIO_LED_1); //low

            //between letters
            waitTicks(3);

            //second letter S
            GPIO_toggle(CONFIG_GPIO_LED_0); //high
            waitTicks(1);
            GPIO_toggle(CONFIG_GPIO_LED_0); //low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_0); //high
            waitTicks(1);
            GPIO_toggle(CONFIG_GPIO_LED_0); //low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_0); //high
            waitTicks(1);
            GPIO_toggle(CONFIG_GPIO_LED_0); //low

            //between messages
            waitTicks(7);

            break; //end cycle

    //========= OK ===================
        case MorseSM_ok:

            //first letter O
            GPIO_toggle(CONFIG_GPIO_LED_1); //high
            waitTicks(3);
            GPIO_toggle(CONFIG_GPIO_LED_1); //low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_1); //high
            waitTicks(3);
            GPIO_toggle(CONFIG_GPIO_LED_1); //low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_1); //high
            waitTicks(3);
            GPIO_toggle(CONFIG_GPIO_LED_1); //low

            //between letters
            waitTicks(3);

            //second letter K
            GPIO_toggle(CONFIG_GPIO_LED_1); //LED 1 high
            waitTicks(3);
            GPIO_toggle(CONFIG_GPIO_LED_1); //LED 1 low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_0); //LED 0 high
            waitTicks(1);
            GPIO_toggle(CONFIG_GPIO_LED_0); //LED 0 low
            waitTicks(1);

            GPIO_toggle(CONFIG_GPIO_LED_1); //LED 1 high
            waitTicks(3);
            GPIO_toggle(CONFIG_GPIO_LED_1); //LED 1 low

            //between messages
            waitTicks(7);

            break; //end cycle

        //safety default case
        default:
            break;
   }
}


// ========= timer callbacks ==========
void timerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    timerFlag = 1;
}


void initTimer(void)
{
    Timer_Handle timer0;
    Timer_Params params;
    Timer_init();
    Timer_Params_init(&params);
    params.period = 500000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    timer0 = Timer_open(CONFIG_TIMER_0, &params);
    if (timer0 == NULL)
    {
        /* Failed to initialized timer */
        while (1) {}
    }


    if (Timer_start(timer0) == Timer_STATUS_ERROR)
    {
        /* Failed to start timer */
        while (1) {}
    }

}





/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver init functions */
    GPIO_init();
    initTimer();

    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    /* Turn on user LED */
    //GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* Install Button callback */
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonFxn0);

    /* Enable interrupts */
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    /*
     *  If more than one input pin is available for your device, interrupts
     *  will be enabled on CONFIG_GPIO_BUTTON1.
     */
    if (CONFIG_GPIO_BUTTON_0 != CONFIG_GPIO_BUTTON_1) {
        /* Configure BUTTON1 pin */
        GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

        /* Install Button callback */
        GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioButtonFxn1);
        GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    }

    //create state machine
    MorseSM_State = MorseSM_Start;

    while(1)
    {
        TickFct_Morse();
    }
}
