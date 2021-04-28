#include "GLSLShader.h"

#include "GLSLFunc.h"
#include "GPUObject.h"

namespace GameEngine
{
    namespace ger
    {
        GLSLShader::GLSLShader(Device *device) : Shader(device) {}

        GLSLShader::~GLSLShader() {}

        bool GLSLShader::Initialize(const ShaderInfo &info)
        {
            shaderInfo.stages = info.stages;
            shaderInfo.attributes = info.attributes;
            shaderInfo.blocks = info.blocks;
            shaderInfo.samplers = info.samplers;

            gpuShaderData = new GPUShader();
            gpuShaderData->blocks = info.blocks;
            gpuShaderData->samplers = info.samplers;
            for (const auto &stage : info.stages)
            {
                GPUShaderStage gpuShaderStage = {stage.type, stage.source};
                gpuShaderData->gpuStages.emplace_back(std::move(gpuShaderStage));
            }
            GLSLFuncCreateShader((GLSLDevice *)_device, gpuShaderData);
            return true;
        }
        void GLSLShader::Destroy()
        {
            if (gpuShaderData)
            {
                GLSLFuncDestroyShader((GLSLDevice *)_device, gpuShaderData);
                gpuShaderData = nullptr;
            }
        }
    }
}