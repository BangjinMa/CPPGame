#pragma once

#include "../Core/GERInputAssembler.h"

namespace GameEngine
{
    namespace ger
    {
        struct GPUInputAssembler;
        class GLSLInputAssembler : public InputAssembler
        {
        public:
            GLSLInputAssembler(Device *device);
            ~GLSLInputAssembler();

            virtual bool Initialize(const InputAssemblerInfo &info) override;
            virtual void Destroy() override;

            GPUInputAssembler *GetGPUInputAssembler() { return p_GPUInputAssembler; }

        private:
            GPUInputAssembler *p_GPUInputAssembler;
            InputAssemblerInfo inputAssemblerInfo;
        };
    }
}