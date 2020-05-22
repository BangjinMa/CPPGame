#ifndef GameEngine_Image_H
#define GameEngine_Image_H

#include <cstdint>
#include "Math.h"

namespace GameEngine{
    struct Image {
        uint32_t Width;
        uint32_t Height;
        Math::R8G8B8A8Unorm* data;
        uint32_t bitcount;
        uint32_t pitch;
        size_t  data_size;
    };
}

#endif