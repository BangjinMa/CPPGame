#include "GLSLDevice.h"

#include "GLSLBuffer.h"
#include "GLSLCommandBuffer.h"
#include "GLSLFrameBuffer.h"
#include "GLSLInputAssembler.h"
#include "GLSLShader.h"
#include "GLSLTexture.h"

namespace GameEngine
{
    namespace ger
    {
        Device *Device::_instance = new GLSLDevice();

        Device *Device::getInstance()
        {
            return _instance;
        }

        bool GLSLDevice::Initialize()
        {
            p_GERCommandBuffer = new GLSLCommandBuffer(this);
            p_GERCommandBuffer->Initialize();
            return true;
        }
        void GLSLDevice::Destroy()
        {
            p_GERCommandBuffer->Destroy();
            delete p_GERCommandBuffer;
        }
        void GLSLDevice::Resize(uint width, uint height) {}
        void GLSLDevice::Acquire() {}
        void GLSLDevice::Present() {}

        Shader *GLSLDevice::CreateShader()
        {
            return new GLSLShader(this);
        }

        Texture *GLSLDevice::CreateTexture()
        {
            return new GLSLTexture(this);
        }

        GERBuffer *GLSLDevice::CreateBuffer()
        {
            return new GLSLBuffer(this);
        }

        FrameBuffer *GLSLDevice::CreateFramebuffer()
        {
            return new GLSLFrameBuffer(this);
        }

        InputAssembler *GLSLDevice::CreateInputAssembler()
        {
            return new GLSLInputAssembler(this);
        }
    }
}
