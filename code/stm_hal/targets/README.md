# Supported Targets

Target specific definitions for all the supported target boards.

### How to add a new target :

1. Add a `NAME` and a MCU name to the `POSSIBLE_TARGETS` array in `targets.cmake`
2. Create a directory with `NAME` and add a `board_defines.hpp` to it
3. Namespace is always `target_specific`
4. At minimum a UART config is needed for the debug UART output. eg:

```c++
constexpr uart::UartConfig STDOUT = {
   .uart     = uart::USART3DEF,
   .baudrate = 115200,
   .tx       = gpio::PC10,
   .rx       = gpio::PC11,
   };
```

Additionally, an RCC config is required for initial clock setup.
See `NUCLEO_L496ZG` for an example config that uses the internal oscillator at 80Mhz.
