#include <core/render/soa_sprite_rgba.h>

namespace core::render {
    SOASpriteRGBA::SOASpriteRGBA(std::uint16_t w, std::uint16_t h) : width_{w}, height_{h} {
        r_buffer_raw_ = new std::uint8_t[w * h + 8];
        g_buffer_raw_ = new std::uint8_t[w * h + 8];
        b_buffer_raw_ = new std::uint8_t[w * h + 8];
        a_buffer_raw_ = new std::uint8_t[w * h + 8];
        for(std::size_t i = 0; i < w * h + 8; ++i)
         {
             r_buffer_raw_[i] = 0;
             g_buffer_raw_[i] = 0;
             b_buffer_raw_[i] = 0;
             a_buffer_raw_[i] = 0;
         }

        r_buffer_ = (reinterpret_cast<std::size_t>(&r_buffer_raw_[0]) % 16 == 0)
            ? &r_buffer_raw_[0]
            : &r_buffer_raw_[8];

        g_buffer_ = (reinterpret_cast<std::size_t>(&g_buffer_raw_[0]) % 16 == 0)
            ? &g_buffer_raw_[0]
            : &g_buffer_raw_[8];

        b_buffer_ = (reinterpret_cast<std::size_t>(&b_buffer_raw_[0]) % 16 == 0)
            ? &b_buffer_raw_[0]
            : &b_buffer_raw_[8];

        a_buffer_ = (reinterpret_cast<std::size_t>(&a_buffer_raw_[0]) % 16 == 0)
            ? &a_buffer_raw_[0]
            : &a_buffer_raw_[8];
    }

    SOASpriteRGBA::~SOASpriteRGBA() {
        delete [] a_buffer_raw_;
        delete [] b_buffer_raw_;
        delete [] g_buffer_raw_;
        delete [] r_buffer_raw_;
    }

    std::uint16_t SOASpriteRGBA::width() const {
        return width_;
    }

    std::uint16_t SOASpriteRGBA::height() const {
        return height_;
    }
}