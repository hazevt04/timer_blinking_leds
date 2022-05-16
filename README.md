Timer Blinking LEDs
===================================
This causes two LEDs to blink on a Raspberry Pi 3 B while in Linux. (It is not bare metal).
One LED blinks every 65 ms while the other blinks five times every 3 seconds.

Dependencies
===================================
This uses the GPIOD Library from:
github.com/brgl/libgpiod

It is included as a submodule.


Build Instructions
===================================
```bash
mkdir build && cd build && cmake ..
make
```

Install Instructions
===================================
```bash
make install
```

Run
===================================
```bash
./bin/timer_blinking_leds
```

