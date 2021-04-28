#pragma once

#include "../Core/GERTexture.h"
namespace GameEngine
{
    namespace ger
    {
        struct GPUTexture;
        class GLSLTexture : public Texture
        {
        public:
            GLSLTexture(Device *device);
            ~GLSLTexture();
            virtual bool Initialize(const TextureInfo &info) override;
            virtual void Destroy() override;

            GPUTexture *GetGPUTexture() { return gpuTexture; }

        private:
            GPUTexture *gpuTexture;
        };
    }
}
