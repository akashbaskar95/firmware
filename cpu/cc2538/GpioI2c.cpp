/**
 * @file       GpioI2c.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include "cpu_include.h"
#include "cpu_types.h"

#include "Gpio.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

GpioI2c::GpioI2c(const Gpio_TypeDef& gpio):
    Gpio(gpio)
{
}

/*=============================== protected =================================*/

/*================================ private ==================================*/
