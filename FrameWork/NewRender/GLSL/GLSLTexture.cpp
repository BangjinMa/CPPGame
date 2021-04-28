#include "GLSLTexture.h"
#include "GLSLFunc.h"
#include "GPUObject.h"
namespace GameEngine
{
    namespace ger
    {
        GLSLTexture::GLSLTexture(Device *device) : Texture(device) {}
        GLSLTexture::~GLSLTexture() {}

        bool GLSLTexture::Initialize(const TextureInfo &info)
        {
            gpuTexture = new GPUTexture();
            gpuTexture->textureInfo = info;
            GLSLFuncCreateTexture((GLSLDevice *)_device, gpuTexture);
            return true;
        }

        void GLSLTexture::Destroy()
        {
            if (gpuTexture)
            {
                GLSLFuncDestroyTexture((GLSLDevice *)_device, gpuTexture);
                gpuTexture = nullptr;
            }
        }
    }
}
