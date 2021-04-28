#pragma once

#include "../Core/GERShader.h"
namespace GameEngine
{
    namespace ger
    {
        struct GPUShader;
        class GLSLShader : public Shader
        {
        public:
            GLSLShader(Device *device);
            ~GLSLShader();
            virtual bool Initialize(const ShaderInfo &info) override;
            virtual void Destroy() override;

            GPUShader *GetGPUShader() { return gpuShaderData; }

        private:
            GPUShader *gpuShaderData;
        };
    }
}
