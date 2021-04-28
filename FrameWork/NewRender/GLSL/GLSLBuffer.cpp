
#include "GLSLBuffer.h"
#include "GLSLFunc.h"
#include "GPUObject.h"

namespace GameEngine
{
    namespace ger
    {
        GLSLBuffer::GLSLBuffer(Device *d) : GERBuffer(d) {}

        GLSLBuffer::~GLSLBuffer() {}

        bool GLSLBuffer::Initialize(const BufferInfo &info)
        {
            gerBuffer.size = info.size;
            gerBuffer.usage = info.usage;

            p_GPUBuffer = new GPUBuffer();
            p_GPUBuffer->size = info.size;
            p_GPUBuffer->usage = info.usage;
            
            GLSLFuncCreateBuffer((GLSLDevice*)p_Device, p_GPUBuffer);
			return true;
        }

        void GLSLBuffer::Destroy()
        {
            GLSLFuncDestroyBuffer((GLSLDevice*)p_Device, p_GPUBuffer);
            delete p_GPUBuffer;
        }

        GPUBuffer *GLSLBuffer::GetGPUBuffer()
        {
            return p_GPUBuffer;
        }
    }
}