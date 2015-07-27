/**
 * @file       GpioSpi.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include "Gpio.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

GpioSpi::GpioSpi(const Gpio_TypeDef& gpio):
    Gpio(gpio)
{
    GPIOPinTypeGPIOOutput(gpio_.port, gpio_.pin);
}

void GpioSpi::high(void)
{
    GPIOPinWrite(gpio_.port, gpio_.pin, gpio_.pin);
}

void GpioSpi::low(void)
{
    GPIOPinWrite(gpio_.port, gpio_.pin, 0);
}

/*=============================== protected =================================*/

/*================================ private ==================================*/
