#pragma once

#include <core/types.h>

namespace core::render {

struct SOASpriteRGB;
struct SOASpriteRGBA;

struct AlphaBlendPolicy {
    static void blit(
        SOASpriteRGB& src, 
        SOASpriteRGB& dest,
        core::types::u16 dx, core::types::u16 dy, 
        core::types::u16 sx, core::types::u16 sy, 
        core::types::u16 w, core::types::u16 h);

    static void blit(
        SOASpriteRGBA& src, 
        SOASpriteRGB& dest,
        core::types::u16 dx, core::types::u16 dy, 
        core::types::u16 sx, core::types::u16 sy, 
        core::types::u16 w, core::types::u16 h
    );
};

}