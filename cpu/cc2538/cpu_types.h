/**
 * @file       cpu_types.h
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

#ifndef CPU_TYPES_H_
#define CPU_TYPES_H_

/*================================ include ==================================*/

/*================================ define ===================================*/

/*================================ typedef ==================================*/

typedef uint32_t Gpio_Port_TypeDef;
typedef uint32_t Gpio_Pin_TypeDef;
typedef uint32_t Gpio_Edge_TypeDef;
typedef uint32_t Gpio_Ioc_TypeDef;
typedef uint32_t Gpio_Adc_TypeDef;

struct Gpio_TypeDef
{
    Gpio_Port_TypeDef port;
    Gpio_Pin_TypeDef  pin;
    Gpio_Edge_TypeDef edge;
    Gpio_Ioc_TypeDef  ioc;
    Gpio_Adc_TypeDef  adc;
};

typedef uint32_t I2c_Periph_TypeDef;

struct I2c_TypeDef
{
    I2c_Periph_TypeDef peripheral;
};

typedef uint32_t Spi_Periph_TypeDef;
typedef uint32_t Spi_Base_TypeDef;
typedef uint32_t Spi_Clock_TypeDef;
typedef uint32_t Spi_Interrupt_TypeDef;

struct Spi_TypeDef
{
    Spi_Periph_TypeDef    peripheral;
    Spi_Base_TypeDef      base;
    Spi_Clock_TypeDef     clock;
    Spi_Interrupt_TypeDef interrupt;
};

typedef uint32_t Timer_Periph_TypeDef;
typedef uint32_t Timer_Base_TypeDef;
typedef uint32_t Timer_Source_TypeDef;
typedef uint32_t Timer_Config_TypeDef;
typedef uint32_t Timer_Interrupt_TypeDef;
typedef uint32_t Timer_InterruptMode_TypeDef;

struct Timer_TypeDef
{
    Timer_Periph_TypeDef        peripheral;
    Timer_Base_TypeDef          base;
    Timer_Source_TypeDef        source;
    Timer_Config_TypeDef        config;
    Timer_Interrupt_TypeDef     interrupt;
    Timer_InterruptMode_TypeDef interrupt_mode;
};

typedef uint32_t Uart_Periph_TypeDef;
typedef uint32_t Uart_Base_TypeDef;
typedef uint32_t Uart_Clock_TypeDef;
typedef uint32_t Uart_Interrupt_TypeDef;

struct Uart_TypeDef
{
    Uart_Periph_TypeDef    peripheral;
    Uart_Base_TypeDef      base;
    Uart_Clock_TypeDef     clock;
    Uart_Interrupt_TypeDef interrupt;
};

/**
 * SleepMode_None:   ~2 mA,   0 + 0 us,   wake-up from any interrupt source (e.g. UART)
 * SleepMode_1:    ~600 uA, 0.5 + 4 us,   wake-up from Gpio, Sleep timer, USB resume
 * SleepMode_2:    ~1.5 uA, 136 + 136 us, wake-up from Gpio, Sleep timer
 * SleepMode_3:    ~0.8 uA, 136 + 136 us, wake-up from Gpio
 */
enum SleepMode : uint32_t {
    SleepMode_None = SYS_CTRL_PM_NOACTION,
    SleepMode_1    = SYS_CTRL_PM_1,
    SleepMode_2    = SYS_CTRL_PM_2,
    SleepMode_3    = SYS_CTRL_PM_3
};

/*=============================== variables =================================*/

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

/*================================ private ==================================*/

#endif  /* CPU_TYPES_H_ */
