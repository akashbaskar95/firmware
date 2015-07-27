/**
 * @file       openmote-cc2538.cpp
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include "openmote-cc2538.h"

/*================================ define ===================================*/

/*================================ typedef ==================================*/

/*=============================== variables =================================*/

Gpio_TypeDef led_green_data  = {LED_GREEN_PORT, LED_GREEN_PIN};
Gpio_TypeDef led_orange_data = {LED_ORANGE_PORT, LED_ORANGE_PIN};
Gpio_TypeDef led_red_data    = {LED_RED_PORT, LED_RED_PIN};
Gpio_TypeDef led_yellow_data = {LED_YELLOW_PORT, LED_YELLOW_PIN};

Gpio_TypeDef debug_ad0_data = {GPIO_DEBUG_AD0_PORT, GPIO_DEBUG_AD0_PIN};
Gpio_TypeDef debug_ad1_data = {GPIO_DEBUG_AD1_PORT, GPIO_DEBUG_AD1_PIN};
Gpio_TypeDef debug_ad2_data = {GPIO_DEBUG_AD2_PORT, GPIO_DEBUG_AD2_PIN};

Gpio_TypeDef button_user_data = {BUTTON_USER_PORT, BUTTON_USER_PIN, BUTTON_USER_EDGE};

Gpio_TypeDef bypass_data = {TPS62730_PORT, TPS62730_BYPASS_PIN};
Gpio_TypeDef status_data = {TPS62730_PORT, TPS62730_STATUS_PIN, TPS62730_STATUS_EDGE};

Gpio_TypeDef i2c_scl_data = {I2C_BASE, I2C_SCL};
Gpio_TypeDef i2c_sda_data = {I2C_BASE, I2C_SDA};
I2c_TypeDef i2c_data      = {I2C_PERIPHERAL};

Gpio_TypeDef gpio_uart_rx_data = {UART_RX_PORT, UART_RX_PIN, 0, UART_RX_IOC};
Gpio_TypeDef gpio_uart_tx_data = {UART_TX_PORT, UART_TX_PIN, 0, UART_TX_IOC};
Uart_TypeDef uart_data         = {UART_PERIPHERAL, UART_BASE, UART_CLOCK, UART_INTERRUPT};

Gpio_TypeDef gpio_spi_miso = {SPI_MISO_BASE, SPI_MISO_PIN, 0, SPI_MISO_IOC};
Gpio_TypeDef gpio_spi_mosi = {SPI_MOSI_BASE, SPI_MOSI_PIN, 0, SPI_MOSI_IOC};
Gpio_TypeDef gpio_spi_clk  = {SPI_CLK_BASE, SPI_CLK_PIN, 0, SPI_CLK_IOC};
Gpio_TypeDef gpio_spi_ncs  = {SPI_nCS_BASE, SPI_nCS_PIN, 0, SPI_nCS_IOC};
Spi_TypeDef spi_data       = {SPI_PERIPHERAL, SPI_BASE, SPI_CLOCK, INT_SSI0};

Gpio_TypeDef gpio_enc28j60_data = {ENC28J60_INT_PORT, ENC28J60_INT_PIN, ENC28J60_INT_EDGE};

// Board management
Board board;
Watchdog watchdog(WATCHDOG_INTERVAL);

// Debug pins
GpioOut debug_ad0(debug_ad0_data);
GpioOut debug_ad1(debug_ad1_data);
GpioOut debug_ad2(debug_ad2_data);

// Leds
GpioOut led_green(led_green_data);
GpioOut led_orange(led_orange_data);
GpioOut led_red(led_red_data);
GpioOut led_yellow(led_yellow_data);

// Button
GpioInPow button_user(button_user_data);

// Timer
Timer_TypeDef timer0_data = {TIMER0_PERIPHERAL, TIMER0_BASE, TIMER0_SOURCE, TIMER0_CONFIG, TIMER0_INTERRUPT, TIMER0_INTERRUPT_MODE};
Timer_TypeDef timer1_data = {TIMER1_PERIPHERAL, TIMER1_BASE, TIMER1_SOURCE, TIMER1_CONFIG, TIMER1_INTERRUPT, TIMER1_INTERRUPT_MODE};
Timer_TypeDef timer2_data = {TIMER2_PERIPHERAL, TIMER2_BASE, TIMER2_SOURCE, TIMER2_CONFIG, TIMER2_INTERRUPT, TIMER2_INTERRUPT_MODE};
Timer_TypeDef timer3_data = {TIMER3_PERIPHERAL, TIMER3_BASE, TIMER3_SOURCE, TIMER3_CONFIG, TIMER3_INTERRUPT, TIMER3_INTERRUPT_MODE};

Timer timer0(timer0_data);
Timer timer1(timer1_data);
Timer timer2(timer2_data);
Timer timer3(timer3_data);

// SleepTimer
SleepTimer sleepTimer(SLEEP_TIMER_INTERRUPT);

// RadioTimer
RadioTimer radioTimer(RADIO_TIMER_INTERRUPT);

// I2C peripheral
GpioI2c i2c_scl(i2c_scl_data);
GpioI2c i2c_sda(i2c_sda_data);
I2c i2c(i2c_data, i2c_scl, i2c_sda);

// SPI peripheral
GpioSpi spi_miso(gpio_spi_miso);
GpioSpi spi_mosi(gpio_spi_mosi);
GpioSpi spi_clk(gpio_spi_clk);
GpioSpi spi_ncs(gpio_spi_ncs);
Spi spi(spi_data, spi_miso, spi_mosi, spi_clk, spi_ncs);

// UART peripheral
GpioUart gpio_uart_rx(gpio_uart_rx_data);
GpioUart gpio_uart_tx(gpio_uart_tx_data);
Uart uart(uart_data, gpio_uart_rx, gpio_uart_tx);

// IEEE 802.15.4 radio
Radio radio;

// Step-down DC/DC converter
#ifdef USE_DRIVER_TPS62730
GpioOut bypass(bypass_data);
GpioIn status(status_data);
Tps62730 tps62730(bypass, status);
#endif

// Acceleration sensor
#ifdef USE_DRIVER_ADXL346
Gpio_TypeDef gpio_adxl346_data = {ADXL346_INT_PORT, ADXL346_INT_PIN, ADXL346_INT_EDGE};
GpioInPow adxl346_int(gpio_adxl346_data);
Adxl346 adxl346(i2c, adxl346_int);
#endif

// Light sensor
#ifdef USE_DRIVER_MAX44009
Gpio_TypeDef gpio_max44009_data = {MAX44009_INT_PORT, MAX44009_INT_PIN, MAX44009_INT_EDGE};
GpioIn max44009_int(gpio_max44009_data);
Max44009 max44009(i2c, max44009_int);
#endif

// Temperature + Relative humidity sensor
#ifdef USE_DRIVER_SHT21
Sht21 sht21(i2c);
#endif

// Ethernet PHY + MAC chip
#ifdef USE_DRIVER_ENC28J60
GpioIn enc28j60_int(gpio_enc28j60_data);
Enc28j60 enc28j60(spi, enc28j60_int);
#endif

/*=============================== prototypes ================================*/

/*================================= public ==================================*/

/*================================ private ==================================*/

