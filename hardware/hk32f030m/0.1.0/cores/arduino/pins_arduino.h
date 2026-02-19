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

/*
 * Pin number mask
 * allows to retrieve the pin number without ALTx
 */
#define PNUM_MASK                   0xFF

/* Pin not defined */
#define PNUM_NOT_DEFINED            NUM_DIGITAL_PINS

#define MAX_ANALOG_INPUTS			NUM_ANALOG_INPUTS

#define TX_TIMEOUT					100


/* Default for Arduino connector compatibility */
/* SPI Definitions */
static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

/* I2C Definitions */
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#ifdef __cplusplus
extern "C" {
#endif
extern const uint8_t digitalPin[];
extern const void *digitalPort[];
extern const uint32_t digitalClock[];
extern const uint8_t digitalSource[];
extern const uint8_t analogInputPin[];
extern const void *analogInputPort[];

#define NC							-1

#define NOT_AN_INTERRUPT            NC


#define digitalPinToPin(p)         digitalPin[p]
#define digitalPinToPort(p)         ((GPIO_TypeDef *)digitalPort[p])
#define digitalPinToClock(p)         digitalClock[p]
#define digitalPinToSource(p)         digitalSource[p]


#define digitalPinIsValid(p)        (p < NUM_DIGITAL_PINS)

/* Specific for Firmata */
#if defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
#define pinIsSerial(p)              ((digitalPinToPinName(p) == \
                                      digitalPinToPinName(PIN_SERIAL_RX & PNUM_MASK)) ||\
                                     (digitalPinToPinName(p) == \
                                      digitalPinToPinName(PIN_SERIAL_TX & PNUM_MASK)))
#endif

#ifdef __cplusplus
}
#endif

/* Default Definitions, could be redefined in variant.h */
#ifndef ADC_RESOLUTION
  #define ADC_RESOLUTION            12
#endif

#ifndef PWM_RESOLUTION
  #define PWM_RESOLUTION            16
#endif

_Static_assert((ADC_RESOLUTION > 0) &&(ADC_RESOLUTION <= 32),
               "ADC_RESOLUTION must be 0 < x <= 32!");
_Static_assert((PWM_RESOLUTION > 0) &&(PWM_RESOLUTION <= 32),
               "PWM_RESOLUTION must be 0 < x <= 32!");

#ifndef PWM_FREQUENCY
  #define PWM_FREQUENCY             1000
#endif
#ifndef PWM_MAX_DUTY_CYCLE
  #define PWM_MAX_DUTY_CYCLE        65535
#endif

#endif /*_PINS_ARDUINO_H_*/
