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

#include <hk32f030m.h>

// Pin number
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const uint8_t digitalPin[] = {
	PIN_A1,
	PIN_A2,
	PIN_A3, //  - TX
	PIN_B4, //  - RX
	PIN_B5, //  - SS - SWCLK
	PIN_D1,
	PIN_D2, //  - MOSI
	PIN_D3, //  - SCK
	PIN_D4,
	PIN_D5, //  - LED - SWDIO
	PIN_D6, //  - MISO
	PIN_C3,	
	PIN_C4,
	PIN_C5, //  - SDA
	PIN_C6, //  - SCL
	PIN_C7
};

const void *digitalPort[] = {
	GPIOA,
	GPIOA,
	GPIOA, //  - TX
	GPIOB, //  - RX
	GPIOB, //  - SS - SWCLK
	GPIOD,
	GPIOD, //  - MOSI
	GPIOD, //  - SCK
	GPIOD,
	GPIOD, //  - LED - SWDIO
	GPIOD, //  - MISO
	GPIOC,	
	GPIOC,
	GPIOC, //  - SDA
	GPIOC, //  - SCL
	GPIOC
};

const uint32_t digitalClock[] = {
	RCC_AHBPeriph_GPIOA,
	RCC_AHBPeriph_GPIOA,
	RCC_AHBPeriph_GPIOA, //  - TX
	RCC_AHBPeriph_GPIOB, //  - RX
	RCC_AHBPeriph_GPIOB, //  - SS - SWCLK
	RCC_AHBPeriph_GPIOD,
	RCC_AHBPeriph_GPIOD, //  - MOSI
	RCC_AHBPeriph_GPIOD, //  - SCK
	RCC_AHBPeriph_GPIOD,
	RCC_AHBPeriph_GPIOD, //  - LED - SWDIO
	RCC_AHBPeriph_GPIOD, //  - MISO
	RCC_AHBPeriph_GPIOC,	
	RCC_AHBPeriph_GPIOC,
	RCC_AHBPeriph_GPIOC, //  - SDA
	RCC_AHBPeriph_GPIOC, //  - SCL
	RCC_AHBPeriph_GPIOC
};

const uint8_t digitalSource[] = {
	GPIO_PinSource1,
	GPIO_PinSource2,
	GPIO_PinSource3, //  - TX
	GPIO_PinSource4, //  - RX
	GPIO_PinSource5, //  - SS - SWCLK
	GPIO_PinSource1,
	GPIO_PinSource2, //  - MOSI
	GPIO_PinSource3, //  - SCK
	GPIO_PinSource4,
	GPIO_PinSource5, //  - LED - SWDIO
	GPIO_PinSource6, //  - MISO
	GPIO_PinSource3,	
	GPIO_PinSource4,
	GPIO_PinSource5, //  - SDA
	GPIO_PinSource6, //  - SCL
	GPIO_PinSource7
};

// Analog (Ax) pin number array
const uint8_t analogInputPin[] = {
  PIN_D5, //A0
  PIN_D6, //A1
  PIN_C4, //A2
  PIN_D3, //A3
  PIN_D2  //A4
};

// Analog (Ax) pin number array
const void *analogInputPort[] = {
  GPIOD, //A0
  GPIOD, //A1
  GPIOC, //A2
  GPIOD, //A3
  GPIOD  //A4
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------


