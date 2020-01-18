#pragma once

#include <cinttypes>
#include <cstddef>

namespace core::render {

struct StandartBlit;

struct SOASpriteRGB {
    SOASpriteRGB(std::uint16_t w, std::uint16_t h);
    SOASpriteRGB(const SOASpriteRGB& other) = delete;
    SOASpriteRGB& operator=(const SOASpriteRGB&) = delete;
    SOASpriteRGB(SOASpriteRGB&& other) = delete;
    SOASpriteRGB& operator=(SOASpriteRGB&&) = delete;
    ~SOASpriteRGB();

    template<typename BlitPolicy = StandartBlit>
    void blit_on_sprite(
        SOASpriteRGB& other, 
        std::int16_t dx, std::int16_t dy, 
        std::uint16_t sx, std::uint16_t sy, 
        std::uint16_t w, std::uint16_t h
    ) {
        lock([&other, dx, dy, sx, sy, w, h](auto sw, auto sh, auto sr, auto sg, auto sb) {
            other.lock([sw, sh, sr, sg, sb, dx, dy, sx, sy, w, h](auto dw, auto dh, auto dr, auto dg, auto db) {
                BlitPolicy policy;
                policy.blit(
                    sw, sh, dw, dh,
                    sr, sg, sb, dr, dg, db,
                    dx, dy, 
                    sx, sy, 
                    w, h
                );
            });
        });
    }

    template<typename BlitPolicy = StandartBlit>
    void blit_on_sprite(SOASpriteRGB& other, std::int16_t x, std::int16_t y) {
        blit_on_sprite<BlitPolicy>(other, x, y, 0, 0, width_, height_);
    }

    //void blit_on_sprite_colorkeyed(SOASpriteRGB& other, std::int16_t x, std::int16_t y, std::uint8_t key_red, std::uint8_t key_green, std::uint8_t key_blue);
    //void blit_on_sprite_semitransparent(SOASpriteRGB& other, std::int16_t x, std::int16_t y);
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

}