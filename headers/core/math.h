#pragma once

#include <core/types.h>

namespace core::math {
    inline core::types::vec2f vsum(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs
    );
    inline core::types::vec2f vdiff(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs
    );
    inline core::types::vec2f vmul(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs
    );
    inline core::types::vec2f vmul(
        core::types::f32 f, 
        core::types::vec2f rhs
    );
    inline core::types::f32 dot(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs
    );
    inline core::types::f32 mix(
        core::types::f32 lhs, 
        core::types::f32 rhs, 
        core::types::f32 a
    );
    inline core::types::vec2f mix(
        const core::types::vec2f& lhs, 
        const core::types::vec2f& rhs, 
        core::types::f32 a
    );

    inline core::types::f32 floor(core::types::f32 f);
    inline core::types::f32 fract(core::types::f32 f);
    inline core::types::vec2f floor(const core::types::vec2f& v);
    inline core::types::vec2f fract(const core::types::vec2f& v);
}