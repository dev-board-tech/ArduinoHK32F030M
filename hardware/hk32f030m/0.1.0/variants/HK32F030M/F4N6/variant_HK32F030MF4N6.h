/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#pragma once

/*----------------------------------------------------------------------------
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
// USB connector on the top, MCU side
// Left Side
/*#define PA0                     PIN_A0 //D0/A0
#define PA1                     PIN_A1 //D1/A1
#define PA2                     PIN_A2 //D2/A2 - TX
#define PA3                     PIN_A3 //D3/A3 - RX
#define PA4                     PIN_A4 //D4/A4 - LED
// Right side
#define PA5                     PIN_A5 //D5/A5 - SCK
#define PA6                     PIN_A6 //D6/A6 - MISO
#define PA7                     PIN_A7 //D7/A7 - MOSI
#define PB1                     PIN_A8 //D8/A8 - SS
#define PA9                     9      //D9    - SCL (TX UART header)
#define PA10                    10     //D10   - SDA (RX UART header)
#define PA13                    11     //D11   - SWDIO
#define PA14                    12     //D12   - SWCLK
// Boards without a crystal can use these pins as well:
#define PF0                     13
#define PF1                     14*/


#define PA1						0
#define PA2						1
#define PA3						2
#define PB4						3
#define PB5						4
#define PD1						5
#define PD2						6
#define PD3						7
#define PD4						8
#define PD5						9
#define PD6						10
#define PC3						11
#define PC4						12
#define PC5						13
#define PC6						14
#define PC7						15

// Alternate pins number
#define PA6_ALT1                (PA6 | ALT1)
#define PA7_ALT1                (PA7 | ALT1)
#define PA7_ALT2                (PA7 | ALT2)
#define PA7_ALT3                (PA7 | ALT3)
#define PB1_ALT1                (PB1 | ALT1)
#define PB1_ALT2                (PB1 | ALT2)

#define NUM_DIGITAL_PINS        15
#define NUM_ANALOG_INPUTS       4

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PD5
#endif
#ifndef LED_GREEN
  #define LED_GREEN             LED_BUILTIN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PB5
#endif
#define PIN_SPI_MOSI            PD2
#define PIN_SPI_MISO            PD6
#define PIN_SPI_SCK             PD3

// I2C Definitions
#define PIN_WIRE_SDA            PC5
#define PIN_WIRE_SCL            PC6

// Timer Definitions
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM14
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM16
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB4
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA3
#endif

#ifdef ARDUINO_DEMO_F030F4_16M
  #define HSE_VALUE             16000000U  /*!< Value of the External oscillator in Hz */
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/
#ifdef __cplusplus
  // These serial port names are intended to allow libraries and architecture-neutral
  // sketches to automatically default to the correct port name for a particular type
  // of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
  // the first hardware serial port whose RX/TX pins are not dedicated to another use.
  //
  // SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
  //
  // SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
  //
  // SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
  //
  // SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
  //
  // SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
  //                            pins are NOT connected to anything by default.
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
#endif
