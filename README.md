# Tiny OS Worksheet 2

**Name:** [Your Name]
**Student ID:** [Your ID]

## Overview
This project implements a minimal 32-bit Operating System kernel that boots via GRUB.
It includes a basic framebuffer driver to print text to the screen and C function calls.

## Task 1: Booting
- I used NASM to write the loader which sets the Multiboot magic number `0x1BADB002`.
- The `loader.asm` puts `0xCAFEBABE` into the `EAX` register.
- Verified using QEMU logs (see screenshot in repo).

## Task 2: Calling C
- Configured a stack in `loader.asm` (4KB size).
- Implemented `kmain` and the required `sum_of_three` function.
- Added `multiply_two` and `get_magic_number` as extra test functions.

## Task 3: Framebuffer Driver
- Implemented memory-mapped I/O at address `0x000B8000`.
- Created `outb` wrapper in Assembly to talk to hardware ports `0x3D4` / `0x3D5` for cursor movement.
- Implemented `fb_clear`, `fb_write`, and `fb_move`.

## How to Run
1. Install dependencies: `nasm`, `gcc`, `genisoimage`, `qemu`.
2. Build: `make os.iso`
3. Run: `make run`<img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/9ca86071-9907-4acb-9499-a8683aabbd0d" />

![hello world](https://github.com/user-attachments/assets/ebbd8c9b-b55a-4a1d-95b5-57cf02f2c968)
