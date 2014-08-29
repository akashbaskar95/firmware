/*
 * Copyright 2013 OpenMote Technologies, S.L.
 */

/**
 *
 * @file       InterruptHandler.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2014
 * @brief
 * @ingroup
 *
 */

/*================================ include ==================================*/

#include "InterruptHandler.h"

#include "GpioIn.h"
#include "GpioInPow.h"
#include "Timer.h"
#include "Uart.h"
#include "I2c.h"
#include "Spi.h"
#include "Radio.h"

#include "cc2538_include.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

InterruptHandler InterruptHandler::instance;

GpioIn* InterruptHandler::GPIOA_interruptVector[8];
GpioIn* InterruptHandler::GPIOB_interruptVector[8];
GpioIn* InterruptHandler::GPIOC_interruptVector[8];
GpioIn* InterruptHandler::GPIOD_interruptVector[8];

Timer* InterruptHandler::TIMER0_interruptVector[2];
Timer* InterruptHandler::TIMER1_interruptVector[2];
Timer* InterruptHandler::TIMER2_interruptVector[2];
Timer* InterruptHandler::TIMER3_interruptVector[2];

Uart* InterruptHandler::UART0_interruptVector;
Uart* InterruptHandler::UART1_interruptVector;

I2c* InterruptHandler::I2C_interruptVector;

Spi* InterruptHandler::SPI0_interruptVector;
Spi* InterruptHandler::SPI1_interruptVector;

Radio* InterruptHandler::Radio_interruptVector;

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

InterruptHandler &InterruptHandler::getInstance(void)
{
    // Returns the only instance of the InterruptHandler
    return instance;
}

void InterruptHandler::setInterruptHandler(GpioIn * gpio_)
{
    // Get the GPIO port and pin
    uint32_t port_ = gpio_->getPort();
    uint8_t pin_   = gpio_->getPin();

    // Select the pin number
    if (pin_ == GPIO_PIN_0)
    {
        pin_ = 0;
    }
    else if (pin_ == GPIO_PIN_1)
    {
        pin_ = 1;
    }
    else if (pin_ == GPIO_PIN_2)
    {
        pin_ = 2;
    }
    else if (pin_ == GPIO_PIN_3)
    {
        pin_ = 3;
    }
    else if (pin_ == GPIO_PIN_4)
    {
        pin_ = 4;
    }
    else if (pin_ == GPIO_PIN_5)
    {
        pin_ = 5;
    }
    else if (pin_ == GPIO_PIN_6)
    {
        pin_ = 6;
    }
    else if (pin_ == GPIO_PIN_7)
    {
        pin_ = 7;
    }

    // Store a pointer to the GPIO object in the interrupt vector
    if (port_ == GPIO_A_BASE)
    {
        GPIOA_interruptVector[pin_] = gpio_;
    }
    else if (port_ == GPIO_B_BASE)
    {
        GPIOB_interruptVector[pin_] = gpio_;
    }
    else if (port_ == GPIO_C_BASE)
    {
        GPIOC_interruptVector[pin_] = gpio_;
    }
    else if (port_ == GPIO_D_BASE)
    {
        GPIOD_interruptVector[pin_] = gpio_;
    }
}

void InterruptHandler::clearInterruptHandler(GpioIn * gpio_)
{
    // Get the GPIO port and pin
    uint32_t port_ = gpio_->getPort();
    uint8_t pin_   = gpio_->getPin();

    // Select the pin number
    if (pin_ == GPIO_PIN_0)
    {
        pin_ = 0;
    }
    else if (pin_ == GPIO_PIN_1)
    {
        pin_ = 1;
    }
    else if (pin_ == GPIO_PIN_2)
    {
        pin_ = 2;
    }
    else if (pin_ == GPIO_PIN_3)
    {
        pin_ = 3;
    }
    else if (pin_ == GPIO_PIN_4)
    {
        pin_ = 4;
    }
    else if (pin_ == GPIO_PIN_5)
    {
        pin_ = 5;
    }
    else if (pin_ == GPIO_PIN_6)
    {
        pin_ = 6;
    }
    else if (pin_ == GPIO_PIN_7)
    {
        pin_ = 7;
    }

    // Remove the pointer to the GPIO object in the interrupt vector
    if (port_ == GPIO_A_BASE)
    {
        GPIOA_interruptVector[pin_] = nullptr;
    }
    else if (port_ == GPIO_B_BASE)
    {
        GPIOB_interruptVector[pin_] = nullptr;
    }
    else if (port_ == GPIO_C_BASE)
    {
        GPIOC_interruptVector[pin_] = nullptr;
    }
    else if (port_ == GPIO_D_BASE)
    {
        GPIOD_interruptVector[pin_] = nullptr;
    }
}

void InterruptHandler::setInterruptHandler(Timer* timer_)
{
    // Get the TIMER base
    uint32_t base = timer_->getBase();
    uint32_t source = timer_->getSource();

    if (base == GPTIMER0_BASE)
    {
        if ( (source == GPTIMER_A) || \
             (source == GPTIMER_BOTH) )
        {
            TIMER0_interruptVector[0] = timer_;
        }
        else if (source == GPTIMER_B)
        {
            TIMER0_interruptVector[1] = timer_;
        }
    }
    else if (base == GPTIMER1_BASE)
    {
        if ( (source == GPTIMER_A) || \
             (source == GPTIMER_BOTH) )
        {
            TIMER1_interruptVector[0] = timer_;
        }
        else if (source == GPTIMER_B)
        {
            TIMER1_interruptVector[1] = timer_;
        }
    }
    else if (base == GPTIMER2_BASE)
    {
        if ( (source == GPTIMER_A) || \
             (source == GPTIMER_BOTH) )
        {
            TIMER2_interruptVector[0] = timer_;
        }
        else if (source == GPTIMER_B)
        {
            TIMER2_interruptVector[1] = timer_;
        }
    }
    else if (base == GPTIMER3_BASE)
    {
        if ( (source == GPTIMER_A) || \
             (source == GPTIMER_BOTH) )
        {
            TIMER3_interruptVector[0] = timer_;
        }
        else if (source == GPTIMER_B)
        {
            TIMER3_interruptVector[1] = timer_;
        }
    }
}

void InterruptHandler::clearInterruptHandler(Timer* timer_)
{
    // Get the TIMER base
    uint32_t base = timer_->getBase();
    uint32_t source = timer_->getSource();

    if (base == GPTIMER0_BASE)
    {
        if ( (source == GPTIMER_A) || \
             (source == GPTIMER_BOTH) )
        {
            TIMER0_interruptVector[0] = nullptr;
        }
        else if (source == GPTIMER_B)
        {
            TIMER0_interruptVector[1] = nullptr;
        }
    }
    else if (base == GPTIMER1_BASE)
    {
        if ( (source == GPTIMER_A) || \
             (source == GPTIMER_BOTH) )
        {
            TIMER1_interruptVector[0] = nullptr;
        }
        else if (source == GPTIMER_B)
        {
            TIMER1_interruptVector[1] = nullptr;
        }
    }
    else if (base == GPTIMER2_BASE)
    {
        if ( (source == GPTIMER_A) || \
             (source == GPTIMER_BOTH) )
        {
            TIMER2_interruptVector[0] = nullptr;
        }
        else if (source == GPTIMER_B)
        {
            TIMER2_interruptVector[1] = nullptr;
        }
    }
    else if (base == GPTIMER3_BASE)
    {
        if ( (source == GPTIMER_A) || \
             (source == GPTIMER_BOTH) )
        {
            TIMER3_interruptVector[0] = nullptr;
        }
        else if (source == GPTIMER_B)
        {
            TIMER3_interruptVector[1] = nullptr;
        }
    }
}

void InterruptHandler::setInterruptHandler(Uart * uart_)
{
    // Get the UART base
    uint32_t base = uart_->getBase();

    // Store a pointer to the UART object in the interrupt vector
    if (base == UART0_BASE)
    {
        UART0_interruptVector = uart_;
    }
    else if (base == UART1_BASE)
    {
        UART1_interruptVector = uart_;
    }
}

void InterruptHandler::clearInterruptHandler(Uart * uart_)
{
    // Get the UART base
    uint32_t base = uart_->getBase();

    // Remove the pointer to the UART object in the interrupt vector
    if (base == UART0_BASE)
    {
        UART0_interruptVector = nullptr;
    }
    else if (base == UART1_BASE)
    {
        UART1_interruptVector = nullptr;
    }
}

void InterruptHandler::setInterruptHandler(I2c * i2c_)
{
    // Store a pointer to the I2C object in the interrupt vector
    I2C_interruptVector = i2c_;
}

void InterruptHandler::clearInterruptHandler(I2c * i2c_)
{
    // Remvoe the pointer to the I2C object in the interrupt vector
    I2C_interruptVector = nullptr;
}

void InterruptHandler::setInterruptHandler(Spi * spi_)
{
    // Get the UART base
    uint32_t base = spi_->getBase();

    // Store a pointer to the UART object in the interrupt vector
    if (base == SSI0_BASE)
    {
        SPI0_interruptVector = spi_;
    }
    else if (base == SSI1_BASE)
    {
        SPI1_interruptVector = spi_;
    }
}

void InterruptHandler::clearInterruptHandler(Spi * spi_)
{
    // Get the UART base
    uint32_t base = spi_->getBase();

    // Remove the pointer to the UART object in the interrupt vector
    if (base == SSI0_BASE)
    {
        SPI0_interruptVector = nullptr;
    }
    else if (base == SSI1_BASE)
    {
        SPI1_interruptVector = nullptr;
    }
}

void InterruptHandler::setInterruptHandler(Radio * radio_)
{
    // Store a pointer to the RADIO object in the interrupt vector
    Radio_interruptVector = radio_;
}

void InterruptHandler::clearInterruptHandler(Radio * radio_)
{
    // Remove the pointer to the RADIO object in the interrupt vector
    Radio_interruptVector = nullptr;
}

/*=============================== protected =================================*/

/*================================ private ==================================*/

InterruptHandler::InterruptHandler()
{
    // Register the GPIO interrupt handlers
    GPIOPortIntRegister(GPIO_A_BASE, GPIOA_InterruptHandler);
    GPIOPortIntRegister(GPIO_B_BASE, GPIOB_InterruptHandler);
    GPIOPortIntRegister(GPIO_C_BASE, GPIOC_InterruptHandler);
    GPIOPortIntRegister(GPIO_D_BASE, GPIOD_InterruptHandler);

    // Register the TIMERx interrupt handlers
    TimerIntRegister(GPTIMER0_BASE, GPTIMER_A, TIMER0_InterruptHandler);
    TimerIntRegister(GPTIMER0_BASE, GPTIMER_B, TIMER0_InterruptHandler);
    TimerIntRegister(GPTIMER0_BASE, GPTIMER_BOTH, TIMER0_InterruptHandler);
    TimerIntRegister(GPTIMER1_BASE, GPTIMER_A, TIMER1_InterruptHandler);
    TimerIntRegister(GPTIMER1_BASE, GPTIMER_B, TIMER1_InterruptHandler);
    TimerIntRegister(GPTIMER1_BASE, GPTIMER_BOTH, TIMER1_InterruptHandler);
    TimerIntRegister(GPTIMER2_BASE, GPTIMER_A, TIMER2_InterruptHandler);
    TimerIntRegister(GPTIMER2_BASE, GPTIMER_B, TIMER2_InterruptHandler);
    TimerIntRegister(GPTIMER2_BASE, GPTIMER_BOTH, TIMER2_InterruptHandler);
    TimerIntRegister(GPTIMER3_BASE, GPTIMER_A, TIMER3_InterruptHandler);
    TimerIntRegister(GPTIMER3_BASE, GPTIMER_B, TIMER3_InterruptHandler);
    TimerIntRegister(GPTIMER3_BASE, GPTIMER_BOTH, TIMER3_InterruptHandler);

    // Register the UARTx interrupt handlers
    UARTIntRegister(UART0_BASE, UART0_InterruptHandler);
    UARTIntRegister(UART1_BASE, UART1_InterruptHandler);

    // Register the I2C interrupt handler
    I2CIntRegister(I2C_InterruptHandler);

    // Register the SPIx interrupt handler
    SSIIntRegister(SSI0_BASE, SPI0_InterruptHandler);
    SSIIntRegister(SSI1_BASE, SPI1_InterruptHandler);

    // Register the RF CORE and ERROR interrupt handlers
    IntRegister(INT_RFCORERTX, RFCore_InterruptHandler);
    IntRegister(INT_RFCOREERR, RFError_InterruptHandler);
}

inline void InterruptHandler::GPIOA_InterruptHandler(void)
{
    uint32_t status;

    // Read the GPIO interrupt status (both regular and power)
    uint32_t pin_status = GPIOPinIntStatus(GPIO_A_BASE, true);
    uint32_t pow_status = GPIOPowIntStatus(GPIO_A_BASE, true);

    // Clear the regular GPIO interrupt status
    if (pin_status)
    {
        GPIOPinIntClear(GPIO_A_BASE, pin_status);
    }

    // Clear the power GPIO interrupt status
    if (pow_status)
    {
        GPIOPowIntClear(GPIO_A_BASE, pow_status);
    }

    // Status is both regular and power GPIO interrupt status
    status = pin_status | pow_status;

    // Call all the GPIO interrupt handlers
    if (status & GPIO_PIN_0)
    {
        GPIOA_interruptVector[0]->interruptHandler();
    }
    if (status & GPIO_PIN_1)
    {
        GPIOA_interruptVector[1]->interruptHandler();
    }
    if (status & GPIO_PIN_2)
    {
        GPIOA_interruptVector[2]->interruptHandler();
    }
    if (status & GPIO_PIN_3)
    {
        GPIOA_interruptVector[3]->interruptHandler();
    }
    if (status & GPIO_PIN_4)
    {
        GPIOA_interruptVector[4]->interruptHandler();
    }
    if (status & GPIO_PIN_5)
    {
        GPIOA_interruptVector[5]->interruptHandler();
    }
    if (status & GPIO_PIN_6)
    {
        GPIOA_interruptVector[6]->interruptHandler();
    }
    if (status & GPIO_PIN_7)
    {
        GPIOA_interruptVector[7]->interruptHandler();
    }
}

inline void InterruptHandler::GPIOB_InterruptHandler(void)
{
    uint32_t status;

    // Read the GPIO interrupt status (both regular and power)
    uint32_t pin_status = GPIOPinIntStatus(GPIO_B_BASE, true);
    uint32_t pow_status = GPIOPowIntStatus(GPIO_B_BASE, true);

    // Clear the regular GPIO interrupt status
    if (pin_status)
    {
        GPIOPinIntClear(GPIO_B_BASE, pin_status);
    }

    // Clear the power GPIO interrupt status
    if (pow_status)
    {
        GPIOPowIntClear(GPIO_B_BASE, pow_status);
    }

    // Status is both regular and power GPIO interrupt status
    status = pin_status | pow_status;

    // Call all the GPIO interrupt handlers
    if (status & GPIO_PIN_0)
    {
        GPIOB_interruptVector[0]->interruptHandler();
    }
    if (status & GPIO_PIN_1)
    {
        GPIOB_interruptVector[1]->interruptHandler();
    }
    if (status & GPIO_PIN_2)
    {
        GPIOB_interruptVector[2]->interruptHandler();
    }
    if (status & GPIO_PIN_3)
    {
        GPIOB_interruptVector[3]->interruptHandler();
    }
    if (status & GPIO_PIN_4)
    {
        GPIOB_interruptVector[4]->interruptHandler();
    }
    if (status & GPIO_PIN_5)
    {
        GPIOB_interruptVector[5]->interruptHandler();
    }
    if (status & GPIO_PIN_6)
    {
        GPIOB_interruptVector[6]->interruptHandler();
    }
    if (status & GPIO_PIN_7)
    {
        GPIOB_interruptVector[7]->interruptHandler();
    }
}

inline void InterruptHandler::GPIOC_InterruptHandler(void)
{
    uint32_t status;

    // Read the GPIO interrupt status (both regular and power)
    uint32_t pin_status = GPIOPinIntStatus(GPIO_C_BASE, true);
    uint32_t pow_status = GPIOPowIntStatus(GPIO_C_BASE, true);

    // Clear the regular GPIO interrupt status
    if (pin_status)
    {
        GPIOPinIntClear(GPIO_C_BASE, pin_status);
    }

    // Clear the power GPIO interrupt status
    if (pow_status)
    {
        GPIOPowIntClear(GPIO_C_BASE, pow_status);
    }

    // Status is both regular and power GPIO interrupt status
    status = pin_status | pow_status;

    // Call all the GPIO interrupt handlers
    if (status & GPIO_PIN_0)
    {
        GPIOC_interruptVector[0]->interruptHandler();
    }
    if (status & GPIO_PIN_1)
    {
        GPIOC_interruptVector[1]->interruptHandler();
    }
    if (status & GPIO_PIN_2)
    {
        GPIOC_interruptVector[2]->interruptHandler();
    }
    if (status & GPIO_PIN_3)
    {
        GPIOC_interruptVector[3]->interruptHandler();
    }
    if (status & GPIO_PIN_4)
    {
        GPIOC_interruptVector[4]->interruptHandler();
    }
    if (status & GPIO_PIN_5)
    {
        GPIOC_interruptVector[5]->interruptHandler();
    }
    if (status & GPIO_PIN_6)
    {
        GPIOC_interruptVector[6]->interruptHandler();
    }
    if (status & GPIO_PIN_7)
    {
        GPIOC_interruptVector[7]->interruptHandler();
    }
}

inline void InterruptHandler::GPIOD_InterruptHandler(void)
{
    uint32_t status;

    // Read the GPIO interrupt status (both regular and power)
    uint32_t pin_status = GPIOPinIntStatus(GPIO_D_BASE, true);
    uint32_t pow_status = GPIOPowIntStatus(GPIO_D_BASE, true);

    // Clear the regular GPIO interrupt status
    if (pin_status)
    {
        GPIOPinIntClear(GPIO_D_BASE, pin_status);
    }

    // Clear the power GPIO interrupt status
    if (pow_status)
    {
        GPIOPowIntClear(GPIO_D_BASE, pow_status);
    }

    // Status is both regular and power GPIO interrupt status
    status = pin_status | pow_status;

    // Call all the GPIO interrupt handlers
    if (status & GPIO_PIN_0)
    {
        GPIOD_interruptVector[0]->interruptHandler();
    }
    if (status & GPIO_PIN_1)
    {
        GPIOD_interruptVector[1]->interruptHandler();
    }
    if (status & GPIO_PIN_2)
    {
        GPIOD_interruptVector[2]->interruptHandler();
    }
    if (status & GPIO_PIN_3)
    {
        GPIOD_interruptVector[3]->interruptHandler();
    }
    if (status & GPIO_PIN_4)
    {
        GPIOD_interruptVector[4]->interruptHandler();
    }
    if (status & GPIO_PIN_5)
    {
        GPIOD_interruptVector[5]->interruptHandler();
    }
    if (status & GPIO_PIN_6)
    {
        GPIOD_interruptVector[6]->interruptHandler();
    }
    if (status & GPIO_PIN_7)
    {
        GPIOD_interruptVector[7]->interruptHandler();
    }
}

inline void InterruptHandler::TIMER0_InterruptHandler(void)
{
    uint32_t status;

    status = TimerIntStatus(GPTIMER0_BASE, true);
    TimerIntClear(GPTIMER0_BASE, status);

    if ( (status & GPTIMER_TIMA_MATCH) || \
         (status & GPTIMER_CAPA_EVENT) || \
         (status & GPTIMER_TIMA_TIMEOUT) || \
         (status & GPTIMER_CAPA_MATCH) )
    {
        TIMER0_interruptVector[0]->interruptHandler();
    }

    if ( (status & GPTIMER_TIMB_MATCH) || \
         (status & GPTIMER_CAPB_EVENT) || \
         (status & GPTIMER_TIMB_TIMEOUT) || \
         (status & GPTIMER_CAPB_MATCH) )
    {
        TIMER0_interruptVector[1]->interruptHandler();
    }
}

inline void InterruptHandler::TIMER1_InterruptHandler(void)
{
    uint32_t status;

    status = TimerIntStatus(GPTIMER1_BASE, true);
    TimerIntClear(GPTIMER1_BASE, status);

    if ( (status & GPTIMER_TIMA_MATCH) || \
         (status & GPTIMER_CAPA_EVENT) || \
         (status & GPTIMER_TIMA_TIMEOUT) || \
         (status & GPTIMER_CAPA_MATCH) )
    {
        TIMER1_interruptVector[0]->interruptHandler();
    }

    if ( (status & GPTIMER_TIMB_MATCH) || \
         (status & GPTIMER_CAPB_EVENT) || \
         (status & GPTIMER_TIMB_TIMEOUT) || \
         (status & GPTIMER_CAPB_MATCH) )
    {
        TIMER1_interruptVector[1]->interruptHandler();
    }
}

inline void InterruptHandler::TIMER2_InterruptHandler(void)
{
    uint32_t status;

    status = TimerIntStatus(GPTIMER2_BASE, true);
    TimerIntClear(GPTIMER2_BASE, status);

    if ( (status & GPTIMER_TIMA_MATCH) || \
         (status & GPTIMER_CAPA_EVENT) || \
         (status & GPTIMER_TIMA_TIMEOUT) || \
         (status & GPTIMER_CAPA_MATCH) )
    {
        TIMER2_interruptVector[0]->interruptHandler();
    }

    if ( (status & GPTIMER_TIMB_MATCH) || \
         (status & GPTIMER_CAPB_EVENT) || \
         (status & GPTIMER_TIMB_TIMEOUT) || \
         (status & GPTIMER_CAPB_MATCH) )
    {
        TIMER2_interruptVector[1]->interruptHandler();
    }
}

inline void InterruptHandler::TIMER3_InterruptHandler(void)
{
    uint32_t status;

    status = TimerIntStatus(GPTIMER3_BASE, true);
    TimerIntClear(GPTIMER3_BASE, status);

    if ( (status & GPTIMER_TIMA_MATCH) || \
         (status & GPTIMER_CAPA_EVENT) || \
         (status & GPTIMER_TIMA_TIMEOUT) || \
         (status & GPTIMER_CAPA_MATCH) )
    {
        TIMER3_interruptVector[0]->interruptHandler();
    }

    if ( (status & GPTIMER_TIMB_MATCH) || \
         (status & GPTIMER_CAPB_EVENT) || \
         (status & GPTIMER_TIMB_TIMEOUT) || \
         (status & GPTIMER_CAPB_MATCH) )
    {
        TIMER3_interruptVector[1]->interruptHandler();
    }
}

inline void InterruptHandler::UART0_InterruptHandler(void)
{
    // Call the UART interrupt handler
    UART0_interruptVector->interruptHandler();
}

inline void InterruptHandler::UART1_InterruptHandler(void)
{
    // Call the UART interrupt handler
    UART1_interruptVector->interruptHandler();
}

inline void InterruptHandler::I2C_InterruptHandler(void)
{
    // Call the I2C interrupt handler
    I2C_interruptVector->interruptHandler();
}

inline void InterruptHandler::SPI0_InterruptHandler(void)
{
    // Call the SPI interrupt handler
    SPI0_interruptVector->interruptHandler();
}

inline void InterruptHandler::SPI1_InterruptHandler(void)
{
    // Call the SPI interrupt handler
    SPI1_interruptVector->interruptHandler();
}

inline void InterruptHandler::RFCore_InterruptHandler(void)
{
    // Call the RF CORE interrupt handler
    Radio_interruptVector->interruptHandler();
}

inline void InterruptHandler::RFError_InterruptHandler(void)
{
    // Call the RF ERROR interrupt handler
    Radio_interruptVector->errorHandler();
}
