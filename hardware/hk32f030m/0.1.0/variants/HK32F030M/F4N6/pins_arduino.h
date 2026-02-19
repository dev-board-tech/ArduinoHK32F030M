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
#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> /* Required for static_assert */
#include "variant.h"

#include "hk_def_build.h"

#if defined (  __GNUC__  ) /* GCC CS3 */
  #define WEAK __attribute__ ((weak))
#endif

#ifndef UNUSED
#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */
#endif /* UNUSED */

#define __IO						volatile
/*
 * Pin number mask
 * allows to retrieve the pin number without ALTx
 */
#define PNUM_MASK                   0xFF

/* Pin not defined */
#define PNUM_NOT_DEFINED            NUM_DIGITAL_PINS

#define MAX_ANALOG_INPUTS			5

#define TX_TIMEOUT					100

/* Avoid PortName issue */
//_Static_assert(LastPort <= 0x0F, "PortName must be less than 16");

_Static_assert(NUM_ANALOG_INPUTS <= MAX_ANALOG_INPUTS,
               "Core NUM_ANALOG_INPUTS limited to MAX_ANALOG_INPUTS");

/* Default for Arduino connector compatibility */
/* SPI Definitions */
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS                10
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1               4
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2               7
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3               8
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI              11
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO              12
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK               13
#endif

static const uint32_t SS   = PIN_SPI_SS;
static const uint32_t SS1  = PIN_SPI_SS1;
static const uint32_t SS2  = PIN_SPI_SS2;
static const uint32_t SS3  = PIN_SPI_SS3;
static const uint32_t MOSI = PIN_SPI_MOSI;
static const uint32_t MISO = PIN_SPI_MISO;
static const uint32_t SCK  = PIN_SPI_SCK;

/* I2C Definitions */
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA              14
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL              15
#endif

static const uint32_t SDA = PIN_WIRE_SDA;
static const uint32_t SCL = PIN_WIRE_SCL;

#ifdef __cplusplus
extern "C" {
#endif
extern const uint32_t digitalPin[];
extern const uint32_t analogInputPin[];

#define NC							-1

#define NOT_AN_INTERRUPT            (uint32_t)NC

#define ALTX_MASK					0xFF // ??
#define PNUM_ANALOG_BASE			0 // ??
#define NUM_ANALOG_INTERNAL_FIRST	0 // ??
#define PNUM_ANALOG_INDEX			0 // ??
#define MAX_NB_PORT					0 // ??

/* Convert a digital pin number Dxx to a uint32_t PX_n */
#if NUM_ANALOG_INPUTS > 0
/* Note: Analog pin is also a digital pin */
#define digitalPinToPinName(p)      ((((uint32_t)(p) & PNUM_MASK) < NUM_DIGITAL_PINS) ? \
            (uint32_t)(digitalPin[(uint32_t)(p) & PNUM_MASK] | ((p) & ALTX_MASK)) : \
            (((uint32_t)(p) & PNUM_ANALOG_BASE) == PNUM_ANALOG_BASE) && \
            (((uint32_t)(p) & PNUM_MASK) < NUM_ANALOG_INTERNAL_FIRST) ? \
            (uint32_t)(digitalPin[analogInputPin[(p) & PNUM_ANALOG_INDEX]] | ((p) & ALTX_MASK)) : NC)
#else
#define digitalPinToPinName(p)      ((((uint32_t)(p) & PNUM_MASK) < NUM_DIGITAL_PINS) ? \
            (uint32_t)(digitalPin[(uint32_t)(p) & PNUM_MASK] | ((p) & ALTX_MASK)) : NC)
#endif /* NUM_ANALOG_INPUTS > 0 */
/* Convert a uint32_t PX_n to a digital pin number */
uint32_t pinNametoDigitalPin(uint32_t p);

/* Convert an analog pin number to a digital pin number */
#if NUM_ANALOG_INPUTS > 0
/* Used by analogRead api to have A0 == 0 */
/* Non contiguous analog pins definition in digitalPin array */
#define analogInputToDigitalPin(p)  ((((uint32_t)(p) & PNUM_MASK) < NUM_ANALOG_INPUTS) ? \
            analogInputPin[(uint32_t)(p) & PNUM_MASK] | ((uint32_t)(p) & ALTX_MASK) : \
            (((uint32_t)(p) & PNUM_ANALOG_BASE) == PNUM_ANALOG_BASE) && \
            (((uint32_t)(p) & PNUM_MASK) < NUM_ANALOG_INTERNAL_FIRST) ? \
            analogInputPin[(p) & PNUM_ANALOG_INDEX] | ((uint32_t)(p) & ALTX_MASK) : (uint32_t)NC)
#else/* No analog pin defined */
#define analogInputToDigitalPin(p)  (NUM_DIGITAL_PINS)
#endif /* NUM_ANALOG_INPUTS > 0 */

/* Convert an analog pin number Ax to a uint32_t PX_n */
uint32_t analogInputToPinName(uint32_t pin);

/* All pins could manage EXTI */
#define digitalPinToInterrupt(p)    (digitalPinIsValid(p) ? p : NOT_AN_INTERRUPT)

#define digitalPinHasI2C(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SDA) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SCL))
#define digitalPinHasPWM(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_TIM))
#define digitalPinHasSerial(p)      (pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_RX) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_TX))
#define digitalPinHasSPI(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MOSI) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MISO) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SCLK) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SSEL))


#define digitalPinToPort(p)         0//(get_GPIO_Port(STM_PORT(digitalPinToPinName(p))))
#define digitalPinToBitMask(p)      0//(STM_GPIO_PIN(digitalPinToPinName(p)))

#define analogInPinToBit(p)         0//(STM_GPIO_PIN(digitalPinToPinName(p)))
#define portOutputRegister(P)       (NULL)//(&(P->ODR))
#define portInputRegister(P)        (NULL)//(&(P->IDR))

#define portSetRegister(P)          (NULL)//(&(P->BSRR))
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
/* For those series reset are in the high part so << 16U needed */
#define portClearRegister(P)        (&(P->BSRR))
#else
#define portClearRegister(P)        (NULL)//(&(P->BRR))
#endif


#if defined(STM32F1xx)
/*
 * Config registers split in 2 registers:
 * CRL: pin 0..7
 * CRH: pin 8..15
 * Return only CRL
 */
#define portModeRegister(P)         (&(P->CRL))
#else
#define portModeRegister(P)         (&(P->MODER))
#endif
#define portConfigRegister(P)       (portModeRegister(P))


#define digitalPinIsValid(p)        (digitalPinToPinName(p) != NC)

/* As some pin could be duplicated in digitalPin[] */
/* return first occurrence of linked uint32_t (PYx) */
#define digitalPinFirstOccurence(p) (pinNametoDigitalPin(digitalPinToPinName(p)))

/* Specific for Firmata */
#if defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
#define pinIsSerial(p)              ((digitalPinToPinName(p) == \
                                      digitalPinToPinName(PIN_SERIAL_RX & PNUM_MASK)) ||\
                                     (digitalPinToPinName(p) == \
                                      digitalPinToPinName(PIN_SERIAL_TX & PNUM_MASK)))
#endif
/* Convenient macro to handle Analog for Firmata */
#define pinIsAnalogInput digitalpinIsAnalogInput
bool digitalpinIsAnalogInput(uint32_t pin);
uint32_t digitalPinToAnalogInput(uint32_t pin);

#ifdef __cplusplus
}
#endif

/* Default Definitions, could be redefined in variant.h */
#ifndef ADC_RESOLUTION
  #define ADC_RESOLUTION            10
#endif

#define DACC_RESOLUTION             12

#ifndef PWM_RESOLUTION
  #define PWM_RESOLUTION            8
#endif

_Static_assert((ADC_RESOLUTION > 0) &&(ADC_RESOLUTION <= 32),
               "ADC_RESOLUTION must be 0 < x <= 32!");
_Static_assert((PWM_RESOLUTION > 0) &&(PWM_RESOLUTION <= 32),
               "PWM_RESOLUTION must be 0 < x <= 32!");

#ifndef PWM_FREQUENCY
  #define PWM_FREQUENCY             1000
#endif
#ifndef PWM_MAX_DUTY_CYCLE
  #define PWM_MAX_DUTY_CYCLE        4095
#endif

#endif /*_PINS_ARDUINO_H_*/
