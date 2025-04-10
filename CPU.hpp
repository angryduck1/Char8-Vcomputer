#include <iostream>
#include <fstream>
#include <cstdint>
#include <conio.h>
#include <raylib.h>
#include <chrono>
#include <thread>
#include <string>

#include "Opcodes.hpp"

using namespace std;

static constexpr int MAX_ROM_MEM = 4096;
static constexpr int MAX_RAM_MEM = 256;

using Word = uint16_t;
using Byte = uint8_t;

struct Memory {
	Word memory[MAX_ROM_MEM]; // ROM
	Word memory_ram[MAX_RAM_MEM]; // RAM
};

class CPU {
public:
	Word A; // A accumulator
	Word Z; // Z register
	Word X; // X register

	Word CF : 1; // Carry flag
	Word ZF : 1; // Zero flag
	Word NF : 1; // Negative flag

	Word PC : 12; // Pointer Counter

	Word SP; // Stack Pointer

	void Reset(Memory& mem) {
		A = Z = X = 0;
		CF = ZF = NF = 0;

		PC = 0xFFF;

		SP = 0xFF1;

		memset(mem.memory, 0, sizeof(mem.memory));
		memset(mem.memory_ram, 0, sizeof(mem.memory_ram));
	}

	void Load_ROM(string name, Memory& mem, Word StAddress) {
		ifstream bin(name, ios::binary);

		char byte;

		if (!bin.is_open()) {
			cout << "Failed to open " << name << endl;
			return;
		}

		while (bin.get(byte)) {
			mem.memory[StAddress++ & 0xFFF] = static_cast<Byte>(byte);
		}
	}

	void SET_ZF_NF_A() {
		ZF = (A == 0);
		NF = (A & 0x8000) != 0;
	}

	void SET_ZF_NF_CF_A(Word& LA, Word& R, bool f) {
		ZF = (A == 0);
		NF = (A & 0x8000) != 0;
		switch (f) {
		case 0: { CF = (LA + R) > 0xFFFF; } break;
		case 1: { CF = R > LA; } break;
		}
	}

	void SET_INC_ST(Word& R) {
		++R;

		ZF = (R == 0);
		NF = (R & 0x8000) != 0;

		CF = ((R - 1) & 0xFFFF) == 0xFFFF;
	}

	void SET_DEC_ST(Word& R) {
		--R;

		ZF = (R == 0);
		NF = (R & 0x8000) != 0;

		CF = ((R + 1) & 0xFFFF) == 0;
	}

	void SET_ZF_NF(Word& R) {
		ZF = (R == 0);
		NF = (R & 0x8000) != 0;
	}

	void WriteToStack(Memory& mem) {
		mem.memory[SP] = (PC + 2) & 0xFFFF;
		++SP;
	}

	void RetFromStack(Memory& mem) {
		PC = mem.memory[--SP];
	}

	void PRINT(Terminal& t) {
		ClearBackground(DARKBLUE);

		BeginDrawing();

		int raws = 0;
		int colls = 0;

		for (int y = 45; y < 750 && colls < 18; y += 40) {
			for (int x = 50; x < 750 && raws < 34; x += 21) {
				DrawText(TextFormat("%c", t.coll[colls][raws]), x, y, 30, GREEN);
				++raws;
			}

			raws = 0;
			++colls;
		}

		DrawText(TextFormat("%d", PC), 720, 10, 30, GREEN);
		DrawText(TextFormat("%d", A), 720, 30, 30, GREEN);
		DrawText(TextFormat("%d", Z), 720, 60, 30, GREEN);
		EndDrawing();
	}

	void PRINT_A(Memory& mem, Terminal &t) {
		string c = to_string(A);
		for (size_t i = 0; i < c.size(); ++i) {
			t.coll[t.MASK_VC][t.MASK_VR + i] = c[i];
			PRINT(t);
		}
	}

	Word Fetch_Byte(Memory& mem) {
		Word Data = mem.memory[PC];
		++PC;
		return Data;
	}

	Word Fetch_Word(Memory& mem) {
		Word Data = mem.memory[PC];
		++PC;

		Data = Data | (mem.memory[PC] << 8);
		++PC;

		return Data;
	}

	Word Read_RAM(Memory& mem, Byte& ByteAddress) {
		Word Data = mem.memory_ram[ByteAddress];
		return Data;
	}
	void Execute(Memory& mem, Terminal& t) {
		Byte Instr;
		char a;
		bool run = true;
		bool is_jmpch = 0;
		bool wait_click = 0;

		InitWindow(800, 800, "Char8");
		SetTargetFPS(90);

		while (!WindowShouldClose() && run == 1) {
			PRINT(t);
			a = '\0';
			a = GetCharPressed();

			if (wait_click && run) {
				if (is_jmpch == 1) {
					if (a == 0) {
						wait_click = 1;
						is_jmpch = 1;
						continue;
					}
					else {
						wait_click = 0;
						is_jmpch = 0;
						Byte ch = Fetch_Byte(mem);
						Byte Address = Fetch_Word(mem);
						if (a == ch) { PC = Address; }
					}
				}
				else {
					if (a == 0) {
						wait_click = 1;
						continue;
					}
					else {
						wait_click = 0;
						t.coll[t.MASK_VC][t.MASK_VR] = a;
					}
				}
			}

			Instr = Fetch_Byte(mem);

			if (run && !wait_click) {
				switch (Instr) {
				case END: {
					run = false;
				} break;

				case LDA: {
					A = Fetch_Word(mem);
					SET_ZF_NF_A();
				} break;

				case STZ: {
					Z = Fetch_Word(mem);
					SET_ZF_NF(Z);
				} break;

				case STX: {
					X = Fetch_Word(mem);
					SET_ZF_NF(X);
				} break;

				case ADD_Z: {
					Word LA = A;
					A += Z;
					SET_ZF_NF_CF_A(A, Z, 0);
				} break;

				case ADD_X: {
					Word LA = A;
					A += X;
					SET_ZF_NF_CF_A(LA, X, 0);
				} break;

				case SUB_Z: {
					Word LA = A;
					A -= X;
					SET_ZF_NF_CF_A(LA, X, 1);
				} break;

				case SUB_X: {
					Word LA = A;
					A -= X;
					SET_ZF_NF_CF_A(LA, X, 1);
				} break;

				case SCF: {
					CF = 1;
				} break;

				case SZF: {
					ZF = 1;
				} break;

				case SNF: {
					NF = 1;
				} break;

				case IAC: {
					SET_INC_ST(A);
				} break;

				case IZC: {
					SET_INC_ST(Z);
				} break;

				case IXC: {
					SET_INC_ST(X);
				} break;

				case DAC: {
					SET_DEC_ST(A);
				} break;

				case DZC: {
					SET_DEC_ST(Z);
				} break;

				case DXC: {
					SET_DEC_ST(X);
				} break;

				case JMP: {
					PC = (Fetch_Word(mem)) & 0xFFF;
				} break;

				case JMS: {
					WriteToStack(mem);
					Word Address = Fetch_Word(mem);
					PC = Address;
				} break;

				case RET: {
					RetFromStack(mem);
				} break;

				case STVC: {
					t.MASK_VC = Fetch_Byte(mem);
				} break;

				case STVR: {
					t.MASK_VR = Fetch_Byte(mem);
				} break;

				case IVC: {
					++t.MASK_VC;
				} break;

				case IVR: {
					++t.MASK_VR;
				} break;

				case RAC: {
					Word LA = A;
					A <<= 1;
					SET_ZF_NF_CF_A(LA, A, 0);
				} break;

				case RAZ: {
					Word LZ = Z;
					Z <<= 1;
					SET_ZF_NF_CF_A(LZ, Z, 0);
				} break;

				case RAX: {
					Word LX = X;
					X <<= 1;
					SET_ZF_NF_CF_A(LX, X, 0);
				} break;

				case JMPAC: {
					Word operand = Fetch_Word(mem);
					Word Address = Fetch_Word(mem);
					if (A == operand) { PC = Address & 0xFFF; }
				} break;

				case JMPZ: {
					Word operand = Fetch_Word(mem);
					Word Address = Fetch_Word(mem);
					if (Z == operand) { PC = Address & 0xFFF; }
				} break;

				case JMPCF: {
					Word Address = Fetch_Word(mem);
					if (CF) { PC = Address & 0xFFF; }
				} break;

				case JMPZF: {
					Word Address = Fetch_Word(mem);
					if (ZF) { PC = Address & 0xFFF; }
				} break;

				case JMPNF: {
					Word Address = Fetch_Word(mem);
					if (NF) { PC = Address; }
				} break;

				case JMPNCF: { 
					Word Address = Fetch_Word(mem);
					if (!CF) { PC = Address; }
				} break;

				case JMPNZF: {
					Word Address = Fetch_Word(mem);
					if (!ZF) { PC = Address; }
				} break;

				case JMPNNF: {
					Word Address = Fetch_Word(mem);
					if (!NF) { PC = Address; }
				} break;

				case JMPCH: {
					if (a == 0) {
						wait_click = 1;
						is_jmpch = 1;
						continue;
					}
					else {
						Byte ch = Fetch_Byte(mem);
						Byte Address = Fetch_Word(mem);
						if (a == ch) { PC = Address; }
					}
				} break;

				case BRK_PUT: {
					if (a == 0) {
						wait_click = 1;
						continue;
					}
					else {
						wait_click = 0;
						t.coll[t.MASK_VC][t.MASK_VR] = a;
					}
				} break;

				case BRK_PRINT_A: {
					PRINT_A(mem, t);
				} break;

				case BRK_PUT_Z: {
					t.coll[t.MASK_VC][t.MASK_VR] = Z & 0xFF;
				} break;

				}

				PRINT(t);
			}
		}

		CloseWindow();
	}
};