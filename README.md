/////////////////////////////////// 
//CPU OPCODES

1) LDA = 0x01; // Load value in accum
2) STZ = 0x02; // Load value in Z
3) STX = 0x03; // Load value in X
4) ADD_Z = 0x04; // A += Z
5) ADD_X = 0x05; // A += X
6) SUB_Z = 0x06; // A -= Z
7) SUB_X = 0x07; // A -= X
8) SCF = 0x08; // CF = 1
9) SZF = 0x09; // ZF = 1
10) SNF = 0xA; // NF = 1
11) JMS = 0xC; // Call subroutine
12) END = 0x10; // END program
13) IAC = 0xE2; // A += 1
14) IZC = 0xE3; // Z += 1
15) IXC = 0xE4; // X += 1
16) DAC = 0xE5; // A -= 1
17) DZC = 0xE6; // Z -= 1
18) DXC = 0xE7; // X -= 1
19) RAC = 0xE8; // A << 1 (A * 2) 
20) RAZ = 0xE9; // Z << 1 (Z * 2) 
21) RAX = 0xEA; // X << 1 (X * 2)

22) JMP = 0xB; // JMP to address
23) MPCF = 0xB1; // JMP to address if CF
24) JMPZF = 0xB2; // JMP to address if ZF
25) JMPNF = 0xB3; // JMP to address if NF
26) JMPNCF = 0xB5; // JMP to address if !CF
27) JMPNZF = 0xB6; // JMP to address if !ZF
28) JMPNNF = 0xB7; // JMP to address if !CF
29) JMPAC = 0xB8; // JMP to address if A == op
30) JMPZ = 0xB9; // JMP to address if Z == op
31) JMPCH = 0xBA; // JMP to address if TEMP CHAR == op

//////////////////////////////////////
//TERMINAL OPCODES

32) BRK_PUT = 0xE; // Break and PRINT value from keyboard
33) BRK_PUT_Z = 0xE1; // Break and PRINT Z char value
34) BRK_PRINT_A = 0xC1; // Break and PRINT A value (not char)

35) STVC = 0xF1; // Set VC value
36) STVR = 0xF2; // Set VR value

37) IVC = 0xF3; // VC += 1
38) IVR = 0xF4; // VR += 1
