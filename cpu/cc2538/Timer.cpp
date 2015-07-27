/**
 * @file       Timer.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include "Timer.h"
#include "InterruptHandler.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

Timer::Timer(Timer_TypeDef& timer):
    timer_(timer)
{
}

uint32_t Timer::getBase(void)
{
    return timer_.base;
}

uint32_t Timer::getSource(void)
{
    return timer_.source;
}

void Timer::init(uint32_t frequency)
{
    // Store the Timer frequency
    frequency_ = frequency;

    // Disable peripheral previous to configuring it
    TimerDisable(timer_.base, timer_.source);

    // Enable peripheral except in deep sleep modes (e.g. LPM1, LPM2, LPM3)
    SysCtrlPeripheralEnable(timer_.peripheral);
    SysCtrlPeripheralSleepEnable(timer_.peripheral);
    SysCtrlPeripheralDeepSleepDisable(timer_.peripheral);

    // Configure the peripheral
    TimerConfigure(timer_.base, timer_.config);

    // Set the frequency
    TimerLoadSet(timer_.base, timer_.source, frequency_);
}

void Timer::start(void)
{
    TimerEnable(timer_.base, timer_.source);
}

void Timer::stop(void)
{
    TimerDisable(timer_.base, timer_.source);
}

uint32_t Timer::read(void)
{
    return TimerValueGet(timer_.base, timer_.source);
}

void Timer::setCallback(Callback* callback)
{
    callback_ = callback;
}

void Timer::clearCallback(void)
{
    callback_ = nullptr;
}

void Timer::enableInterrupts(void)
{
    InterruptHandler::getInstance().setInterruptHandler(this);

    // Enable Timer interrupts
    TimerIntEnable(timer_.base, timer_.interrupt_mode);

    // Set the Timer interrupt priority
    // IntPrioritySet(interrupt_, (7 << 5));

    // Enable the Timer interrupt
    IntEnable(timer_.interrupt);
}

void Timer::disableInterrupts(void)
{
    // Diisable Timer interrupts
    TimerIntDisable(timer_.base, timer_.interrupt_mode);

    // Disable the Timer interrupt
    IntDisable(timer_.interrupt);
}

/*=============================== protected =================================*/

void Timer::interruptHandler(void)
{
    if (callback_ != nullptr)
    {
        callback_->execute();
    }
}

/*================================ private ==================================*/
