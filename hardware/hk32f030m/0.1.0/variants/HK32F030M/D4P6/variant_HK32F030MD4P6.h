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
 *        HK32F030M pins number
 *----------------------------------------------------------------------------*/

#define PIN_A1						0
#define PIN_A2						1
#define PIN_A3						2
#define PIN_B4						3
#define PIN_B5						4
#define PIN_D1						5
#define PIN_D2						6
#define PIN_D3						7
#define PIN_D4						8
#define PIN_D5						9
#define PIN_D6						10
#define PIN_C3						11
#define PIN_C4						12
#define PIN_C5						13
#define PIN_C6						14
#define PIN_C7						15

#define NUM_DIGITAL_PINS        16
#define NUM_ANALOG_INPUTS       5

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PIN_D5
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
  #define PIN_SPI_SS            PIN_B5
#endif
#define PIN_SPI_MOSI            PIN_D2
#define PIN_SPI_MISO            PIN_D6
#define PIN_SPI_SCK             PIN_D3

// I2C Definitions
#define PIN_WIRE_SDA            PIN_C5
#define PIN_WIRE_SCL            PIN_C6

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
  #define PIN_SERIAL_RX         PIN_B4
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PIN_A3
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
