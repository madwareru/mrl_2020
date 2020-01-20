#include <cstddef>
#include <cstdint>
#include <cstring>

#include <core/loaders/png_loader.h>
#include <core/render/soa_sprite_rgb.h>
#include <core/render/soa_sprite_rgba.h>

#include <util/defer_action.h>
#include <util/macro_shared.h>

#include <lodepng.h>

namespace core::loaders {
    std::shared_ptr<core::render::SOASpriteRGB> load_sprite_from_png_24(const char* filename) {
        std::uint8_t* image_bytes = nullptr;
        std::uint32_t lodepng_w, lodepng_h;

        const auto lodepng_err = lodepng_decode24_file(&image_bytes, &lodepng_w, &lodepng_h, filename);
        LOG("Loaded image with w = " << static_cast<std::int32_t>(lodepng_w) << ", h = " << static_cast<std::int32_t>(lodepng_h));

        DEFER([&image_bytes]()
        {
            if (image_bytes != nullptr) {
                free(reinterpret_cast<void*>(image_bytes));
            }
        })

        if(lodepng_err != 0) {
            LOG_ERROR("error " << lodepng_err << ": " << lodepng_error_text(lodepng_err));
            return std::make_shared<core::render::SOASpriteRGB>(1,1);
        }

        auto result = std::make_shared<core::render::SOASpriteRGB>(lodepng_w, lodepng_h);
        result->lock([image_bytes](auto dw, auto dh, auto r_buf, auto g_buf, auto b_buf){
            std::uint8_t* p = image_bytes;
            for(std::size_t j = 0; j < dh; ++j){
                for(std::size_t i = 0; i < dw; ++i){
                    *r_buf++= *p++;
                    *g_buf++= *p++;
                    *b_buf++= *p++;
                }
            }
        });
        return result;
    }

    std::shared_ptr<core::render::SOASpriteRGB> load_sprite_from_png_24(std::string& memory_buffer) {
        std::uint8_t* image_bytes = nullptr;
        std::uint32_t lodepng_w, lodepng_h;

        const char* in_bytes = memory_buffer.c_str();
        std::uint8_t* in_bytes_copy = new std::uint8_t[memory_buffer.size()];
        std::memcpy((void*)in_bytes_copy, (void*)in_bytes, memory_buffer.size());
        DEFER([&in_bytes_copy]() {delete [] in_bytes_copy; });

        const auto lodepng_err = lodepng_decode24(
            &image_bytes,
            &lodepng_w,
            &lodepng_h,
            in_bytes_copy,
            memory_buffer.size()
        );
        DEFER([&image_bytes]()
        {
            if (image_bytes != nullptr) {
                free(reinterpret_cast<void*>(image_bytes));
            }
        })

        if(lodepng_err != 0) {
            LOG_ERROR("error " << lodepng_err << ": " << lodepng_error_text(lodepng_err));
            return std::make_shared<core::render::SOASpriteRGB>(1,1);
        }

        auto result = std::make_shared<core::render::SOASpriteRGB>(lodepng_w, lodepng_h);
        result->lock([image_bytes](auto dw, auto dh, auto r_buf, auto g_buf, auto b_buf){
            std::uint8_t* p = image_bytes;
            for(std::size_t j = 0; j < dh; ++j){
                for(std::size_t i = 0; i < dw; ++i){
                    *r_buf++= *p++;
                    *g_buf++= *p++;
                    *b_buf++= *p++;
                }
            }
        });
        return result;
    }

    std::shared_ptr<core::render::SOASpriteRGBA> load_sprite_from_png_32(const char* filename) {
        std::uint8_t* image_bytes = nullptr;
        std::uint32_t lodepng_w, lodepng_h;

        const auto lodepng_err = lodepng_decode32_file(&image_bytes, &lodepng_w, &lodepng_h, filename);
        LOG("Loaded image with w = " << static_cast<std::int32_t>(lodepng_w) << ", h = " << static_cast<std::int32_t>(lodepng_h));

        DEFER([&image_bytes]()
        {
            if (image_bytes != nullptr) {
                free(reinterpret_cast<void*>(image_bytes));
            }
        })

        if(lodepng_err != 0) {
            LOG_ERROR("error " << lodepng_err << ": " << lodepng_error_text(lodepng_err));
            return std::make_shared<core::render::SOASpriteRGBA>(1,1);
        }

        auto result = std::make_shared<core::render::SOASpriteRGBA>(lodepng_w, lodepng_h);
        result->lock([image_bytes](auto dw, auto dh, auto r_buf, auto g_buf, auto b_buf, auto a_buf){
            std::uint8_t* p = image_bytes;
            for(std::size_t j = 0; j < dh; ++j){
                for(std::size_t i = 0; i < dw; ++i){
                    *r_buf++= *p++;
                    *g_buf++= *p++;
                    *b_buf++= *p++;
                    *a_buf++= *p++;
                }
            }
        });
        return result;
    }

}