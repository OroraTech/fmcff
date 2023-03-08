# FMcFF

Fast MicroPython Controller for Flight Faults IEEE Aerospace

This repo contains code and samples to recreate our on-board fault detection setup in another project.

It is neither a full firmware, nor does it contain the full simulations for recreating a Hardware-in-the-Loop (HiL) setup.

But it does contain our context-switching, monitor and handling code including a small sample for how to test in a HiL-manner.

## Build the Code

### Dependencies

 - `cmake`
 - `make`
 - `arm-none-eabi-g++`
 - `arm-none-eabi-newlib` - for C-headers
 - 'arm-none-eabi-binutils'

### Building

```
cd code
cmake -S . -B build
cmake --build build
```

Or use the CMake generator of your choice ;)

#### Building for Unix

To debug non-target-specific code, it might be helpful to compile and run on unix:

```
cd code
cmake -S . -B build -DFMCFF_UNIX=ON
cmake --build build
```

## License

All code in this repository (not including git submodules) is licensed under the terms and conditions of the Apache 2.0 license (See LICENSE.TXT)

```
Copyright [2023] [OroraTech GmbH]
```
