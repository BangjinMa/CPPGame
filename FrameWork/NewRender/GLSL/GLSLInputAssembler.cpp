#include "GLSLInputAssembler.h"

#include "GLSLBuffer.h"
#include "GLSLFunc.h"
#include "GPUObject.h"

namespace GameEngine
{
    namespace ger
    {
        GLSLInputAssembler::GLSLInputAssembler(Device *device) : InputAssembler(device) {}

        GLSLInputAssembler::~GLSLInputAssembler() {}

        bool GLSLInputAssembler::Initialize(const InputAssemblerInfo &info)
        {
            inputAssemblerInfo.attributes = info.attributes;
            inputAssemblerInfo.vertexBuffers = info.vertexBuffers;
            inputAssemblerInfo.indexBuffer = info.indexBuffer;
            p_GPUInputAssembler = new GPUInputAssembler();

            p_GPUInputAssembler->attributes = info.attributes;
            p_GPUInputAssembler->gpuIndexBuffer = ((GLSLBuffer *)info.indexBuffer)->GetGPUBuffer();
			p_GPUInputAssembler->gpuVertexBuffer = ((GLSLBuffer *)info.vertexBuffers)->GetGPUBuffer();

            GLSLFuncCreateInputAssembler((GLSLDevice*)p_Device, p_GPUInputAssembler);
			return true;
        }

        void GLSLInputAssembler::Destroy()
        {
            if (p_GPUInputAssembler)
            {
                GLSLFuncDestroyInputAssembler((GLSLDevice*)p_Device, p_GPUInputAssembler);
                delete p_GPUInputAssembler;
                p_GPUInputAssembler = nullptr;
            }
        }
    }
}
