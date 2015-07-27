/**
 * @file       GpioOut.cpp
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

GpioOut::GpioOut(const Gpio_TypeDef& gpio):
    Gpio(gpio)
{
    // Set the pin as output
    GPIOPinTypeGPIOOutput(gpio_.port, gpio_.pin);

    // Set the pin low
    GPIOPinWrite(gpio_.port, gpio_.pin, 0);
}

void GpioOut::on(void)
{
    // Set the pin high
    GPIOPinWrite(gpio_.port, gpio_.pin, gpio_.pin);
}

void GpioOut::off(void)
{
    // Set the pin low
    GPIOPinWrite(gpio_.port, gpio_.pin, 0);
}

void GpioOut::toggle(void)
{
    // Read the old status of the pin
    uint32_t status = GPIOPinRead(gpio_.port, gpio_.pin);

    // Change the status of the pin
    status = (~status) & gpio_.pin;

    // Set the new status of the pin
    GPIOPinWrite(gpio_.port, gpio_.pin, status);
}

bool GpioOut::status(void)
{
    // Read the pin status
    uint32_t status = GPIOPinRead(gpio_.port, gpio_.pin);

    // Return the pin status
    return (bool)(status & gpio_.pin);
}

/*=============================== protected =================================*/

/*================================ private ==================================*/
