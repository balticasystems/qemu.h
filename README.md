# qemu.h

A single-header C library that exposes QEMU's virtual hardware, SiFive machine layout, UART, and other emulated peripherals, to bare-metal bootloader and kernel code.

## Why this exists

Before real silicon (or even an FPGA bitstream) is in the loop, QEMU stands in as the target platform. `qemu.h` is the thin, dependency-free layer that lets a bootloader or kernel talk to QEMU's emulated devices without hand-rolling register offsets and memory maps every time. It's meant to be dropped straight into a freestanding bootloader/kernel build with `#include "qemu.h"` - no build system, no linking, just one header.

## What's in here

- Memory-mapped register definitions and addresses for QEMU's SiFive-based RISC-V machine
- UART access (init, putchar/getchar-style primitives) for early boot console output
- Header-only, freestanding-friendly, no libc dependency, suitable for bootloader/early-kernel contexts

*(More devices will be added as the bootloader and kernel grow: CLINT/PLIC, timers, virtio, etc. Contributions welcome.)*

## Usage

```c
#include "qemu.h"

void _start(void) {
    uart_init();
    uart_puts("hello from the bootloader\n");
    // ...
}
```

Build/run against QEMU's `virt` machine (RISC-V SiFive-based), e.g.:

```sh
qemu-system-riscv64 -machine virt -nographic -bios none -kernel your_bootloader.elf
```

## Status

Early stage and actively evolving alongside the bootloader/kernel it supports. Expect the API to shift as more of QEMU's virtual devices get wired in. Not much active development right now, but the project is very much alive - issues and PRs are welcome, and slow-but-steady progress continues.

## Contributing

Issues, PRs, and ideas are all welcome, especially around additional QEMU device support (CLINT/PLIC, virtio, timers).

