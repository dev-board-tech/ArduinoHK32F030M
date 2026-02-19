/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef RTOS_ENABLED
uint32_t SysTick_Cnt = 0;
#endif
uint32_t millis(void) {
  // ToDo: ensure no interrupts
#ifndef RTOS_ENABLED
  return SysTick_Cnt;
#else
  return xTaskGetTickCount();
#endif
}

// Interrupt-compatible version of micros
uint32_t micros(void) {
#ifndef RTOS_ENABLED
  return (SysTick_Cnt * 1000) + SysTick->VAL;
#else
  return (xTaskGetTickCount() * 1000) + (SysTick->VAL / ( SystemCoreClock / 1000 ));
#endif
}

void delay(uint32_t ms) {
  if (ms != 0) {
    uint32_t start = millis();
    do {
      yield();
    } while (millis() - start < ms);
  }
}

#ifndef RTOS_ENABLED
void SysTick_Handler(void) {
	SysTick_Cnt++;
}
#endif

#ifdef __cplusplus
}
#endif
