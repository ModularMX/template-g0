This is the title {#mainpage}
============

The template project builds with a makefile ready to compile and link out of the box, it is not limited to build the project but also comes with several extra targets that help you run some others tasks like flashing or linting the project. But first let me explain how to add more files to the compilation process in case you need it.

You can write the new file to compile using the lines 4,5 or 6 or you can add a new line using `SRCS =+ <file to compile>.c`. in case you add more sub durectories you can add them to the `SRC_PATHS` and `INC_PATHS` variables.

```make
# Project name, you can change for any other you wish
TARGET = temp
# Files to compile. You should add here all new files for your project 
SRCS  = main.c app_ints.c app_msps.c startup_stm32g0b1xx.s system_stm32g0xx.c 
SRCS += stm32g0xx_hal.c stm32g0xx_hal_cortex.c stm32g0xx_hal_rcc.c stm32g0xx_hal_flash.c
SRCS += stm32g0xx_hal_gpio.c

# Linker file, (you can change for any other you wish)
LINKER = linker.ld

# Global symbols ( #defines )
SYMBOLS = -DSTM32G0B1xx -DUSE_HAL_DRIVER

# Directories with files to compile (.c y .s)
SRC_PATHS  = app
SRC_PATHS += cmsisg0/startups
SRC_PATHS += halg0/Src

# Directoriesn with file headers .h
INC_PATHS  = app
INC_PATHS += cmsisg0/core
INC_PATHS += cmsisg0/registers
INC_PATHS += halg0/Inc
```

## Make Targets

- **make** Build the project and recompile only the files that has been updated

```bash
$ make
...
arm-none-eabi-objcopy -Oihex Build/temp.elf Build/temp.hex
arm-none-eabi-objdump -S Build/temp.elf > Build/temp.lst
arm-none-eabi-size --format=berkeley Build/temp.elf
   text    data     bss     dec     hex filename
   2188      20    1572    3780     ec4 Build/temp.elf
```

- **make clean** Remove all the previous Build files, use this target if you want to run make again to compile from scratch

```bash
$ make clean
rm -rf Build
```

- **make flash** Transfer the build program to the microcontroller using OpenOCD

```bash
$ make flash
...
** Programming Finished **
** Verify Started **
** Verified OK **
** Resetting Target **
Info : Unable to match requested speed 2000 kHz, using 1800 kHz
Info : Unable to match requested speed 2000 kHz, using 1800 kHz
shutdown command invoked
```

- **make open** Opens a OpenOCD connection to the nucleo board. This come ins handy when you want to open a debug session using GDB

```bash
$ make open
...
Info : STLINK V2J40M27 (API v2) VID:PID 0483:374B
Info : Target voltage: 3.249376
Info : [stm32g0x.cpu] Cortex-M0+ r0p1 processor detected
Info : [stm32g0x.cpu] target has 4 breakpoints, 2 watchpoints
Info : starting gdb server for stm32g0x.cpu on 3333
Info : Listening on port 3333 for gdb connections
```
- **make debug** Opens a GDB debug session, it is mandatory to run make open in another terminal previous to run this command. GDP will init with command presented in the file .gdbinit which in turn sets load the program and set a breakpoint and also run up to the main function.

```bash
$ make debug
...
target halted due to debug-request, current mode: Thread 
xPSR: 0xf1000000 pc: 0x08000218 msp: 0x20024000
Breakpoint 1 at 0x8000198: file app/main.c, line 27.
Note: automatically using hardware breakpoints for read-only addresses.

Breakpoint 1, main () at app/main.c:27
27          HAL_Init( );
(gdb)
```

- **make docs** Generates HTML doxygen documentation from the code, this only applies to files in folders app, excluding anyother file in the project. It will try to open the Firefox browser with the generated documentation. In case you don't have Firefox installed you can open manually the file `Build/doxygen/html/index.html`

```bash
$ make docs
...
Generating file member index...
Generating example index...
finalizing index lists...
writing tag file...
Running plantuml with JAVA...
lookup cache used 11/65536 hits=0 misses=11
finished...
```
- **make lint** run the cppcheck linter to validate MISRA rules. You will need to purchase the official PDF first and then written  in file .misra

```bash
$ make lint
...
app/app_bsp.h:2:0: warning: #define and #undef shall not be used on a reserved identifier or reserved macro name [misra-c2012-21.1]
#define _BSP_H_
^
app/app_msps.c:6:6: warning: A compatible declaration shall be visible when an object or function with external linkage is defined [misra-c2012-8.4]
void HAL_MspInit( void )
     ^
```

