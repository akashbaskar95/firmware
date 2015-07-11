/**
 * @file       Gpio.h
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#include "Callback.h"

typedef struct Gpio_TypeDef Gpio_TypeDef;

class Gpio
{
public:
    Gpio(Gpio_TypeDef& gpio);
    uint32_t getPort(void);
    uint32_t getPin(void);
protected:
    Gpio_TypeDef& gpio_;
};

/*****************************************************************************/

class GpioIn : public Gpio
{

friend class InterruptHandler;

public:
    GpioIn(Gpio_TypeDef& gpio);
    bool read(void);
    void setCallback(Callback* callback);
    void clearCallback(void);
    void enableInterrupts(void);
    void disableInterrupts(void);
protected:
    void interruptHandler(void);
protected:
    Callback* callback_;
};

/*****************************************************************************/

class GpioOut : public Gpio
{
public:
    GpioOut(Gpio_TypeDef& gpio);
    void on(void);
    void off(void);
    void toggle(void);
    bool status(void);
};

/*****************************************************************************/

class GpioInPow : public GpioIn
{
public:
    GpioInPow(Gpio_TypeDef& gpio);
    void enableInterrupts(void);
    void disableInterrupts(void);
};

/*****************************************************************************/

class GpioAdc : public Gpio
{
public:
    GpioAdc(Gpio_TypeDef& gpio);
    void init(uint32_t resolution, uint32_t reference);
    uint32_t read(void);
};

/*****************************************************************************/

class GpioI2c : public Gpio
{
public:
    GpioI2c(Gpio_TypeDef& gpio);
};

/*****************************************************************************/

class GpioSpi : public Gpio
{
public:
    GpioSpi(Gpio_TypeDef& gpio);
    uint32_t getIoc(void);
    void high(void);
    void low(void);
};

/*****************************************************************************/

class GpioPwm : public Gpio
{
public:
    GpioPwm(Gpio_TypeDef& gpio);
};

/*****************************************************************************/

class GpioUart : public Gpio
{
public:
    GpioUart(Gpio_TypeDef& gpio);
    uint32_t getIoc(void);
};

/*****************************************************************************/

#endif /* GPIO_H_ */
