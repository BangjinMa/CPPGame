#pragma once

#include <cstdint>
#include "MyMath.h"
#include "Object.h"

namespace GameEngine
{
    class Texture : public Object
    {
    public:
        int id;
        std::string Path;
        uint32_t Width;
        uint32_t Height;
        unsigned char *data;
        size_t data_size;
    };
} // namespace GameEngine

