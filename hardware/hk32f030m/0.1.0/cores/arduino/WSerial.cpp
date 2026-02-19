#include "WSerial.h"
#include "pins_arduino.h"

WEAK void serialEventRun(void)
{
#if defined(HAVE_HWSERIAL1)
  if (serialEvent1 && Serial1.available()) {
    serialEvent1();
  }
#endif
}

