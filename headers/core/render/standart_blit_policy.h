#pragma once

#include <cstdint>
#include <cstddef>

namespace core::render {

struct StandartBlit {
    void blit(
        std::uint16_t sw, std::uint16_t sh,
        std::uint16_t dw, std::uint16_t dh,
        std::uint8_t* src_r_buffer, std::uint8_t* src_g_buffer, std::uint8_t* src_b_buffer,
        std::uint8_t* dest_r_buffer, std::uint8_t* dest_g_buffer, std::uint8_t* dest_b_buffer,
        std::int16_t dx, std::int16_t dy, 
        std::uint16_t sx, std::uint16_t sy, 
        std::uint16_t w, std::uint16_t h
    );

    void blit(
        std::uint16_t sw, std::uint16_t sh,
        std::uint16_t dw, std::uint16_t dh,
        std::uint8_t* src_r_buffer, std::uint8_t* src_g_buffer, std::uint8_t* src_b_buffer, std::uint8_t* src_a_buffer,
        std::uint8_t* dest_r_buffer, std::uint8_t* dest_g_buffer, std::uint8_t* dest_b_buffer, std::uint8_t* dest_a_buffer,
        std::int16_t dx, std::int16_t dy, 
        std::uint16_t sx, std::uint16_t sy,
        std::uint16_t w, std::uint16_t h
    );
};

}