/**
 * @file       Scheduler.h
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "FreeRTOS.h"
#include "task.h"

class Scheduler
{
public:
    Scheduler();
    void start(void);
    void stop(void);
};

#endif /* SCHEDULER_H_ */
