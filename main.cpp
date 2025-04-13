#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"

#include <iostream>
#include "Terminal.hpp"
#include "CPU.hpp"

using namespace std;

int main() {
    CPU cpu;
    Memory mem;
    Terminal t;

    cpu.Reset(mem);
    cpu.Load_ROM("gametest.bin", mem, 0xFFF);
    cpu.Execute(mem, t);
}
