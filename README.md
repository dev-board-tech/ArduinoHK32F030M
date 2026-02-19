# Arduino core support HK32F030M

Currently no Arduino api/glue is implemeted, no specific pins_arduino.h for each version is updated, everything that is platform dependent is commented waiting to be developed, as it is you can call the device derivers API directly as in Example_HK32F030MF4P6.

Anyone can fork it and contribute, the only request is to talk between us to synchronize about parts that each one want to contribute, to avoid for now for two or more people working to the same thing at the same time.

Taking into account that those chips use a baremetal implementation of cortex-m0 and they have a small program memory (16KB of FLASH), if you can write drivers in ASM for good code size optimization is a plus.

I don't bother if the code is ugly or not optimized, I will take care of it and optimize it, the only request is to run, those chips are very cheap and the power consumption for the processing power is very good and deserve they'r Arduino implementation for everyone to enjoy using them.
