#pragma once

#include "../Core/GERDevice.h"

namespace GameEngine
{
    namespace ger
    {
        class GLSLDevice : public Device
        {
        public:
            using Device::CreateBuffer;
            using Device::CreateFramebuffer;
            using Device::CreateInputAssembler;
            using Device::CreateShader;
            using Device::CreateTexture;

        public:
            virtual bool Initialize() override;
            virtual void Destroy() override;
            virtual void Resize(uint width, uint height) override;
            virtual void Acquire() override;
            virtual void Present() override;

        protected:
            virtual Shader *CreateShader() override;
            virtual Texture *CreateTexture() override;
            virtual GERBuffer *CreateBuffer() override;
            virtual FrameBuffer *CreateFramebuffer() override;
            virtual InputAssembler *CreateInputAssembler() override;
        };

    }
}