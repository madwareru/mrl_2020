#pragma once

#include <core/types.h>

namespace core::noise {
    core::types::f32 noise(
        const core::types::vec2f& p, 
        const core::types::vec2f& seed_xy
    );
    core::types::f32 fbm_noise(
        const core::types::vec2f& p, 
        const core::types::vec2f& seed_xy, 
        core::types::u32 octaves    
    );
}