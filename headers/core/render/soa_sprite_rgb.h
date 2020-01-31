#pragma once

#include <core/types.h>

namespace core::render {
    struct StandartBlit;

    struct SOASpriteRGB {
        SOASpriteRGB(core::types::u16 w, core::types::u16 h);
        SOASpriteRGB(const SOASpriteRGB& other) = delete;
        SOASpriteRGB& operator=(const SOASpriteRGB&) = delete;
        SOASpriteRGB(SOASpriteRGB&& other) = delete;
        SOASpriteRGB& operator=(SOASpriteRGB&&) = delete;
        ~SOASpriteRGB();
        
        void blit_on_opengl_buffer(core::types::u8* buf, core::types::u16 buf_width, core::types::u16 buf_height);

        template<typename FF>
        void lock(FF&& predicate) {
            predicate(width_, height_, r_buffer_, g_buffer_, b_buffer_);
        }

        core::types::u16 width() const;
        core::types::u16 height() const;
    private:
        core::types::u16 width_;
        core::types::u16 height_;

        core::types::u8* r_buffer_raw_;
        core::types::u8* g_buffer_raw_;
        core::types::u8* b_buffer_raw_;

        core::types::u8* r_buffer_;
        core::types::u8* g_buffer_;
        core::types::u8* b_buffer_;
    };

    template<typename BlitPolicy = StandartBlit>
    void blit_sprite(
        SOASpriteRGB& src,
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

    template<typename BlitPolicy = StandartBlit>
    inline void blit_sprite(SOASpriteRGB& src,SOASpriteRGB& dest, std::int16_t x, std::int16_t y) {
        blit_sprite<BlitPolicy>(src, dest, x, y, 0, 0, src.width(), src.height());
    }
}