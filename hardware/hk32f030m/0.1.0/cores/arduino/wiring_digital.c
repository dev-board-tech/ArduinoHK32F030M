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
#include <src/hk32f030m_gpio.h>

#ifdef __cplusplus
extern "C" {
#endif


//extern uint32_t g_anOutputPinConfigured[MAX_NB_PORT];

void pinMode(uint32_t ulPin, uint32_t ulMode) {
  //uint32_t p = 0;//digitalPinToPinName(ulPin);
  if (ulPin < NUM_DIGITAL_PINS) {
#if 0
    // If the pin that support PWM or DAC output, we need to turn it off
#if (defined(HAL_DAC_MODULE_ENABLED) && !defined(HAL_DAC_MODULE_ONLY)) ||\
    (defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY))
    if (is_pin_configured(p, g_anOutputPinConfigured)) {
#if defined(HAL_DAC_MODULE_ENABLED) && !defined(HAL_DAC_MODULE_ONLY)
      if (pin_in_pinmap(p, PinMap_DAC)) {
        dac_stop(p);
      } else
#endif //HAL_DAC_MODULE_ENABLED && !HAL_DAC_MODULE_ONLY
#if defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY)
        if (pin_in_pinmap(p, PinMap_TIM)) {
          pwm_stop(p);
        }
#endif //HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY
      {
        reset_pin_configured(p, g_anOutputPinConfigured);
      }
    }
#endif
#endif
	GPIO_InitTypeDef GPIO_InitStructure;
	// Enable AHB Clock
	RCC_AHBPeriphClockCmd(digitalPinToClock(ulPin), ENABLE);
	GPIO_InitStructure.GPIO_Pin = digitalPinToPin(ulPin);
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Schmit = GPIO_Schmit_Disable;

    switch (ulMode) {
      case INPUT: /* INPUT_FLOATING */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Schmit = GPIO_Schmit_Enable;
        break;
      case INPUT_PULLUP:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Schmit = GPIO_Schmit_Enable;
        break;
      case INPUT_PULLDOWN:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStructure.GPIO_Schmit = GPIO_Schmit_Enable;
        break;
      case INPUT_ANALOG:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  		GPIO_PinAFConfig(digitalPinToPort(ulPin), digitalPinToSource(ulPin), GPIO_AF_7);
        break;
      case OUTPUT:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        break;
      case OUTPUT_OPEN_DRAIN:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        break;
      default:
        return;
    }
	GPIO_Init(digitalPinToPort(ulPin), &GPIO_InitStructure);
  }
}

void digitalWrite(uint32_t ulPin, uint32_t ulVal) {
  if (ulPin < NUM_DIGITAL_PINS) {
    GPIO_WriteBit(digitalPinToPort(ulPin), digitalPinToPin(ulPin), ulVal);
  }
}

int digitalRead(uint32_t ulPin) {
  if (ulPin < NUM_DIGITAL_PINS) {
  	return GPIO_ReadInputDataBit(digitalPinToPort(ulPin), digitalPinToPin(ulPin));
  }
  return 0;
}

void digitalToggle(uint32_t ulPin) {
  if (ulPin < NUM_DIGITAL_PINS) {
    GPIO_Toggle(digitalPinToPort(ulPin), digitalPinToPin(ulPin));
  }
}

#ifdef __cplusplus
}
#endif
