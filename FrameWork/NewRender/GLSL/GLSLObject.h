#pragma once

#include <glad/glad.h>

#include "../Core/GERObject.h"
#include <map>
#include <string>

namespace GameEngine
{
    namespace ger
    {
        struct GPUBuffer
        {
            BufferUsage usage;
            GLuint glBuffer;
            uint size;
            uint8_t *buffer = nullptr;
        };
        typedef std::vector<GPUBuffer *> GPUBufferList;

        struct GPUTexture
        {
            TextureInfo textureInfo;

            GLuint glTexture = 0;
            GLenum glType = 0;
            GLenum glTarget = 0;
            GLenum glFormat = 0;
            GLenum glInternelFmt = 0;
        };
        typedef std::vector<GPUTexture *> GPUTextureList;

        struct GPUFrameBuffer
        {
            GPUTextureList gpuColorTextures;
            GPUTexture *gpuDepthStencilTexture = nullptr;
            GLuint glFramebuffer = 0;
        };

        struct GPUUniformBlock final
        {
        };
        typedef std::vector<GPUUniformBlock> GPUUniformBlockList;

        struct GPUShaderStage
        {
            ShaderStageFlagBit type;
            std::string source;
            GLuint glShader = 0;
        };
        typedef std::vector<GPUShaderStage> GPUShaderStageList;

        struct GPUUniformSampler final
        {
            // uint set = GFX_INVALID_BINDING;
            // uint binding = GFX_INVALID_BINDING;
            // uint idx = 0;
            // std::string name;
            // uint size = 0;
            // uint glBinding = GFX_INVALID_BINDING;
            // GPUUniformList glUniforms;
            // GPUUniformList glActiveUniforms;
        };
        typedef std::vector<GPUUniformSampler> GPUUniformSamplerList;

        struct GPUInput final
        {
            // void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,const GLvoid * pointer);
            //https://baike.baidu.com/item/glVertexAttribPointer/6483823?fr=aladdin
            std::string name;
            GLint index = -1;
            uint size = 0;
            GLenum glType = 0;
            GLboolean isNormalized;
            uint stride = 0;
        };
        typedef std::vector<GPUInput> GPUInputList;

        struct GPUShader
        {
            std::string name;
            GLuint glProgram = 0;
            UniformBlockList blocks;
            UniformSamplerList samplers;

            GPUShaderStageList gpuStages;

            GPUInputList glInputs;
            GPUUniformBlockList glBlocks;
            GPUUniformSamplerList glSamplers;
        };

        struct GPUInputAssembler
        {
            GLuint glVAO;
            AttributeList attributes;
            GPUBuffer *gpuVertexBuffer = nullptr;
            GPUBuffer *gpuIndexBuffer = nullptr;
        };
    }
}