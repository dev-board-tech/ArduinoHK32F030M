#ifndef WIRING_SERIAL_H
#define WIRING_SERIAL_H

#include "variant.h"
#include "HardwareSerial.h"
#if defined (USBCON) && defined(USBD_USE_CDC)
  #include "USBSerial.h"
#endif /* USBCON && USBD_USE_CDC */
#if defined(VIRTIOCON)
  #include "VirtIOSerial.h"
#endif /* VIRTIOCON */

#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
  #if !defined(HWSERIAL_NONE) && defined(SERIAL_UART_INSTANCE)
      #define ENABLE_HWSERIAL1
      #if !defined(Serial)
        #define Serial Serial1
        #define serialEvent serialEvent1
      #endif
  #endif

  #if defined(HAVE_HWSERIAL1)
    extern void serialEvent1(void) __attribute__((weak));
  #endif
#endif /* HAL_UART_MODULE_ENABLED  && !HAL_UART_MODULE_ONLY */

extern void serialEventRun(void);

#endif /* WIRING_SERIAL_H */
