#include <core/math.h>
#include <cmath>

namespace core::math {
    core::types::vec2f vsum(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs
    ) {
        return core::types::vec2f {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    core::types::vec2f vdiff(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs
    ) {
        return core::types::vec2f {lhs.x - rhs.x, lhs.y - rhs.y};
    }

    core::types::vec2f vmul(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs
    ) {
        return core::types::vec2f {lhs.x * rhs.x, lhs.y * rhs.y};
    }

    core::types::vec2f vmul(
        core::types::f32 f, 
        core::types::vec2f rhs
    ) {
        return core::types::vec2f {f * rhs.x, f * rhs.y};
    }


    core::types::f32 dot(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs
    ) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    core::types::f32 mix(
        core::types::f32 lhs, 
        core::types::f32 rhs, 
        core::types::f32 a
    ) {
        return lhs + (rhs - lhs) * (a > 1.0f ? 1.0f : a < 0.0f ? 0.0 : a);
    }

    core::types::vec2f mix(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs, 
        core::types::f32 a
    ) {
        const core::types::f32 clamped_a = a > 1.0f ? 1.0f : a < 0.0f ? 0.0 : a;
        return core::types::vec2f {
            static_cast<core::types::f32>(lhs.x + (rhs.x - lhs.x) * clamped_a),
            static_cast<core::types::f32>(lhs.y + (rhs.y - lhs.y) * clamped_a)
        };
    }

    core::types::f32 floor(core::types::f32 f) { return std::floorf(f); }
    core::types::f32 fract(core::types::f32 f) { return f - floor(f); }
    core::types::vec2f floor(const core::types::vec2f& v) {
        return core::types::vec2f{ floor(v.x), floor(v.y) };
    }
    core::types::vec2f fract(const core::types::vec2f& v) {
        return core::types::vec2f{ fract(v.x), fract(v.y) };
    }
}