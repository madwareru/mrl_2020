#pragma once

#include <core/types.h>
#include <core/render/soa_sprite_rgb.h>

namespace core::render {
    struct StandartBlit;
    struct AlphaBlendPolicy;

    struct SOASpriteRGB;

    struct SOASpriteRGBA {
        SOASpriteRGBA(core::types::u16 w, core::types::u16 h);
        SOASpriteRGBA(const SOASpriteRGBA& other) = delete;
        SOASpriteRGBA& operator=(const SOASpriteRGBA&) = delete;
        SOASpriteRGBA(SOASpriteRGBA&& other) = delete;
        SOASpriteRGBA& operator=(SOASpriteRGBA&&) = delete;
        ~SOASpriteRGBA();
        
        template<typename FF>
        void lock(FF&& predicate) {
            predicate(width_, height_, r_buffer_, g_buffer_, b_buffer_, a_buffer_);
        }

        core::types::u16 width() const;
        core::types::u16 height() const;
    private:
        core::types::u16 width_;
        core::types::u16 height_;

        core::types::u8* r_buffer_raw_;
        core::types::u8* g_buffer_raw_;
        core::types::u8* b_buffer_raw_;
        core::types::u8* a_buffer_raw_;

        core::types::u8* r_buffer_;
        core::types::u8* g_buffer_;
        core::types::u8* b_buffer_;
        core::types::u8* a_buffer_;
    };

    template<typename BlitPolicy = AlphaBlendPolicy>
    void blit_sprite(
        SOASpriteRGBA& src,
        SOASpriteRGB& dest, 
        std::int16_t dx, std::int16_t dy, 
        core::types::u16 sx, core::types::u16 sy, 
        core::types::u16 w, core::types::u16 h
    ) {
        if(dx < 0) {
            if(static_cast<core::types::u16>(-dx) >= w) return;
            sx -= dx;
            w += dx;
            dx = 0;
        }
        if(dy < 0) {
            if(static_cast<core::types::u16>(-dy) >= h) return;
            sy -= dy;
            h += dy;
            dy = 0;
        }
        if(static_cast<core::types::u16>(dx) >= dest.width() || static_cast<core::types::u16>(dy) >= dest.height()) {
            return;
        }
        BlitPolicy::blit(src, dest, static_cast<core::types::u16>(dx), static_cast<core::types::u16>(dy), sx, sy, w, h);
    }

    template<typename BlitPolicy = AlphaBlendPolicy>
    inline void blit_sprite(SOASpriteRGBA& src,SOASpriteRGB& dest, std::int16_t x, std::int16_t y) {
        blit_sprite<BlitPolicy>(src, dest, x, y, 0, 0, src.width(), src.height());
    }
}