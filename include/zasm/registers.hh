#pragma once

#ifndef __ZASM__REGISTERS__
#define __ZASM__REGISTERS__

#include "zasm/types.hh"

namespace zasm
{
    enum ByteRegister
    {
        A, F,
        B, C,
        D, E,
        H, L,
        I, R,
    };

    enum WordRegister
    {
        AF, BC, DE, HL,
        AF_, BC_, DE_, HL_,
        IR,
        IX, IY,
        SP, PC,
    };

    struct Register
    {
        word_t word;
        union
        {
            byte_t lowByte;
            byte_t highByte;
        };

        /**
         * Creates a new zero initialized register.
         */
        Register();
    };
}

#endif
