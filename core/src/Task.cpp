/**
 * @file       Task.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include "Task.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

/*=============================== prototypes ================================*/

extern "C" void pvTaskCode(void *pvParameters);

/*================================= public ==================================*/

Task::Task(const char *taskName, unsigned short taskStack, char taskPriority)
{
    xTaskCreate(pvTaskCode, (const char *) taskName, taskStack, (void*) this, taskPriority, &taskHandle);
}

extern "C" void pvTaskCode(void *pvParameters)
{
    (static_cast<Task*>(pvParameters))->run();
}

/*=============================== protected =================================*/

/*================================ private ==================================*/
