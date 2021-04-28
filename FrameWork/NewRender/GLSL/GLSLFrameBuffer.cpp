#include "GLSLFrameBuffer.h"
#include "GLSLFunc.h"
#include "GPUObject.h"

namespace GameEngine
{
    namespace ger
    {
        GLSLFrameBuffer::GLSLFrameBuffer(Device *device) : FrameBuffer(device) {}
        GLSLFrameBuffer::~GLSLFrameBuffer() {}

        bool GLSLFrameBuffer::Initialize(const FrameBufferInfo &info)
        {
            gpuFrameBuffer = new GPUFrameBuffer();
            GLSLFuncCreateFrameBuffer((GLSLDevice *)_device, gpuFrameBuffer);
            return true;
        }

        void GLSLFrameBuffer::Destroy()
        {
            if (gpuFrameBuffer)
            {
                GLSLFuncDestroyFrameBuffer((GLSLDevice *)_device, gpuFrameBuffer);
                gpuFrameBuffer = nullptr;
            }
        }
    }
}
