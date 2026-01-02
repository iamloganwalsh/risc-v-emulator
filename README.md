# High Level Overview
This is a RISC-V emulator using the RV32I instruction set.

## Running the program from command line
From the project root, execute the following commands:
```bash
make
./vm
```

To clean up any extra files you may notice (such as .d or .o extensions), simply execute:
```bash
make clean
```

**Note:** If you encounter "Permission denied", execute the following command and retry the process above:
```bash
chmod +x vm
```
This gives file permissions to execute the vm executable.