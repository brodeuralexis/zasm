#pragma once

#ifndef __ZASM__MACHINE__DECODE__
#define __ZASM__MACHINE__DECODE__

#include <cstddef>
#include <functional>

#include "zasm/registers.hh"
#include "zasm/machine/cpu.hh"
#include "zasm/machine/bus.hh"

#include "meta.hh"

namespace zasm
{
    using Instruction = std::function<size_t(CPU& cpu, Bus& bus)>;

    template<ByteRegister r, ByteRegister r_, size_t cycles = 1>
    size_t ld_R_R(CPU& cpu, Bus& bus) noexcept
    {
        UNUSED(bus);
        cpu.step(1);

        cpu.write(r, cpu.read(r_));

        return cycles;
    }

    template<ByteRegister r, size_t cycles = 2>
    size_t ld_R_N(CPU& cpu, Bus& bus) noexcept
    {
        auto pc = cpu.step(2);

        auto n = bus.read<byte_t>(pc + 1);
        cpu.write(r, n);

        return cycles;
    }

    template<ByteRegister r, WordRegister rr, size_t cycles = 2>
    size_t ld_R_atRR(CPU& cpu, Bus& bus) noexcept
    {
        cpu.step();

        auto n = bus.read<byte_t>(cpu.read(rr));
        cpu.write(r, n);

        return cycles;
    }

    template<ByteRegister r, WordRegister ii, size_t cycles = 5>
    size_t ld_R_atII_plusD(CPU& cpu, Bus& bus) noexcept
    {
        auto pc = cpu.step(3);

        auto address = cpu.read(ii);
        auto offset = bus.read<byte_t>(pc + 2);

        auto byte = bus.read<byte_t>(address + offset);
        cpu.write(r, byte);

        return cycles;
    }

    template<WordRegister rr, ByteRegister r, size_t cycles = 2>
    size_t ld_atRR_R(CPU& cpu, Bus& bus) noexcept
    {
        cpu.step();

        auto n = cpu.read(r);
        bus.write(cpu.read(rr), n);

        return cycles;
    }

    template<WordRegister rr, size_t cycles = 3>
    size_t ld_atRR_N(CPU& cpu, Bus& bus) noexcept
    {
        auto pc = cpu.step(2);

        auto n = bus.read<byte_t>(pc + 1);
        bus.write(cpu.read(rr), n);

        return cycles;
    }

    template<WordRegister rr, size_t cycles = 5>
    size_t ld_atRR_plus_D_N(CPU& cpu, Bus& bus) noexcept
    {
        auto pc = cpu.step(3);

        auto n = bus.read<byte_t>(pc + 3);

        auto address = cpu.read(rr);
        auto offset = bus.read<byte_t>(pc + 2);

        bus.write(address + offset, n);

        return cycles;
    }

    template<ByteRegister r, size_t cycles = 4>
    size_t ld_R_atNN(CPU& cpu, Bus& bus) noexcept
    {
        auto pc = cpu.step(3);

        auto nn = bus.read<word_t>(pc + 1);
        cpu.write(r, bus.read<byte_t>(nn));

        return cycles;
    }

    template<ByteRegister r, size_t cycles = 4>
    size_t ld_atNN_R(CPU& cpu, Bus& bus) noexcept
    {
        auto pc = cpu.step(3);

        auto nn = bus.read<word_t>(pc + 1);
        bus.write(nn, cpu.read(r));

        return cycles;
    }

    template<ByteRegister r, ByteRegister ir, size_t cycles = 2>
    size_t ld_R_IR(CPU& cpu, Bus& bus) noexcept
    {
        UNUSED(bus);

        cpu.step(2);

        auto n = cpu.read(ir);
        cpu.write(r, n);

        if ((n & 0b10000000) != 0)
        {
            cpu.enable(Flag::S);
        }

        if (n == 0)
        {
            cpu.enable(Flag::Z);
        }

        cpu.disable(Flag::H);

        cpu.set(Flag::PV, cpu.iff2());

        cpu.disable(Flag::N);

        return cycles;
    }
}

#endif
