#pragma once

#include <cinttypes>
#include <cstddef>

namespace core::render {
    struct StandartBlit;
    struct SemitransparentBlit;

    struct SOASpriteRGB {
        SOASpriteRGB(std::uint16_t w, std::uint16_t h);
        SOASpriteRGB(const SOASpriteRGB& other) = delete;
        SOASpriteRGB& operator=(const SOASpriteRGB&) = delete;
        SOASpriteRGB(SOASpriteRGB&& other) = delete;
        SOASpriteRGB& operator=(SOASpriteRGB&&) = delete;
        ~SOASpriteRGB();
        
        void blit_on_opengl_buffer(std::uint8_t* buf, std::uint16_t buf_width, std::uint16_t buf_height);

        template<typename FF>
        void lock(FF&& predicate) {
            predicate(width_, height_, r_buffer_, g_buffer_, b_buffer_);
        }

        std::uint16_t width() const;
        std::uint16_t height() const;
    private:
        std::uint16_t width_;
        std::uint16_t height_;

        std::uint8_t* r_buffer_raw_;
        std::uint8_t* g_buffer_raw_;
        std::uint8_t* b_buffer_raw_;

        std::uint8_t* r_buffer_;
        std::uint8_t* g_buffer_;
        std::uint8_t* b_buffer_;
    };

    template<typename BlitPolicy = StandartBlit>
    void blit_sprite(
        SOASpriteRGB& src,
        SOASpriteRGB& dest, 
        std::int16_t dx, std::int16_t dy, 
        std::uint16_t sx, std::uint16_t sy, 
        std::uint16_t w, std::uint16_t h
    ) {
        if(dx < 0) {
            if(static_cast<std::uint16_t>(-dx) >= w) return;
            sx -= dx; w += dx; dx = 0;
        }
        if(dy < 0) {
            if(static_cast<std::uint16_t>(-dy) >= h) return;
            sy -= dy; h += dy; dy = 0;
        }
        if(static_cast<std::uint16_t>(dx) >= dest.width() || static_cast<std::uint16_t>(dy) >= dest.height()) {
            return;
        }
        BlitPolicy::blit(src, dest, static_cast<std::uint16_t>(dx), static_cast<std::uint16_t>(dy), sx, sy, w, h);
    }

    template<typename BlitPolicy = StandartBlit>
    inline void blit_sprite(SOASpriteRGB& src,SOASpriteRGB& dest, std::int16_t x, std::int16_t y) {
        blit_sprite<BlitPolicy>(src, dest, x, y, 0, 0, src.width(), src.height());
    }
}