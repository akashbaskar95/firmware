/**
 * @file       Task.h
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

#ifndef TASK_H_
#define TASK_H_

#include "FreeRTOS.h"
#include "task.h"

class Task
{
public:
    Task(const char *taskName, unsigned short taskStack, char taskPriority);
    virtual void run() = 0;
private:
    xTaskHandle taskHandle;
};

#endif /* TASK_H_ */
