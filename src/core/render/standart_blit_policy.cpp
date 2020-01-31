#include <core/render/standart_blit_policy.h>
#include <core/render/soa_sprite_rgb.h>
#include <core/render/soa_sprite_rgba.h>
#include <emmintrin.h>

namespace core::render {
    void StandartBlit::blit(
        SOASpriteRGB& src, 
        SOASpriteRGB& dest,
        core::types::u16 dx, core::types::u16 dy, 
        core::types::u16 sx, core::types::u16 sy, 
        core::types::u16 w, core::types::u16 h
    ) {
        src.lock([&](auto sw, auto sh, auto src_r_buffer, auto src_g_buffer, auto src_b_buffer){
            dest.lock([&](auto dw, auto dh, auto dest_r_buffer, auto dest_g_buffer, auto dest_b_buffer){
                core::types::u16 span_width = dw - dx;
                if(span_width > sw - sx) {
                    span_width = sw - sx;
                }
                if(span_width > w) {
                    span_width = w;
                }

                core::types::u16 span16_count = span_width / 16;
                span_width %= 16;

                core::types::u16 span_count = dh - dy;
                if(span_count > sh - sy) {
                    span_count = sh - sy;
                }
                if(span_count > h) {
                    span_count = h;
                }

                const core::types::ptr_size src_stride_start = sx + sw * sy;
                const core::types::ptr_size dst_stride_start = dx + dw * dy;

                core::types::u8* b_data_l = &src_b_buffer[src_stride_start];
                core::types::u8* g_data_l = &src_g_buffer[src_stride_start];
                core::types::u8* r_data_l = &src_r_buffer[src_stride_start];

                core::types::u8* db_data_l = &dest_b_buffer[dst_stride_start];
                core::types::u8* dg_data_l = &dest_g_buffer[dst_stride_start];
                core::types::u8* dr_data_l = &dest_r_buffer[dst_stride_start];

                for(core::types::u16 j = span_count; j; --j) {
                    core::types::u8* b_data = b_data_l;
                    core::types::u8* g_data = g_data_l;
                    core::types::u8* r_data = r_data_l;

                    core::types::u8* db_data = db_data_l;
                    core::types::u8* dg_data = dg_data_l;
                    core::types::u8* dr_data = dr_data_l;

                    for(core::types::u16 i = span16_count; i; --i) {
                        _mm_storeu_si128(
                            reinterpret_cast<__m128i*>(db_data), 
                            _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data))
                        );
                        _mm_storeu_si128(
                            reinterpret_cast<__m128i*>(dg_data), 
                            _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data))
                        );
                        _mm_storeu_si128(
                            reinterpret_cast<__m128i*>(dr_data), 
                            _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data))
                        );
                        db_data += 16;
                        dg_data += 16;
                        dr_data += 16;

                        b_data += 16;
                        g_data += 16;
                        r_data += 16;
                    }

                    for(core::types::u16 i = span_width; i; --i) {
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
        SOASpriteRGB& dest,
        core::types::u16 dx, core::types::u16 dy, 
        core::types::u16 sx, core::types::u16 sy, 
        core::types::u16 w, core::types::u16 h
    ){
        src.lock([&](auto sw, auto sh, auto src_r_buffer, auto src_g_buffer, auto src_b_buffer, auto a_buf_not_used){
            dest.lock([&](auto dw, auto dh, auto dest_r_buffer, auto dest_g_buffer, auto dest_b_buffer){
                core::types::u16 span_width = dw - dx;
                if(span_width > sw - sx) {
                    span_width = sw - sx;
                }
                if(span_width > w) {
                    span_width = w;
                }

                core::types::u16 span16_count = span_width / 16;
                span_width %= 16;

                core::types::u16 span_count = dh - dy;
                if(span_count > sh - sy) {
                    span_count = sh - sy;
                }
                if(span_count > h) {
                    span_count = h;
                }

                const core::types::ptr_size src_stride_start = sx + sw * sy;
                const core::types::ptr_size dst_stride_start = dx + dw * dy;

                core::types::u8* b_data_l = &src_b_buffer[src_stride_start];
                core::types::u8* g_data_l = &src_g_buffer[src_stride_start];
                core::types::u8* r_data_l = &src_r_buffer[src_stride_start];

                core::types::u8* db_data_l = &dest_b_buffer[dst_stride_start];
                core::types::u8* dg_data_l = &dest_g_buffer[dst_stride_start];
                core::types::u8* dr_data_l = &dest_r_buffer[dst_stride_start];

                for(core::types::u16 j = span_count; j; --j) {
                    core::types::u8* b_data = b_data_l;
                    core::types::u8* g_data = g_data_l;
                    core::types::u8* r_data = r_data_l;

                    core::types::u8* db_data = db_data_l;
                    core::types::u8* dg_data = dg_data_l;
                    core::types::u8* dr_data = dr_data_l;

                    for(core::types::u16 i = span16_count; i; --i) {
                        _mm_storeu_si128(
                            reinterpret_cast<__m128i*>(db_data), 
                            _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data))
                        );
                        _mm_storeu_si128(
                            reinterpret_cast<__m128i*>(dg_data), 
                            _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data))
                        );
                        _mm_storeu_si128(
                            reinterpret_cast<__m128i*>(dr_data), 
                            _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data))
                        );
                        db_data += 16;
                        dg_data += 16;
                        dr_data += 16;

                        b_data += 16;
                        g_data += 16;
                        r_data += 16;
                    }

                    for(core::types::u16 i = span_width; i; --i) {
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
}