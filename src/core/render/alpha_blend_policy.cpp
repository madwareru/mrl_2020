#include <core/render/alpha_blend_policy.h>
#include <core/render/soa_sprite_rgb.h>
#include <core/render/soa_sprite_rgba.h>
#include <emmintrin.h>

namespace core::render {
    void AlphaBlendPolicy::blit(
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

    void AlphaBlendPolicy::blit(
        SOASpriteRGBA& src, 
        SOASpriteRGB& dest,
        core::types::u16 dx, core::types::u16 dy, 
        core::types::u16 sx, core::types::u16 sy, 
        core::types::u16 w, core::types::u16 h
    ){
        src.lock([&](auto sw, auto sh, auto src_r_buffer, auto src_g_buffer, auto src_b_buffer, auto src_a_buffer){
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

                core::types::u8* a_data_l = &src_a_buffer[src_stride_start];
                core::types::u8* b_data_l = &src_b_buffer[src_stride_start];
                core::types::u8* g_data_l = &src_g_buffer[src_stride_start];
                core::types::u8* r_data_l = &src_r_buffer[src_stride_start];

                core::types::u8* db_data_l = &dest_b_buffer[dst_stride_start];
                core::types::u8* dg_data_l = &dest_g_buffer[dst_stride_start];
                core::types::u8* dr_data_l = &dest_r_buffer[dst_stride_start];

                auto m_z = _mm_set1_epi32(0);

                for(core::types::u16 j = span_count; j; --j) {
                    core::types::u8* a_data = a_data_l;
                    core::types::u8* b_data = b_data_l;
                    core::types::u8* g_data = g_data_l;
                    core::types::u8* r_data = r_data_l;

                    core::types::u8* db_data = db_data_l;
                    core::types::u8* dg_data = dg_data_l;
                    core::types::u8* dr_data = dr_data_l;

                    for(core::types::u16 i = span16_count; i; --i) {
                        auto ad = _mm_loadu_si128(reinterpret_cast<__m128i*>(a_data));
                        auto bd = _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data));
                        auto gd = _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data));
                        auto rd = _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data));

                        auto dbd = _mm_loadu_si128(reinterpret_cast<__m128i*>(db_data));
                        auto dgd = _mm_loadu_si128(reinterpret_cast<__m128i*>(dg_data));
                        auto drd = _mm_loadu_si128(reinterpret_cast<__m128i*>(dr_data));

                        // prepare data by unpacking and interlieving

                        auto m_a_lo = _mm_unpacklo_epi8(ad, m_z);
                        auto m_a_hi = _mm_unpackhi_epi8(ad, m_z);

                        auto m_b_lo = _mm_unpacklo_epi8(bd, m_z);
                        auto m_b_hi = _mm_unpackhi_epi8(bd, m_z);

                        auto m_g_lo = _mm_unpacklo_epi8(gd, m_z);
                        auto m_g_hi = _mm_unpackhi_epi8(gd, m_z);

                        auto m_r_lo = _mm_unpacklo_epi8(rd, m_z);
                        auto m_r_hi = _mm_unpackhi_epi8(rd, m_z);

                        auto m_db_lo = _mm_unpacklo_epi8(dbd, m_z);
                        auto m_db_hi = _mm_unpackhi_epi8(dbd, m_z);

                        auto m_dg_lo = _mm_unpacklo_epi8(dgd, m_z);
                        auto m_dg_hi = _mm_unpackhi_epi8(dgd, m_z);

                        auto m_dr_lo = _mm_unpacklo_epi8(drd, m_z);
                        auto m_dr_hi = _mm_unpackhi_epi8(drd, m_z);

                        // calculating diffs:

                        #define DIFFR(x, lohi) \
                            auto df_##x##_##lohi = _mm_sub_epi16(m_##x##_##lohi, m_d##x##_##lohi)
                        #define DIFF_COMP(x) DIFFR(x, lo); DIFFR(x, hi)
                            DIFF_COMP(b);
                            DIFF_COMP(g);
                            DIFF_COMP(r);
                        #undef DIFF_COMP
                        #undef DIFFR

                        // accs:

                        #define ACC(x, lohi) \
                            auto acc_##x##_##lohi = _mm_mullo_epi16(df_##x##_##lohi, m_a_##lohi)
                        #define ACC_COMP(x) ACC(x, lo); ACC(x, hi)
                            ACC_COMP(b);
                            ACC_COMP(g);
                            ACC_COMP(r);
                        #undef ACC_COMP
                        #undef ACC

                        // adds:

                        #define ADD_ACC(x, lohi) \
                            auto add_##x##_##lohi = \
                            _mm_srli_epi16(_mm_add_epi16(_mm_slli_epi16(m_d##x##_##lohi, 8), acc_##x##_##lohi), 8)
                        #define ADD_ACC_COMP(x) ADD_ACC(x, lo); ADD_ACC(x, hi)
                            ADD_ACC_COMP(b);
                            ADD_ACC_COMP(g);
                            ADD_ACC_COMP(r);
                        #undef ADD_ACC_COMP
                        #undef ADD_ACC

                        // finals:

                        _mm_storeu_si128(reinterpret_cast<__m128i*>(db_data), _mm_packus_epi16(add_b_lo, add_b_hi));
                        _mm_storeu_si128(reinterpret_cast<__m128i*>(dg_data), _mm_packus_epi16(add_g_lo, add_g_hi));
                        _mm_storeu_si128(reinterpret_cast<__m128i*>(dr_data), _mm_packus_epi16(add_r_lo, add_r_hi));

                        db_data += 16;
                        dg_data += 16;
                        dr_data += 16;

                        a_data += 16;
                        b_data += 16;
                        g_data += 16;
                        r_data += 16;
                    }

                    for(core::types::u16 i = span_width; i; --i) {
                        auto alpha = *a_data++;

                        const auto dst_b = *db_data;
                        const auto dst_g = *dg_data;
                        const auto dst_r = *dr_data;

                        *db_data++ = (dst_b * (255 - alpha) + *b_data++ * alpha) / 256;
                        *dg_data++ = (dst_g * (255 - alpha) + *g_data++ * alpha) / 256;
                        *dr_data++ = (dst_r * (255 - alpha) + *r_data++ * alpha) / 256;
                    }

                    a_data_l += sw;
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