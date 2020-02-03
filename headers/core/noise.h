#pragma once

#include <core/types.h>

namespace core::noise {
    core::types::float noise(
        const core::types::vec2f& p, 
        const core::types::vec2f& seed_xy
    );
    core::types::float fbm_noise(
        const core::types::vec2f& p, 
        const core::types::vec2f& seed_xy, 
        core::types::u32 octaves    
    );
}