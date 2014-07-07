/*
 * Copyright 2013 OpenMote Technologies, S.L.
 */

/**
 *
 * @file       InterruptHandler.h
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2014
 * @brief
 * @ingroup
 *
 */

#ifndef INTERRUPT_HANDLER_H_
#define INTERRUPT_HANDLER_H_

class GpioIn;
class GpioInPow;
class I2c;
class Radio;
class Uart;

class InterruptHandler {

public:
    static InterruptHandler& getInstance(void);
    static void registerInterruptHandler(GpioIn* gpio_);
    static void registerInterruptHandler(Uart* uart_);
    static void registerInterruptHandler(I2c* i2c_);
    static void registerInterruptHandler(Radio* radio_);
protected:
    static inline void GPIOA_InterruptHandler(void);
    static inline void GPIOB_InterruptHandler(void);
    static inline void GPIOC_InterruptHandler(void);
    static inline void GPIOD_InterruptHandler(void);
    static inline void UART0_InterruptHandler(void);
    static inline void UART1_InterruptHandler(void);
    static inline void I2C_InterruptHandler(void);
    static inline void RFCore_InterruptHandler(void);
    static inline void RFError_InterruptHandler(void);
private:
    InterruptHandler();
private:
    static InterruptHandler instance;
    static GpioIn* GPIOA_interruptVector[8];
    static GpioIn* GPIOB_interruptVector[8];
    static GpioIn* GPIOC_interruptVector[8];
    static GpioIn* GPIOD_interruptVector[8];
    static Uart* UART0_interruptVector;
    static Uart* UART1_interruptVector;
    static I2c*  I2c_interruptVector;
    static Radio* Radio_interruptVector;
};

#endif /* INTERRUPT_HANDLER_H */
