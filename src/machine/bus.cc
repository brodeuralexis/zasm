#include "zasm/machine/bus.hh"

#include "meta.hh"

namespace zasm
{
    Bus::Bus()
        : _components()
    {
    }

    Bus::~Bus() = default;

    BusComponent::~BusComponent() = default;

    bool BusComponent::accept_read(address_t address) const noexcept
    {
        UNUSED(address);
        return false;
    }

    bool BusComponent::accept_write(address_t address) const noexcept
    {
        UNUSED(address);
        return false;
    }

    void Bus::write(address_t address, byte_t byte) noexcept
    {
        for (auto& component : _components) {
            if (component->accept_write(address)) {
                component->write(address, byte);
            }
        }
    }

    void Bus::write(address_t address, word_t word) noexcept
    {
        for (auto& component : _components) {
            auto low_byte = (byte_t) (word | 0xFFu);
            auto high_byte = (byte_t) ((word >> 8u) | 0xFF);

            if (component->accept_write(address)) {
                component->write(address, low_byte);
            }

            if (component->accept_write(address + 1)) {
                component->write(address + 1, high_byte);
            }
        }
    }

    byte_t Bus::read_byte(address_t address) const noexcept
    {
        byte_t byte = 0;

        for (const auto& component : _components) {
            if (component->accept_read(address)) {
                byte |= component->read(address);
            }
        }

        return byte;
    }

    word_t Bus::read_word(address_t address) const noexcept
    {
        byte_t low_byte = 0;
        byte_t high_byte = 0;

        for (const auto& component : _components) {
            if (component->accept_read(address)) {
                low_byte |= component->read(address);
            }

            if (component->accept_read((address + 1))) {
                high_byte |= component->read(address + 1);
            }
        }

        return (((word_t) high_byte) << 8u) | ((word_t) low_byte);
    }

    RAM::RAM(address_t inclusiveStart, address_t exclusiveEnd)
        : _inclusiveStart(inclusiveStart)
        , _exclusiveEnd(exclusiveEnd)
        , _memory(size_t(exclusiveEnd - inclusiveStart), byte_t(0))
    {
    }

    uint8_t RAM::read(address_t address) const noexcept
    {
        return _memory[address - _inclusiveStart];
    }

    void RAM::write(address_t address, byte_t byte) noexcept
    {
        _memory[address - _inclusiveStart] = byte;
    }

    bool RAM::accept_read(address_t address) const noexcept
    {
        return address >= _inclusiveStart && address < _exclusiveEnd;
    }

    bool RAM::accept_write(address_t address) const noexcept
    {
        return address >= _inclusiveStart && address < _exclusiveEnd;
    }

    ROM::ROM(address_t inclusiveStart, address_t exclusiveEnd)
        : RAM(inclusiveStart, exclusiveEnd)
    {
    }

    bool ROM::accept_write(address_t address) const noexcept
    {
        UNUSED(address);
        return false;
    }
}
