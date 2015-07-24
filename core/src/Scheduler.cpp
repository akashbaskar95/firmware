/**
 * @file       Scheduler.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include "Scheduler.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

Scheduler::Scheduler()
{
}

void Scheduler::start(void)
{
    // Kick the FreeRTOS scheduler
    vTaskStartScheduler();
}

void Scheduler::stop(void)
{
}

/*=============================== protected =================================*/

/*================================ private ==================================*/
