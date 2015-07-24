/**
 * @file       cc2538_startup.c
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

/*================================ include ==================================*/

#include <stdint.h>

#include "cpu_include.h"

/*================================ define ===================================*/

#define DEFAULT_STACK_SIZE              ( 1024 )
#ifndef STACK_SIZE
#define STACK_SIZE                      ( DEFAULT_STACK_SIZE )
#endif

#define FLASH_START_ADDR                ( 0x00200000 )
#define BOOTLOADER_BACKDOOR_ENABLED     ( 0xF6FFFFFF ) // ENABLED: PORT A, PIN 6, LOW
#define BOOTLOADER_BACKDOOR_DISABLED    ( 0xEFFFFFFF ) // DISABLED

#ifndef HWREG
#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))
#endif

/*================================ typedef ==================================*/

typedef struct
{
    uint32_t bootloader_config;
    uint32_t image_is_valid;
    uint32_t image_vector_address;
    uint8_t  lock_page[32];
} Lock_Page_CCA_t;

/*=============================== prototypes ================================*/

static void System_Init(void);
static void System_Exit(void);

void Default_Handler(void);
void Reset_Handler(void);

extern void SystemInit(void);

extern int main (void);

extern void __libc_init_array(void);

extern void vPortSVCHandler(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);

void NMI_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void GPIO_A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void GPIO_B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void GPIO_C_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void GPIO_D_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void UART0_Handler(void)        __attribute__ ((weak, alias("Default_Handler")));
void UART1_Handler(void)        __attribute__ ((weak, alias("Default_Handler")));
void SSI0_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void I2C_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void ADC0_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void Watchdog_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void Timer0A_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void Timer0B_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void Timer1A_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void Timer1B_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void Timer2A_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void Timer2B_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void Analog_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void Radio_Handler(void)        __attribute__ ((weak, alias("Default_Handler")));
void RadioError_Handler(void)   __attribute__ ((weak, alias("Default_Handler")));
void AES_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void PKA_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void SleepTimer_Handler(void)   __attribute__ ((weak, alias("Default_Handler")));
void MacTimer_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void SSI1_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void Timer3A_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void Timer3B_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void USB_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void uDMA_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void uDMAError_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));

/*=============================== variables =================================*/

extern uint32_t _text_start;
extern uint32_t _text_end;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;

__attribute__ ((section(".stack")))
static uint8_t _stack[STACK_SIZE];

__attribute__ ((section(".flashcca"), used))
const Lock_Page_CCA_t lock_page_cca =
{
  BOOTLOADER_BACKDOOR_ENABLED,  // Bootloader backdoor enabled
  0,                            // Image valid bytes
  FLASH_START_ADDR,             // Vector table located at flash start address
  {0xFF, 0xFF, 0xFF, 0xFF,      // Unlock all pages and debug
   0xFF, 0xFF, 0xFF, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF}
};

__attribute__ ((section(".vectors"), used))
void (* const interrupt_vector[])(void) =
{
   (void (*)(void))((uint32_t)&_stack + sizeof(_stack)), // Stack pointer
   Reset_Handler,                                        // 1 Reset handler
   NMI_Handler,                                          // 2 The NMI handler
   HardFault_Handler,                                    // 3 The hard fault handler
   MemManage_Handler,                                    // 4 The MPU fault handler
   BusFault_Handler,                                     // 5 The bus fault handler
   UsageFault_Handler,                                   // 6 The usage fault handler
   0, 0, 0, 0,                                           // 7-10 Reserved
   vPortSVCHandler,                                      // 11 SVCall handler
   DebugMon_Handler,                                     // 12 Debug monitor handler
   0,                                                    // 13 Reserved
   xPortPendSVHandler,                                   // 14 The PendSV handler
   xPortSysTickHandler,                                  // 15 The SysTick handler
   GPIO_A_Handler,                                       // 16 GPIO Port A
   GPIO_B_Handler,                                       // 17 GPIO Port B
   GPIO_C_Handler,                                       // 18 GPIO Port C
   GPIO_D_Handler,                                       // 19 GPIO Port D
   0,                                                    // 20 Reserved
   UART0_Handler,                                        // 21 UART0 Rx and Tx
   UART1_Handler,                                        // 22 UART1 Rx and Tx
   SSI0_Handler,                                         // 23 SSI0 Rx and Tx
   I2C_Handler,                                          // 24 I2C Master and Slave
   0, 0, 0, 0, 0,                                        // 25-29 Reserved
   ADC0_Handler,                                         // 30 ADC Sequence 0
   0, 0, 0,                                              // 31-33 Reserved
   Watchdog_Handler,                                     // 34 Watchdog timer
   Timer0A_Handler,                                      // 35 Timer 0 subtimer A
   Timer0B_Handler,                                      // 36 Timer 0 subtimer B
   Timer1A_Handler,                                      // 37 Timer 1 subtimer A
   Timer1B_Handler,                                      // 38 Timer 1 subtimer B
   Timer2A_Handler,                                      // 39 Timer 2 subtimer A
   Timer2B_Handler,                                      // 40 Timer 2 subtimer B
   Analog_Handler,                                       // 41 Analog Comparator 0
   Radio_Handler,                                        // 42 RFCore Rx/Tx
   RadioError_Handler,                                   // 43 RFCore Error
   Default_Handler,                                      // 44 IcePick
   Default_Handler,                                      // 45 FLASH Control
   AES_Handler,                                          // 46 AES
   PKA_Handler,                                          // 47 PKA
   SleepTimer_Handler,                                   // 48 Sleep Timer
   MacTimer_Handler,                                     // 49 MacTimer
   SSI1_Handler,                                         // 50 SSI1 Rx and Tx
   Timer3A_Handler,                                      // 51 Timer 3 subtimer A
   Timer3B_Handler,                                      // 52 Timer 3 subtimer B
   0, 0, 0, 0, 0, 0, 0,                                  // 53-59 Reserved
   USB_Handler,                                          // 60 USB
   0,                                                    // 61 Reserved
   uDMA_Handler,                                         // 62 uDMA
   uDMAError_Handler,                                    // 63 uDMA Error
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 64-73 Reserved
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 74-83 Reserved
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 84-93 Reserved
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 94-103 Reserved
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 104-113 Reserved
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 114-123 Reserved
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 124-133 Reserved
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 134-143 Reserved
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         // 144-143 Reserved
   0, 0,                                                 // 154-155 Reserved
   USB_Handler,                                          // 156 USB
   Radio_Handler,                                        // 157 RFCORE RX/TX
   RadioError_Handler,                                   // 158 RFCORE Error
   AES_Handler,                                          // 159 AES
   PKA_Handler,                                          // 160 PKA
   SleepTimer_Handler,                                   // 161 SMTimer
   MacTimer_Handler                                      // 162 MACTimer
};

/*================================= public ==================================*/

void Default_Handler(void)
{
    while (1)
    {
        __asm("nop");
    }
}

void Reset_Handler(void)
{
    volatile uint32_t *src, *dst;

    /* Workaround for PM debug issue */
    HWREG(SYS_CTRL_EMUOVR) = 0xFF;

    /* Workaround for J-Link debug issue */
    HWREG(NVIC_VTABLE) = (uint32_t)interrupt_vector;

    /* Copy the data segment initializers from flash to SRAM */
    for (src = &_text_end, dst = &_data_start; dst < &_data_end; )
    {
        *dst++ = *src++;
    }

    /* Initialize the BSS section to zero */
    for (dst = &_bss_start; dst < &_bss_end; *dst++)
    {
        *dst = 0;
    }

    /* Initialize the system */
    System_Init();

    /* Initialize standard C library */
    __libc_init_array();

   /* Call the application's entry point */
   main();

   /* End here if return from main() */
   System_Exit();
}

/*================================ private ==================================*/

static void System_Init(void)
{
    SystemInit();
}

static void System_Exit(void)
{
    while (1)
    {
        __asm("nop");
    }
}
