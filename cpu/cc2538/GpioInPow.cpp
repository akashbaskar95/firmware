/**
 * @file       GpioInPow.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include "cc2538_include.h"
#include "cc2538_types.h"

#include "Gpio.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

GpioInPow::GpioInPow(Gpio_TypeDef& gpio):
    GpioIn(gpio)
{
    // Set the pin as input
    GPIOPinTypeGPIOInput(gpio_.port, gpio_.pin);

    // Set the edge of the interrupt
    GPIOPowIntTypeSet(gpio_.port, gpio_.pin, gpio_.edge);

    // Enable the interrupt wakeup capability of the port
    if (gpio_.port == GPIO_A_BASE)
    {
        GPIOIntWakeupEnable(GPIO_IWE_PORT_A);
    }
    else if (gpio_.port == GPIO_B_BASE)
    {
        GPIOIntWakeupEnable(GPIO_IWE_PORT_B);
    }
    else if (gpio_.port == GPIO_C_BASE)
    {
        GPIOIntWakeupEnable(GPIO_IWE_PORT_C);
    }
    else if (gpio_.port == GPIO_D_BASE)
    {
        GPIOIntWakeupEnable(GPIO_IWE_PORT_D);
    }
}

void GpioInPow::enableInterrupts(void)
{
    // Clear the power interrupt
    GPIOPowIntClear(gpio_.port, gpio_.pin);

    // Enable the power intrrupt
    GPIOPowIntEnable(gpio_.port, gpio_.pin);
}

void GpioInPow::disableInterrupts(void)
{
    // Enable the power intrrupt
    GPIOPowIntDisable(gpio_.port, gpio_.pin);
}

/*=============================== protected =================================*/

/*================================ private ==================================*/
