#pragma once

#include "../Core/GERFrameBuffer.h"
namespace GameEngine
{
    namespace ger
    {
        struct GPUFrameBuffer;
        class GLSLFrameBuffer : public FrameBuffer
        {
        public:
            GLSLFrameBuffer(Device *device);
            ~GLSLFrameBuffer();
            virtual bool Initialize(const FrameBufferInfo &info) override;
            virtual void Destroy() override;

        private:
            GPUFrameBuffer *gpuFrameBuffer;
        };
    }
}
