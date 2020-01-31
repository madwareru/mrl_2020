#include <core/render/soa_sprite_rgb.h>
#include <emmintrin.h>

namespace core::render {
    SOASpriteRGB::SOASpriteRGB(core::types::u16 w, core::types::u16 h) : width_{w}, height_{h} {
        r_buffer_raw_ = new core::types::u8[w * h + 8];
        g_buffer_raw_ = new core::types::u8[w * h + 8];
        b_buffer_raw_ = new core::types::u8[w * h + 8];
        for(core::types::ptr_size i = 0; i < w * h + 8; ++i)
         {
             r_buffer_raw_[i] = 0;
             g_buffer_raw_[i] = 0;
             b_buffer_raw_[i] = 0;
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
    }

    SOASpriteRGB::~SOASpriteRGB() {
        delete [] b_buffer_raw_;
        delete [] g_buffer_raw_;
        delete [] r_buffer_raw_;
    }

    void SOASpriteRGB::blit_on_opengl_buffer(core::types::u8* dest_cbuf, core::types::u16 dw, core::types::u16 dh){
        core::types::u8* b_data = &b_buffer_[0];
        core::types::u8* g_data = &g_buffer_[0];
        core::types::u8* r_data = &r_buffer_[0];
        core::types::u8* d_data = &dest_cbuf[0];

        __m128i zero_batch = _mm_set1_epi8(0);

        for(core::types::ptr_size i = dw * dh; i; i -= 16) {
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

    core::types::u16 SOASpriteRGB::width() const {
        return width_;
    }

    core::types::u16 SOASpriteRGB::height() const {
        return height_;
    }
}