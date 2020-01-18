#pragma once

#include <memory>
#include <string>

namespace core::render {
    struct SOASpriteRGB;
    struct SOASpriteRGBA;
}

namespace core::loaders {
    std::shared_ptr<core::render::SOASpriteRGB> load_sprite_from_png_24(const std::string& memory_buffer);
    std::shared_ptr<core::render::SOASpriteRGB> load_sprite_from_png_24(const char* filename);
    std::shared_ptr<core::render::SOASpriteRGBA> load_sprite_from_png_32(const char* filename);
}