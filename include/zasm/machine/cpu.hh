#pragma once

#ifndef __ZASM__MACHINE__CPU__
#define __ZASM__MACHINE__CPU__

#include "zasm/registers.hh"

namespace zasm
{
    enum class Flag
    {
        S = 7,
        Z = 6,
        H = 4,
        PV = 2,
        N = 1,
        C = 0,
    };

    /**
     * A class holding the state of the Z80 cpu.
     */
    class CPU final
    {
    private:
        Register _af;
        Register _bc;
        Register _de;
        Register _hl;

        Register _alternateAf;
        Register _alternateBc;
        Register _alternateDe;
        Register _alternateHl;

        Register _ir;

        Register _ix;
        Register _iy;

        Register _sp;
        Register _pc;

        bool _iff1;
        bool _iff2;

    public:
        /**
         * Reads the value of a word register passed by template argument.
         * @tparam r A word register
         * @return The value in the register
         */
        template<WordRegister r>
        [[nodiscard]] inline word_t read() const noexcept
        {
            return read(r);
        }

        /**
         * Reads The value of a word register.
         * @param r A word register
         * @return The value in the register
         */
        [[nodiscard]] word_t read(WordRegister r) const noexcept;

        /**
         * Reads the value of a byte register passed by template argument.
         * @tparam r A byte register
         * @return The value in the register
         */
        template<ByteRegister r>
        [[nodiscard]] inline byte_t read() const noexcept
        {
            return read(r);
        }

        /**
         * Reads the value of a byte register.
         * @param r A byte register
         * @return The value in the register
         */
        [[nodiscard]] byte_t read(ByteRegister r) const noexcept;

        /**
         * Writes a value to the word register passed by template argument.
         * @tparam r A word register
         * @param value The word to write
         */
        template<WordRegister r>
        inline void write(word_t value) noexcept
        {
            write(r, value);
        }

        /**
         * Writes a value to the word register.
         * @param r A word register
         * @param value The word to write
         */
        void write(WordRegister r, word_t value) noexcept;

        /**
         * Writes a value to the byte register passed by template argument.
         * @tparam r A byte register
         * @param value The byte to write
         */
        template<ByteRegister r>
        inline void write(byte_t value) noexcept
        {
            write(r, value);
        }

        /**
         * Writes a value to the byte register.
         * @param r A byte register
         * @param value The byte to write
         */
        void write(ByteRegister r, byte_t value) noexcept;

        /**
         * Represents a step of *offset* amount of bytes in PC.
         * @param offset An offset
         * @return The previous value of PC
         */
        address_t step(address_t offset = 1) noexcept;

        /**
         * Sets the given flag in the F register.
         * @param flag A flag
         */
        void enable(Flag flag) noexcept;

        /**
         * Unsets the given flag from the F register.
         * @param flag A flag
         */
        void disable(Flag flag) noexcept;

        /**
         * Changes the value of the flag in the F register.
         * @param flag A flag
         * @param value Its value
         */
        void set(Flag flag, bool value) noexcept;

        /**
         * Gets the given flag from the F register.
         * @param flag A flag
         * @return The state of the flag
         */
        [[nodiscard]] bool get(Flag flag) const noexcept;

        /**
         * Clears the flags from the F register.
         */
        void clearFlags() noexcept;

        [[nodiscard]] inline bool iff1() const noexcept
        {
            return _iff1;
        }

        [[nodiscard]] inline bool& iff1() noexcept
        {
            return _iff1;
        }

        [[nodiscard]] inline bool iff2() const noexcept
        {
            return _iff2;
        }

        [[nodiscard]] inline bool& iff2() noexcept
        {
            return _iff2;
        }
    };
}

#endif
