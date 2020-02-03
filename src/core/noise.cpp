#include <core/noise.h>
#include <core/math.h>
#include <util/macro_shared.h>

namespace {
    core::types::vec2f noise_hash(const core::types::vec2f& x, const core::types::vec2f& seed_xy) {
        const auto k = core::types::vec2f{ 0.3183099f, 0.3678794f };
        core::types::vec2f result;
        x = core::math::vsum(seed_xy, x);
        x.x = x.x * k.x + k.y;
        x.y = x.y * k.y + k.x;
        float a = core::math::fract(x.x * x.y * (x.x + x.y));
        result = core::math::vmul(2.0f, core::math::vfract(core::math::vmul(a * 16.0f, k)));
        result.x -= 1.0f;
        result.y -= 1.0f;
        return result;
    }
}

namespace core::noise {

    core::types::float noise(
        const core::types::vec2f& p, 
        const core::types::vec2f& seed_xy
    ){
        auto i = floor(p);
        auto f = fract(p);
        const auto z = core::types::vec2f{ 3.0f, 3.0f };
        auto u = core::math::vmul(
            core::math::vdiff(z, core::math::vmul2(2.0f, f)), 
            core::math::vmul(f, f)
        );
        LOG_ASSERT(u.x >= 0.0f && u.x <= 1.0f);
        LOG_ASSERT(u.y >= 0.0f && u.y <= 1.0f);
        const auto tl = core::types::vec2f{0.0f, 0.0f};
        const auto tr = core::types::vec2f{1.0f, 0.0f};
        const auto bl = core::types::vec2f{0.0f, 1.0f};
        const auto br = core::types::vec2f{1.0f, 1.0f};
        return core::math::mix(
            core::math::mix(
                core::math::dot( noise_hash(core::math::vsum(i, tl), seed_xy), core::math::vdiff(f, tl)),
                core::math::dot( noise_hash(core::math::vsum(i, tr), seed_xy), core::math::vdiff(f, tr)),
                u.x
            ),
            core::math::mix(
                core::math::dot( noise_hash(vsum(i, bl), seed_xy), core::math::vdiff(f, bl)),
                core::math::dot( noise_hash(vsum(i, br), seed_xy), core::math::vdiff(f, br)),
                u.x
            ),
            u.y
        );
    }
    core::types::float fbm_noise(
        const core::types::vec2f& p, 
        const core::types::vec2f& seed_xy, 
        core::types::u32 octaves    
    ){
        core::types::vec2f p_acc = p;
        const core::types::f32 s = 1.98f;
        const core::types::f32 w = 0.49f;
        const core::types::f32 b = 0.5f;
        core::types::f32 r = 0.0f;
        for(core::types::u32 i = octaves; i; --i) {
            r += b * noise(p_acc, seed_xy);
            b *= w;
            p_acc = core::math::vmul(s, p_acc);
        }
        return r;
    }
}