#pragma once

#include "GERObject.h"
#include <string>

namespace GameEngine
{
    namespace ger
    {
        class Device;
        class Texture
        {
        public:
            Texture(Device *d);
            ~Texture();

        public:
            virtual bool Initialize(const TextureInfo &info) = 0;
            virtual void Destroy() = 0;

        protected:
            Device *_device;
        };
    }
}