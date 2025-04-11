# About Computer
CHAR 8 16 bit computer, have 4095 byte address rom space and 255 byte ram address space. He have 16 bit Registers: Accumulator, Z register, X register. Carry flag, Zero flag, Negative flag.  Terminal using for print char info or input and print char info. The terminal uses 16 columns and 33 line registers (y, x).

### CPU Operations
Below are the operations available for the CPU:

### Arithmetic and Load Operations
- **`LDA (0x01)`**: Load value into the accumulator.
- **`STZ (0x02)`**: Load value into the Z register.
- **`STX (0x03)`**: Load value into the X register.
- **`ADD_Z (0x04)`**: Add the value from the Z register to the accumulator (A += Z).
- **`ADD_X (0x05)`**: Add the value from the X register to the accumulator (A += X).
- **`SUB_Z (0x06)`**: Subtract the value from the Z register from the accumulator (A -= Z).
- **`SUB_X (0x07)`**: Subtract the value from the X register from the accumulator (A -= X).

### Flag Operations
- **`SCF (0x08)`**: Set the carry flag (CF = 1).
- **`SZF (0x09)`**: Set the zero flag (ZF = 1).
- **`SNF (0xA)`**: Set the negative flag (NF = 1).

### Control Flow Operations
- **`JMS (0xC)`**: Call a subroutine.
- **`END (0x10)`**: End the program.

### Increment/Decrement Operations
- **`IAC (0xE2)`**: Increment the accumulator (A += 1).
- **`IZC (0xE3)`**: Increment the Z register (Z += 1).
- **`IXC (0xE4)`**: Increment the X register (X += 1).
- **`DAC (0xE5)`**: Decrement the accumulator (A -= 1).
- **`DZC (0xE6)`**: Decrement the Z register (Z -= 1).
- **`DXC (0xE7)`**: Decrement the X register (X -= 1).

### Shift Operations
- **`RAC (0xE8)`**: Multiply the accumulator by 2 (A << 1).
- **`RAZ (0xE9)`**: Multiply the Z register by 2 (Z << 1).
- **`RAX (0xEA)`**: Multiply the X register by 2 (X << 1).

## Jump Operations
- **`JMP (0xB)`**: Jump to the specified address.
- **`JMPCF (0xB1)`**: Jump to the address if the carry flag is set (CF).
- **`JMPZF (0xB2)`**: Jump to the address if the zero flag is set (ZF).
- **`JMPNF (0xB3)`**: Jump to the address if the negative flag is set (NF).
- **`JMPNCF (0xB5)`**: Jump to the address if the carry flag is not set (!CF).
- **`JMPNZF (0xB6)`**: Jump to the address if the zero flag is not set (!ZF).
- **`JMPNNF (0xB7)`**: Jump to the address if the negative flag is not set (!NF).
- **`JMPAC (0xB8)`**: Jump to the address if the accumulator equals the operand.
- **`JMPZ (0xB9)`**: Jump to the address if the Z register equals the operand.
- **`JMPCH (0xBA)`**: Jump to the address if the temporary character equals the operand.

## Terminal Operations
- **`BRK_PUT (0xE)`**: Break execution and print the value from the keyboard.
- **`BRK_PUT_Z (0xE1)`**: Break execution and print the character value from the Z register.
- **`BRK_PRINT_A (0xC1)`**: Break execution and print the accumulator value (not character).
- **`STVC (0xF1)`**: Set the VC value.
- **`STVR (0xF2)`**: Set the VR value.
- **`IVC (0xF3)`**: Increment VC (VC += 1).
- **`IVR (0xF4)`**: Increment VR (VR += 1).
