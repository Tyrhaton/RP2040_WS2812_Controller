# RP2040-WS2812-Controller
![Version](https://img.shields.io/badge/version-1.0.0-green.svg)

A repository with c code for controlling WS2812 RGB LEDs using RP2040-based boards, including the Raspberry Pi Pico and Pico W. Provides custom drivers and examples for dynamic lighting effects.

# Dependencies
1. [RP2040_UART_Debugger](https://github.com/Tyrhaton/RP2040_UART_Debugger)
   A repository demonstrating UART communication using the Raspberry Pi Pico Debug Probe with RP2040-based boards. 

# Setup Instructions

## Option 1: Standalone Project Setup
1. Import the dependencies into the root directory:
   ```bash
   git clone https://github.com/Tyrhaton/RP2040_UART_Debugger.git
   ```

2. Create a build directory within the root directory:
   ```bash
   mkdir build
   ```

3. Navigate into the build directory:
   ```bash
   cd build
   ```

4. Generate the build files using CMake:
   ```bash
   cmake ..
   ```

5. Compile the project:
   ```bash
   make
   ```
   * Tip: Use `make -j4` to enable parallel compilation for faster build times.

6. Run the project using OpenOCD:
   ```bash
   sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program main.elf verify reset exit"
   ```

---

## Option 2: Integration into Another Project

1. Navigate to your project's `modules` directory:
   ```bash
   cd modules/
   ```

2. Clone this repository into the modules directory:
   ```bash
   git clone https://github.com/Tyrhaton/RP2040_WS2812_Controller.git
   ```

3. Update your project's `CMakeLists.txt`:
   ```bash
   # Add the RP2040_WS2812_Controller module
   add_library(RP2040_WS2812_Controller STATIC
     modules/RP2040_WS2812_Controller/led.c
   )

   # Include the RP2040_WS2812_Controller module's header files
   target_include_directories(RP2040_WS2812_Controller PUBLIC modules/RP2040_WS2812_Controller)

   # Link the main executable with the RP2040_WS2812_Controller library and Pico SDK
   target_link_libraries(${PROJECT_NAME} RP2040_WS2812_Controller pico_stdlib)
    ```

4. Make sure to also do these steps for the dependencies!

5. Run the project using OpenOCD:
   ```bash
   sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program main.elf verify reset exit"
   ```