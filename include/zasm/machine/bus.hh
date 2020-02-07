#pragma once

#ifndef __ZASM__MACHINE__BUS__
#define __ZASM__MACHINE__BUS__

#include "zasm/types.hh"

#include <vector>
#include <memory>

namespace zasm
{
    /**
     * A component of the CPU's bus.
     *
     * By default, bus components do not accept any read or write request unless their `accept_read` and `accept_write`
     * methods are overridden.
     */
    class BusComponent
    {
    public:
        // abstract class
        virtual ~BusComponent();

        /**
         * Reads a single byte from this bus component.
         * @param address The address at which to read the byte
         * @return The read byte
         */
        [[nodiscard]] virtual byte_t read(address_t address) const noexcept = 0;

        /**
         * Writes a single byte to this bus component.
         * @param address The address at which to write the byte
         * @param byte The byte to write
         */
        virtual void write(address_t address, byte_t byte) noexcept = 0;

        /**
         * Indicates if this bus component can accept a read at the given address.
         * @param address An address
         * @return If the address is readable
         */
        [[nodiscard]] virtual bool accept_read(address_t address) const noexcept;

        /**
         * Indicates if this bus component can accept a write at the given address.
         * @param address An address
         * @return If the address is writable
         */
        [[nodiscard]] virtual bool accept_write(address_t address) const noexcept;
    };

    /**
     * A bus of components that is linked to a CPU for processing instructions.
     */
    class Bus final
    {
    private:
        std::vector<std::unique_ptr<BusComponent>> _components;

    public:
        /**
         * Creates a new bus without any attached components.
         */
        Bus();

        /**
         * Destroys this bus, freeing any associated memory.
         */
        ~Bus() = default;

        Bus(const Bus&) = delete;
        Bus& operator=(const Bus&) = delete;

        Bus(Bus&&) = default;
        Bus& operator=(Bus&&) = default;

        /**
         * Reads a single value of the given type from the bus.
         * @tparam T The type to read
         * @param address The address at which to read the value
         * @return The value that was read
         */
        template<typename T>
        [[nodiscard]] T read(address_t address) const noexcept = delete;

        template<>
        [[nodiscard]] inline byte_t read<byte_t>(address_t address) const noexcept
        {
            return read_byte(address);
        }

        template<>
        [[nodiscard]] inline word_t read<word_t>(address_t address) const noexcept
        {
            return read_word(address);
        }

        /**
         * Writes a single byte to the bus.
         * @param address The address at which to write the byte
         * @param byte The byte to write
         */
        void write(address_t address, byte_t byte) noexcept;

        /**
         * Writes a single word to the bus.
         * @param address The address at which to write the word
         * @param word The word to write
         */
        void write(address_t address, word_t word) noexcept;

    private:
        [[nodiscard]] byte_t read_byte(address_t address) const noexcept;
        [[nodiscard]] word_t read_word(address_t address) const noexcept;
    };

    /**
     * A bus component holding memory that can be read and written to.
     */
    class RAM : public BusComponent
    {
    private:
        address_t _inclusiveStart;
        address_t _exclusiveEnd;
        std::vector<byte_t> _memory;

    public:
        /**
         * Creates a new RAM component for the given address ranges.
         * @param inclusiveStart The inclusive starting address
         * @param exclusiveEnd The exclusive ending address
         */
        RAM(address_t inclusiveStart, address_t exclusiveEnd);

        [[nodiscard]] byte_t read(address_t address) const noexcept override;

        void write(address_t address, byte_t byte) noexcept override;

        [[nodiscard]] bool accept_read(address_t address) const noexcept override;

        [[nodiscard]] bool accept_write(address_t address) const noexcept override;
    };

    /**
     * A bus component holding memory that can only be read.
     */
    class ROM : public RAM
    {
    public:
        /**
         * Creates a new ROM component for the given address range.
         * @param inclusiveStart The inclusive starting address
         * @param exclusiveEnd The exclusive ending address
         */
        ROM(address_t inclusiveStart, address_t exclusiveEnd);

        [[nodiscard]] bool accept_write(address_t address) const noexcept override;
    };
}

#endif
