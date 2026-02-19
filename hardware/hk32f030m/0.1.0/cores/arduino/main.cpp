/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"

#include <src/hk32f030m_misc.h>
#ifndef RTOS_ENABLED
#include <hk32f030m_it.c>
#endif

#define NVIC_SYSTICK_CLK_BIT				( 1UL << 2UL )
#define NVIC_SYSTICK_CLK_BIT_CONFIG			( NVIC_SYSTICK_CLK_BIT )//( 0 )
#define NVIC_SYSTICK_INT_BIT				( 1UL << 1UL )
#define NVIC_SYSTICK_ENABLE_BIT				( 1UL << 0UL )

void NVIC_Configuration(void) {
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  // value between 0 and 3
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need HAL may fail.
__attribute__((constructor(101))) void premain() {
  init();
}

/*
 * \brief Main entry point of Arduino application
 */
int main(void) {
  initVariant();
  
#ifndef RTOS_ENABLED
  NVIC_Configuration();
  /*SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
  SysTick->LOAD = 1000;               // Set Reload Value
  SysTick->VAL = 0x00;                        // Set Current Value to 0
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   // Start counter*/
  /* Stop and reset the SysTick. */
  /*SysTick->CTRL = 0UL;
  SysTick->VAL = 0UL;
  // Configure SysTick to interrupt at the requested rate. 
  SysTick->LOAD = ( SystemCoreClock / 1000 ) - 1UL;
  SysTick->CTRL = ( NVIC_SYSTICK_CLK_BIT_CONFIG | NVIC_SYSTICK_INT_BIT | NVIC_SYSTICK_ENABLE_BIT );*/
  SysTick_Config(SystemCoreClock / 1000);
#endif

  setup();

  for (;;) {
#if defined(CORE_CALLBACK)
    CoreCallback();
#endif
    loop();
    serialEventRun();
  }

  return 0;
}
