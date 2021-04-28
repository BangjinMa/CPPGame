#pragma once

namespace GameEngine
{
    namespace ger
    {
        struct GPUShader;
        struct GPUTexture;
        struct GPUFrameBuffer;
        struct GPUBuffer;
        struct GPUInputAssembler;
        class GLSLDevice;

        void GLSLFuncCreateShader(GLSLDevice *device, GPUShader *gpuShader);
        void GLSLFuncDestroyShader(GLSLDevice *device, GPUShader *gpuShader);

        void GLSLFuncCreateTexture(GLSLDevice *device, GPUTexture *gpuShader);
        void GLSLFuncDestroyTexture(GLSLDevice *device, GPUTexture *gpuShader);

        void GLSLFuncCreateFrameBuffer(GLSLDevice *device, GPUFrameBuffer *gpuShader);
        void GLSLFuncDestroyFrameBuffer(GLSLDevice *device, GPUFrameBuffer *gpuShader);

        void GLSLFuncCopyBuffersToTexture(GLSLDevice *device, const unsigned char *buffers, GPUTexture *gpuTexture);

        void GLSLFuncUpdateBuffer(GLSLDevice *device, GPUBuffer *gpuBuffer, const void *buffer);
        void GLSLFuncCreateBuffer(GLSLDevice *device, GPUBuffer *gpuBuffer);
        void GLSLFuncDestroyBuffer(GLSLDevice *device, GPUBuffer *gpuBuffer);

        void GLSLFuncCreateInputAssembler(GLSLDevice *device, GPUInputAssembler *gpuInputAssembler);
        void GLSLFuncDestroyInputAssembler(GLSLDevice *device, GPUInputAssembler *gpuInputAssembler);
        void GLSLFuncBindVAO(GLSLDevice *device, GPUInputAssembler *gpuInputAssembler, GPUShader* shader);
    }
}
