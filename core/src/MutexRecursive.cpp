/**
 * @file       MutexRecursive.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include "Mutex.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

MutexRecursive::MutexRecursive():
    Mutex()
{
    mutex_ = xSemaphoreCreateRecursiveMutex();
}

MutexRecursive::~MutexRecursive()
{
    vSemaphoreDelete(mutex_);
}

bool MutexRecursive::take(void)
{
    bool status = (xSemaphoreTakeRecursive(mutex_, portMAX_DELAY) == pdTRUE);
    return status;
}

bool MutexRecursive::take(uint32_t milliseconds)
{
    TickType_t timeout = milliseconds / portTICK_RATE_MS;
    bool status = (xSemaphoreTakeRecursive(mutex_, timeout) == pdTRUE);
    return status;
}

void MutexRecursive::give(void)
{
    xSemaphoreGiveRecursive(mutex_);
}

/*=============================== protected =================================*/

/*================================ private ==================================*/
