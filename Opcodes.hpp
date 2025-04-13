#include <cstdint>

/////////////////////////////////// 
//CPU OPCODES

static constexpr uint8_t LDA = 0x01; // Load value in accum
static constexpr uint8_t STZ = 0x02; // Load value in Z
static constexpr uint8_t STX = 0x03; // Load value in X
static constexpr uint8_t ADD_Z = 0x04; // A += Z
static constexpr uint8_t ADD_X = 0x05; // A += X
static constexpr uint8_t SUB_Z = 0x06; // A -= Z
static constexpr uint8_t SUB_X = 0x07; // A -= X
static constexpr uint8_t SCF = 0x08; // CF = 1
static constexpr uint8_t SZF = 0x09; // ZF = 1
static constexpr uint8_t SNF = 0xA; // NF = 1
static constexpr uint8_t JMS = 0xC; // Call subroutine
static constexpr uint8_t RET = 0xD; // Rerturn from subroutine
static constexpr uint8_t END = 0x10; // END program
static constexpr uint8_t IAC = 0xE2; // A += 1
static constexpr uint8_t IZC = 0xE3; // Z += 1
static constexpr uint8_t IXC = 0xE4; // X += 1
static constexpr uint8_t DAC = 0xE5; // A -= 1
static constexpr uint8_t DZC = 0xE6; // Z -= 1
static constexpr uint8_t DXC = 0xE7; // X -= 1
static constexpr uint8_t RAC = 0xE8; // A << 1 (A * 2) 
static constexpr uint8_t RAZ = 0xE9; // Z << 1 (Z * 2) 
static constexpr uint8_t RAX = 0xEA; // X << 1 (X * 2)

static constexpr uint8_t JMP = 0xB; // JMP to address
static constexpr uint8_t JMPCF = 0xB1; // JMP to address if CF
static constexpr uint8_t JMPZF = 0xB2; // JMP to address if ZF
static constexpr uint8_t JMPNF = 0xB3; // JMP to address if NF
static constexpr uint8_t JMPNCF = 0xB5; // JMP to address if !CF
static constexpr uint8_t JMPNZF = 0xB6; // JMP to address if !ZF
static constexpr uint8_t JMPNNF = 0xB7; // JMP to address if !CF
static constexpr uint8_t JMPAC = 0xB8; // JMP to address if A == op
static constexpr uint8_t JMPZ = 0xB9; // JMP to address if Z == op
static constexpr uint8_t JMPCH = 0xBA; // JMP to address if TEMP CHAR == op
static constexpr uint8_t JMP_IF_A_BIG_THEN = 0xEB; // JMP to address if A > op


//////////////////////////////////////
//RAM OPCODES

static constexpr uint8_t PUT_MEM_CHAR = 0xF5; // Set char in ram

static constexpr uint8_t LRM = 0xF6; // Set ram value
static constexpr uint8_t LRM_FR_A = 0xF9; // Set ram value from A
static constexpr uint8_t LRM_FR_X = 0xFA; // Set ram value from X

static constexpr uint8_t LRM_A = 0xF7; // Transfer ram value in A
static constexpr uint8_t LRM_X = 0xF8; // Transfer ram value in X 


//////////////////////////////////////
//TERMINAL OPCODES

static constexpr uint8_t BRK_PUT_IN_Z = 0xE; // Break and PRINT value from keyboard and input in Z
static constexpr uint8_t BRK_PUT_Z = 0xE1; // Break and PRINT Z char value
static constexpr uint8_t BRK_PRINT_A = 0xC1; // Break and PRINT A value (not char)
static constexpr uint8_t BRK_PRINT_RAM = 0xC2; // Break and PRINT A ram reg info

static constexpr uint8_t STVC = 0xF1; // Set VC value
static constexpr uint8_t STVR = 0xF2; // Set VR value

static constexpr uint8_t IVC = 0xF3; // VC += 1
static constexpr uint8_t IVR = 0xF4; // VR += 1

static constexpr uint8_t DVC = 0xFB; // VC -= 1
static constexpr uint8_t DVR = 0xFC; // VR -= 1