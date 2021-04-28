#pragma once

#include "GERObject.h"
#include <string>

namespace GameEngine
{
    namespace ger
    {
        class Device;
        class FrameBuffer
        {
        public:
            FrameBuffer(Device *d);
            ~FrameBuffer();

        public:
            virtual bool Initialize(const FrameBufferInfo &info) = 0;
            virtual void Destroy() = 0;

        protected:
            Device *_device;
        };
    }
}