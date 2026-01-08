# High Level Overview
This is a RISC-V emulator using the RV32I instruction set.

## Features
- Full RV32I instruction set support
- CLI and Electron GUI interfaces
- Loads and executes .mi binary programs adhering to the RV32I instruction architecture
- Supports custom binary programs with proper memory padding and syntax

## Requirements
- Node.js >= 16
- npm
- GCC
- Optional: make utility for Unix/Linux systems (see below "Running the program from command line")

## Running the program using the Electron interface
From the project root, run the following commands:
```bash
cd electron-vm-app
npm init
npm run start
```

This will launch the Electron GUI, where you can:
- Upload .mi binary programs
- View raw binary files in hexadecimal
- Execute and interact with programs
- Manage files easily

## Running the program from command line
### Initialising the program executable
**Unix/Linux Systems**:
```bash
make
```

Please note that for Unix/Linux Systems running the make command, you may notice many other files being generated. To clean these up after using the program, simply execute the following command to remove all of these extra fiels:
```bash
make clean
```

**Windows Systems**:
```bash
gcc virtual_routines.c vm.c register_dump.c instructions.c initialisation.c heapbanks.c decoding.c -o vm
```

### Running the program
To run the program, we simply need to reference the executable and provide a path to a binary file containing our instructions, for example:
```bash
./vm 5_sum.mi                   # Requests 5 integer inputs and adds them together
./vm add_2_numbers.mi           # Requests 2 integer inputs and adds them together
./vm printing_h.mi              # Prints "h"
```

**Note:** If you encounter "Permission denied", execute the following command and retry the process above:
```bash
chmod +x vm
```
This gives file permissions to execute the vm executable.

## Creating custom binary files
- The binary file ust consist of 1024 bytes for instruction memory and 1024 bytes for data memory
- If instructions do not reach 1024 bytes, pad the instruction memory with 0's to reach this size
- Data memory should initially be all padding bytes
- Total file size must be 2048 bytes; otherwise the program will not run