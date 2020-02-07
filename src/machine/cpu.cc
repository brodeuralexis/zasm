#include "zasm/machine/cpu.hh"

namespace zasm
{
    word_t CPU::read(WordRegister r) const noexcept
    {
        switch (r)
        {
            case AF:
                return _af.word;
            case BC:
                return _bc.word;
            case DE:
                return _de.word;
            case HL:
                return _hl.word;

            case AF_:
                return _alternateAf.word;
            case BC_:
                return _alternateBc.word;
            case DE_:
                return _alternateDe.word;
            case HL_:
                return _alternateHl.word;

            case IR:
                return _ir.word;

            case IX:
                return _ix.word;
            case IY:
                return _iy.word;

            case SP:
                return _sp.word;
            case PC:
                return _pc.word;
        }
    }

    byte_t CPU::read(ByteRegister r) const noexcept
    {
        switch (r)
        {
            case A:
                return _af.highByte;
            case F:
                return _af.lowByte;

            case B:
                return _bc.highByte;
            case C:
                return _bc.lowByte;

            case D:
                return _de.highByte;
            case E:
                return _de.lowByte;

            case H:
                return _hl.highByte;
            case L:
                return _hl.lowByte;

            case I:
                return _ir.highByte;
            case R:
                return _ir.lowByte;
        }
    }

    void CPU::write(WordRegister r, word_t value) noexcept
    {
        switch (r)
        {
            case AF:
                _af.word = value;
                break;
            case BC:
                _bc.word = value;
                break;
            case DE:
                _de.word = value;
                break;
            case HL:
                _hl.word = value;
                break;

            case AF_:
                _alternateAf.word = value;
                break;
            case BC_:
                _alternateBc.word = value;
                break;
            case DE_:
                _alternateDe.word = value;
                break;
            case HL_:
                _alternateHl.word = value;
                break;

            case IR:
                _ir.word = value;
                break;

            case IX:
                _ix.word = value;
                break;
            case IY:
                _iy.word = value;
                break;

            case SP:
                _sp.word = value;
                break;
            case PC:
                _pc.word = value;
                break;
        }
    }

    void CPU::write(ByteRegister r, byte_t value) noexcept
    {
        switch (r)
        {
            case A:
                _af.highByte = value;
                break;
            case F:
                _af.lowByte = value;
                break;

            case B:
                _bc.highByte = value;
                break;
            case C:
                _bc.lowByte = value;
                break;

            case D:
                _de.highByte = value;
                break;
            case E:
                _de.lowByte = value;
                break;

            case H:
                _hl.highByte = value;
                break;
            case L:
                _hl.lowByte = value;
                break;

            case I:
                _ir.highByte = value;
                break;
            case R:
                _ir.lowByte = value;
                break;
        }
    }

    address_t CPU::step(address_t offset) noexcept
    {
        auto pc = read(PC);
        write(PC, pc + offset);
        return pc;
    }

    void CPU::enable(Flag flag) noexcept
    {
        auto byte = byte_t(1u) << byte_t(flag);
        write<F>(read<F>() | byte);
    }

    void CPU::disable(Flag flag) noexcept
    {
        auto byte = ~(byte_t(1u) << byte_t(flag));
        write<F>(read<F>() & byte);
    }

    bool CPU::get(Flag flag) const noexcept
    {
        auto byte = byte_t(1u) << byte_t(flag);
        return (read<F>() & byte) != 0;
    }

    void CPU::clearFlags() noexcept
    {
        write<F>(0);
    }

    void CPU::set(Flag flag, bool value) noexcept
    {
        if (value)
        {
            disable(flag);
        }
        else
        {
            enable(flag);
        }
    }
}
