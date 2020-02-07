#pragma once

#ifndef __ZASM__TYPES__
#define __ZASM__TYPES__

#include <cstdint>

namespace zasm
{
    /**
     * The type of a byte handled by our emulated CPU.
     */
    using byte_t = uint8_t;

    /**
     * The type of a word handled by our emulated CPU.
     */
    using word_t = uint16_t;

    /**
     * The type of an address handled by our emulated CPU.
     */
    using address_t = word_t;
}

#endif
