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
#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Pin number
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const uint32_t digitalPin[] = {
	PA1,
	PA2,
	PA3, //  - TX
	PB4, //  - RX
	PB5, //  - SS - SWCLK
	PD1,
	PD2, //  - MOSI
	PD3, //  - SCK
	PD4,
	PD5, //  - LED - SWDIO
	PD6, //  - MISO
	PC3,	
	PC4,
	PC5, //  - SDA
	PC6, //  - SCL
	PC7
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  PD5, //A0
  PD6, //A1
  PC4, //A2
  PD3, //A3
  PD2  //A4
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------



