#include <core/render/standart_blit_policy.h>
#include <core/render/soa_sprite_rgb.h>
#include <emmintrin.h>

namespace core::render {
    void StandartBlit::blit(
        SOASpriteRGB& src, 
        SOASpriteRGB& dest,
        std::uint16_t dx, std::uint16_t dy, 
        std::uint16_t sx, std::uint16_t sy, 
        std::uint16_t w, std::uint16_t h) {
        src.lock([&](auto sw, auto sh, auto src_r_buffer, auto src_g_buffer, auto src_b_buffer){
            dest.lock([&](auto dw, auto dh, auto dest_r_buffer, auto dest_g_buffer, auto dest_b_buffer){
                std::uint16_t span_width = dw - dx;
                if(span_width > w) {
                    span_width = w;
                }

                std::uint16_t span16_count = span_width / 16;
                span_width %= 16;

                std::uint16_t span_count = dh - dy;
                if(span_count > sh) {
                    span_count = sh;
                }
                if(span_count > h) {
                    span_count = h;
                }

                std::uint8_t* b_data_l = &src_b_buffer[sx + sw * sy];
                std::uint8_t* g_data_l = &src_g_buffer[sx + sw * sy];
                std::uint8_t* r_data_l = &src_r_buffer[sx + sw * sy];

                std::uint8_t* db_data_l = &dest_b_buffer[dx + dw * dy];
                std::uint8_t* dg_data_l = &dest_g_buffer[dx + dw * dy];
                std::uint8_t* dr_data_l = &dest_r_buffer[dx + dw * dy];

                for(std::uint16_t j = span_count; j; --j) {
                    std::uint8_t* b_data = b_data_l;
                    std::uint8_t* g_data = g_data_l;
                    std::uint8_t* r_data = r_data_l;

                    std::uint8_t* db_data = db_data_l;
                    std::uint8_t* dg_data = dg_data_l;
                    std::uint8_t* dr_data = dr_data_l;

                    for(std::uint16_t i = span16_count; i; --i) {
                        _mm_storeu_si128(reinterpret_cast<__m128i*>(db_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data)));
                        _mm_storeu_si128(reinterpret_cast<__m128i*>(dg_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data)));
                        _mm_storeu_si128(reinterpret_cast<__m128i*>(dr_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data)));
                        db_data += 16;
                        dg_data += 16;
                        dr_data += 16;

                        b_data += 16;
                        g_data += 16;
                        r_data += 16;
                    }

                    for(std::uint16_t i = span_width; i; --i) {
                        *db_data++ = *b_data++;
                        *dg_data++ = *g_data++;
                        *dr_data++ = *r_data++;
                    }

                    b_data_l += sw;
                    g_data_l += sw;
                    r_data_l += sw;

                    db_data_l += dw;
                    dg_data_l += dw;
                    dr_data_l += dw;
                }
            });
        });
    }

    void StandartBlit::blit(
        SOASpriteRGBA& src, 
        SOASpriteRGBA& dest,
        std::uint16_t dx, std::uint16_t dy, 
        std::uint16_t sx, std::uint16_t sy, 
        std::uint16_t w, std::uint16_t h
    ){
        // TODO
    }
}