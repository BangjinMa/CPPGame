#pragma once

#include "GERObject.h"
namespace GameEngine
{
    namespace ger
    {
        class Device;
        class GERBuffer
        {
        public:
            GERBuffer(Device *d);
            ~GERBuffer();

        public:
            virtual bool Initialize(const BufferInfo &info) = 0;
            virtual void Destroy() = 0;

        protected:
            Device *p_Device;
        };

    }
}