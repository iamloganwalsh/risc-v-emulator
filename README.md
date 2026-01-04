# High Level Overview
This is a RISC-V emulator using the RV32I instruction set.

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
The binary file should consist of 1024 bytes for instruction memory and 1024 bytes for data memory. Note that on initialisation, data memory should be all padding bytes, and if the instructions do not make up 1024 bytes, then the isntruction memory should be padded to reach this amount. If the input file is not 2048 bytes in total, then the program will not run.