#pragma once

#include "../Types.h"
#include "GERBuffer.h"
#include "GERCommandBuffer.h"
#include "GERFrameBuffer.h"
#include "GERInputAssembler.h"
#include "GERObject.h"
#include "GERShader.h"
#include "GERTexture.h"

namespace GameEngine
{
    namespace ger
    {
        class Device
        {
        public:
            static Device *getInstance();
            static Device *_instance;

            Device();
            virtual ~Device();

            virtual bool Initialize() = 0;
            virtual void Destroy() = 0;
            virtual void Resize(uint width, uint height) = 0;
            virtual void Acquire() = 0;
            virtual void Present() = 0;

            inline uint GetShaderID() { return _shaderIdGen++; }

            inline Shader *CreateShader(const ShaderInfo &info)
            {
                Shader *res = CreateShader();
                res->Initialize(info);
                return res;
            }

            inline FrameBuffer *CreateFramebuffer(const FrameBufferInfo &info)
            {
                FrameBuffer *res = CreateFramebuffer();
                res->Initialize(info);
                return res;
            }

            inline Texture *CreateTexture(const TextureInfo &info)
            {
                Texture *res = CreateTexture();
                res->Initialize(info);
                return res;
            }

            inline GERBuffer *CreateBuffer(const BufferInfo &info)
            {
                GERBuffer *res = CreateBuffer();
                res->Initialize(info);
                return res;
            }

            inline InputAssembler *CreateInputAssembler(const InputAssemblerInfo &info)
            {
                InputAssembler *res = CreateInputAssembler();
                res->Initialize(info);
                return res;
            }

        protected:
            virtual Shader *CreateShader() = 0;
            virtual Texture *CreateTexture() = 0;
            virtual GERBuffer *CreateBuffer() = 0;
            virtual FrameBuffer *CreateFramebuffer() = 0;
            virtual InputAssembler *CreateInputAssembler() = 0;

        private:
            uint _shaderIdGen = 0;

        public:
            GERCommandBuffer *p_GERCommandBuffer;
        };

    }
}