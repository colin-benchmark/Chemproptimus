# Requirements

## VS Code
 - [VSC C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
 - [VSC Cortex-Debug extension](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)

## OpenOCD
 - Version 0.12.0
 - Linux:
    - Didn't work with version 0.10.0 which is the debian default
    - Latest version installed from [here](https://github.com/xpack-dev-tools/openocd-xpack/releases)

## GNU ARM Embedded Toolchain
 - Tested using version 10.3-2021.10
 - Linux:
    - Remove any version installed via apt
    - Manually install latest version [from here](https://developer.arm.com/downloads/-/gnu-rm)

# Building
 - From within VS Code press `ctrl + shift + b` and select `Build`

# Debugging
 - Using the Debug tab within the VS Code explorer hit the `Play` button
 - Any issues are likely to be from `cortex-debug.openocdPath` being incorrect in `.vscode/settings.json`
    - TODO: Install openocd as a system package rather than in my `.local` folder

# Ninja
    cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-gcc.cmake -GNinja
    cmake --build build
