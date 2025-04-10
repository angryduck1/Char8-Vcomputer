/////////////////////////////////// 
//CPU OPCODES

LDA = 0x01; // Load value in accum
STZ = 0x02; // Load value in Z
STX = 0x03; // Load value in X
ADD_Z = 0x04; // A += Z
ADD_X = 0x05; // A += X
SUB_Z = 0x06; // A -= Z
SUB_X = 0x07; // A -= X
SCF = 0x08; // CF = 1
SZF = 0x09; // ZF = 1
SNF = 0xA; // NF = 1
JMS = 0xC; // Call subroutine
END = 0x10; // END program
IAC = 0xE2; // A += 1
IZC = 0xE3; // Z += 1
IXC = 0xE4; // X += 1
DAC = 0xE5; // A -= 1
DZC = 0xE6; // Z -= 1
DXC = 0xE7; // X -= 1
RAC = 0xE8; // A << 1 (A * 2) 
RAZ = 0xE9; // Z << 1 (Z * 2) 
RAX = 0xEA; // X << 1 (X * 2)

JMP = 0xB; // JMP to address
JMPCF = 0xB1; // JMP to address if CF
JMPZF = 0xB2; // JMP to address if ZF
JMPNF = 0xB3; // JMP to address if NF
JMPNCF = 0xB5; // JMP to address if !CF
JMPNZF = 0xB6; // JMP to address if !ZF
JMPNNF = 0xB7; // JMP to address if !CF
JMPAC = 0xB8; // JMP to address if A == op
JMPZ = 0xB9; // JMP to address if Z == op
JMPCH = 0xBA; // JMP to address if TEMP CHAR == op

//////////////////////////////////////
//TERMINAL OPCODES

BRK_PUT = 0xE; // Break and PRINT value from keyboard
BRK_PUT_Z = 0xE1; // Break and PRINT Z char value
BRK_PRINT_A = 0xC1; // Break and PRINT A value (not char)

STVC = 0xF1; // Set VC value
STVR = 0xF2; // Set VR value

IVC = 0xF3; // VC += 1
IVR = 0xF4; // VR += 1
