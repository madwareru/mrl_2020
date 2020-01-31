#include <core/render/soa_sprite_rgba.h>

namespace core::render {
    SOASpriteRGBA::SOASpriteRGBA(core::types::u16 w, core::types::u16 h) : width_{w}, height_{h} {
        r_buffer_raw_ = new core::types::u8[w * h + 8];
        g_buffer_raw_ = new core::types::u8[w * h + 8];
        b_buffer_raw_ = new core::types::u8[w * h + 8];
        a_buffer_raw_ = new core::types::u8[w * h + 8];
        for(core::types::ptr_size i = 0; i < w * h + 8; ++i)
         {
             r_buffer_raw_[i] = 0;
             g_buffer_raw_[i] = 0;
             b_buffer_raw_[i] = 0;
             a_buffer_raw_[i] = 0;
         }

        r_buffer_ = (reinterpret_cast<core::types::ptr_size>(&r_buffer_raw_[0]) % 16 == 0)
            ? &r_buffer_raw_[0]
            : &r_buffer_raw_[8];

        g_buffer_ = (reinterpret_cast<core::types::ptr_size>(&g_buffer_raw_[0]) % 16 == 0)
            ? &g_buffer_raw_[0]
            : &g_buffer_raw_[8];

        b_buffer_ = (reinterpret_cast<core::types::ptr_size>(&b_buffer_raw_[0]) % 16 == 0)
            ? &b_buffer_raw_[0]
            : &b_buffer_raw_[8];

        a_buffer_ = (reinterpret_cast<core::types::ptr_size>(&a_buffer_raw_[0]) % 16 == 0)
            ? &a_buffer_raw_[0]
            : &a_buffer_raw_[8];
    }

    SOASpriteRGBA::~SOASpriteRGBA() {
        delete [] a_buffer_raw_;
        delete [] b_buffer_raw_;
        delete [] g_buffer_raw_;
        delete [] r_buffer_raw_;
    }

    core::types::u16 SOASpriteRGBA::width() const {
        return width_;
    }

    core::types::u16 SOASpriteRGBA::height() const {
        return height_;
    }
}