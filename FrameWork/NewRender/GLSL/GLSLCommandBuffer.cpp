#include "GLSLCommandBuffer.h"
#include "GLSLBuffer.h"
#include "GLSLFunc.h"
#include "GLSLInputAssembler.h"
#include "GLSLShader.h"
namespace GameEngine
{
    namespace ger
    {

        GLSLCommandBuffer::GLSLCommandBuffer(Device *device) : GERCommandBuffer(device) {}
        GLSLCommandBuffer::~GLSLCommandBuffer() {}

        void GLSLCommandBuffer::Initialize() {}
        void GLSLCommandBuffer::Destroy() {}

        void GLSLCommandBuffer::BindVAO(Shader *shader, InputAssembler *ia)
        {
            GLSLFuncBindVAO((GLSLDevice *)p_Device, ((GLSLInputAssembler *)ia)->GetGPUInputAssembler(), ((GLSLShader *)shader)->GetGPUShader());
        }

        void GLSLCommandBuffer::UpdateBuffer(GERBuffer *buffer, const void *data)
        {
        }

    }
}
