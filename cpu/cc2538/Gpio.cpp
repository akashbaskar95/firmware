/**
 * @file       Gpio.cpp
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

Gpio::Gpio(const Gpio_TypeDef& gpio):
    gpio_(gpio)
{
}

uint32_t Gpio::getPort(void)
{
    return gpio_.port;
}

uint32_t Gpio::getPin(void)
{
    return gpio_.pin;
}

uint32_t Gpio::getIoc(void)
{
    return gpio_.ioc;
}

/*=============================== protected =================================*/

/*================================ private ==================================*/
