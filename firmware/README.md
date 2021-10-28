# STM32-FreeRTOS Buildchain Example

__Goal:__ The purpose of this repository and documentation is to demonstrate a buildchain
implementation for the STM32F103C8 (STM32) microcontroller found on the _STM32 Blue Pill_ dev board.

## Components

* __CMake__ is used to generate the build tools. It is used to generate Makefiles that are
then used to compile code.
* [__libopencm3__](https://github.com/libopencm3/libopencm3) is used as a _hardware abstraction library (HAL)_ for the STM32.
* [__FreeRTOS__](https://freertos.org) is the real-time operating system used. It exposes APIs like threads,
queues, semaphores, mutexes, and other helpful constructs.

## How They Work

## Resources

_There are lots..._

* [STM32F103 CMake Template](https://bitbucket.org/dimtass/stm32f103-cmake-template/src/master/) - Used as inspiration/source for a lot of CMake things
    * [Accompanying article](https://www.stupid-projects.com/stm32-cmake-template-new-with-cool-stuff/)
* [libopencm3 Examples](https://github.com/libopencm3/libopencm3-examples)
* [Bare-metal Example](https://user-images.githubusercontent.com/26856618/33801623-616b3e14-dd15-11e7-951b-94d278fffb02.png)
* [STM32 Blue Pill ARM development](https://satoshinm.github.io/blog/171212_stm32_blue_pill_arm_development_board_first_look_bare_metal_programming.html)
* [Blue Pill/Make/GCC Environment](https://geokon-gh.github.io/bluepill/)
* [cmake-stm32](https://github.com/Teivaz/cmake-stm32)
* [Programming a microcontroller without an IDE](https://teivaz.com/the-microcontroller-and-how-to-program-it-without-an-ide/)
* [STM32 Development without an IDE](https://teivaz.com/the-microcontroller-and-how-to-program-it-without-an-ide/)
