#include <core/render/soa_sprite_rgb.h>
#include <core/render/standart_blit_policy.h>
#include <emmintrin.h>
#include <iostream>

namespace core::render {
    SOASpriteRGB::SOASpriteRGB(std::uint16_t w, std::uint16_t h) {
        r_buffer_raw_ = new std::uint8_t[w * h + 8];
        g_buffer_raw_ = new std::uint8_t[w * h + 8];
        b_buffer_raw_ = new std::uint8_t[w * h + 8];
        for(std::size_t i = 0; i < w * h + 8; ++i)
         {
             r_buffer_raw_[i] = 0;
             g_buffer_raw_[i] = 0;
             b_buffer_raw_[i] = 0;
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
    }

    SOASpriteRGB::~SOASpriteRGB() {
        delete [] b_buffer_raw_;
        delete [] g_buffer_raw_;
        delete [] r_buffer_raw_;
    }

    void SOASpriteRGB::blit_on_opengl_buffer(std::uint8_t* dest_cbuf, std::uint16_t dw, std::uint16_t dh){
        std::uint8_t* b_data = &b_buffer_[0];
        std::uint8_t* g_data = &g_buffer_[0];
        std::uint8_t* r_data = &r_buffer_[0];
        std::uint8_t* d_data = &dest_cbuf[0];

        __m128i zero_batch = _mm_set1_epi8(0);

        for(std::size_t i = dw * dh; i; i -= 16) {
            auto bd = _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data));
            auto gd = _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data));
            auto rd = _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data));

            auto m_r_b = _mm_unpacklo_epi8(rd, bd);
            auto m_g_a = _mm_unpacklo_epi8(gd, zero_batch);
            auto m_r_b_hi = _mm_unpackhi_epi8(rd, bd);
            auto m_g_a_hi = _mm_unpackhi_epi8(gd, zero_batch);

            _mm_storeu_si128(reinterpret_cast<__m128i*>(d_data), _mm_unpacklo_epi8(m_r_b, m_g_a));
            d_data += 16;
            _mm_storeu_si128(reinterpret_cast<__m128i*>(d_data), _mm_unpackhi_epi8(m_r_b, m_g_a));
            d_data += 16;
            _mm_storeu_si128(reinterpret_cast<__m128i*>(d_data), _mm_unpacklo_epi8(m_r_b_hi, m_g_a_hi));
            d_data += 16;
            _mm_storeu_si128(reinterpret_cast<__m128i*>(d_data), _mm_unpackhi_epi8(m_r_b_hi, m_g_a_hi));
            d_data += 16;

            b_data += 16;
            g_data += 16;
            r_data += 16;
        }
    }

    std::uint16_t SOASpriteRGB::width() const {
        return width_;
    }

    std::uint16_t SOASpriteRGB::height() const {
        return height_;
    }
}