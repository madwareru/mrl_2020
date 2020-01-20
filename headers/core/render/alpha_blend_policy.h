#pragma once

#include <cstdint>
#include <cstddef>

namespace core::render {

struct SOASpriteRGB;
struct SOASpriteRGBA;

struct AlphaBlendPolicy {
    static void blit(
        SOASpriteRGB& src, 
        SOASpriteRGB& dest,
        std::uint16_t dx, std::uint16_t dy, 
        std::uint16_t sx, std::uint16_t sy, 
        std::uint16_t w, std::uint16_t h);

    void blit(
        SOASpriteRGBA& src, 
        SOASpriteRGB& dest,
        std::uint16_t dx, std::uint16_t dy, 
        std::uint16_t sx, std::uint16_t sy, 
        std::uint16_t w, std::uint16_t h
    );
};

}