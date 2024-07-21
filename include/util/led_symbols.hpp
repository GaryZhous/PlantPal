#pragma once

#include <stdint.h>

namespace led_symbols {
    const uint32_t off[3] = { 0 };

    const uint32_t heart[] = {
        0x3184a444,
        0x44042081,
        0x100a0040
    };
    const uint32_t ok[] = {
        0xf9189289,
        0x48988948,
        0x92891f91,
    };
    const uint32_t dry[] = {
        0xccaaaaaa,
		0xaacaaa4a,
		0xa4aa4ca4,
    };
    const uint32_t cold[] = {
        0xda69a59a,
		0x59a59a59,
		0xa59a5db6,
    };
    const uint32_t hot[] = {
        0xaeeaa4aa,
		0x4ea4aa4a,
		0xa4aa4ae4,
    };
    const uint32_t hi[] = {
        0x89289288,
		0x2f928928,
		0x92890892,
    };
}

