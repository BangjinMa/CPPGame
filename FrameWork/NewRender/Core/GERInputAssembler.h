#pragma once
#include "GERObject.h"
namespace GameEngine
{
    namespace ger
    {
        class Device;
        class InputAssembler
        {
        public:
            InputAssembler(Device *device);
            ~InputAssembler();

        public:
            virtual bool Initialize(const InputAssemblerInfo &info) = 0;
            virtual void Destroy() = 0;

        protected:
            Device *p_Device;
        };

    }
}