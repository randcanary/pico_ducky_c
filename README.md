# Pico ducky c

This project leverages FreeRTOS to control a Raspberry Pi Pico to emulate a USB keyboard. The goal is to execute specific instructions (such as opening websites or performing other automated tasks) via a custom set of scripts, in other words, a bad usb. 

## Project Overview

The project is designed to run on the Raspberry Pi Pico and uses FreeRTOS. The core functionality is to detect and parse instructions that simulate keyboard inputs, sending specific key sequences to a host device.

### Key Features:
- USB Keyboard Emulation
- Runs on Raspberry Pi Pico with FreeRTOS
- Allows automated keyboard input based on predefined instructions
- Example instruction to open Rick Astley's "Never Gonna Give You Up" in the Brave browser.

## Getting Started

To get started with this project, follow the steps below:

### Prerequisites

Before you start, you need the following:
- **Raspberry Pi Pico** board.
- **FreeRTOS** kernel.
- **pico-sdk**.

Make sure that you have **Git** and **CMake** installed on your system. Additionally, ensure that you have a suitable toolchain installed for compiling and flashing the code to your Raspberry Pi Pico.

### Step 1: Clone the Repository

Clone the main repository:

```bash
git clone https://github.com/randcanary/pico_ducky_c.git
cd pico_ducky_c
```

### Step 2: Clone FreeRTOS Repository

Clone the FreeRTOS kernel repository:

```bash
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
cd FreeRTOS-Kernel
```

And move to the smp branch that supports multiple core:

```bash
git checkout -t remotes/origin/smp
git submodule update --init
```

### 3. Clone Pico SDK Repository

Clone the Pico SDK repository:

```bash
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
```

### 4. Set up CMake and Build the Project

You can now set up CMake and build the project:

```bash
mkdir build
cd build
cmake ..
make
```

### 5. New scripts

Have fun creating new scripts in the scripts folder, include the file in runner.c and call it in the runner_task.