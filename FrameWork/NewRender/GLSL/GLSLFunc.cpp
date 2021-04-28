#include "GLSLFunc.h"

#include <glad/glad.h>
#include <string>

#include "GLSLDevice.h"
#include "GLSLShader.h"
#include "GPUObject.h"

namespace GameEngine
{
    namespace ger
    {
        uint GLTypeSize(GLenum glType)
        {
            switch (glType)
            {
            case GL_BOOL:
                return 4;
            case GL_BOOL_VEC2:
                return 8;
            case GL_BOOL_VEC3:
                return 12;
            case GL_BOOL_VEC4:
                return 16;
            case GL_INT:
                return 4;
            case GL_INT_VEC2:
                return 8;
            case GL_INT_VEC3:
                return 12;
            case GL_INT_VEC4:
                return 16;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_INT_VEC2:
                return 8;
            case GL_UNSIGNED_INT_VEC3:
                return 12;
            case GL_UNSIGNED_INT_VEC4:
                return 16;
            case GL_FLOAT:
                return 4;
            case GL_FLOAT_VEC2:
                return 8;
            case GL_FLOAT_VEC3:
                return 12;
            case GL_FLOAT_VEC4:
                return 16;
            case GL_FLOAT_MAT2:
                return 16;
            case GL_FLOAT_MAT2x3:
                return 24;
            case GL_FLOAT_MAT2x4:
                return 32;
            case GL_FLOAT_MAT3x2:
                return 24;
            case GL_FLOAT_MAT3:
                return 36;
            case GL_FLOAT_MAT3x4:
                return 48;
            case GL_FLOAT_MAT4x2:
                return 32;
            case GL_FLOAT_MAT4x3:
                return 48;
            case GL_FLOAT_MAT4:
                return 64;
            case GL_SAMPLER_2D:
                return 4;
            case GL_SAMPLER_2D_ARRAY:
                return 4;
            case GL_SAMPLER_2D_ARRAY_SHADOW:
                return 4;
            case GL_SAMPLER_3D:
                return 4;
            case GL_SAMPLER_CUBE:
                return 4;
            case GL_INT_SAMPLER_2D:
                return 4;
            case GL_INT_SAMPLER_2D_ARRAY:
                return 4;
            case GL_INT_SAMPLER_3D:
                return 4;
            case GL_INT_SAMPLER_CUBE:
                return 4;
            case GL_UNSIGNED_INT_SAMPLER_2D:
                return 4;
            case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
                return 4;
            case GL_UNSIGNED_INT_SAMPLER_3D:
                return 4;
            case GL_UNSIGNED_INT_SAMPLER_CUBE:
                return 4;
            default:
            {
                return 0;
            }
            }
        }

        GLenum MapGLInternalFormat(Format format)
        {
            switch (format)
            {

            case Format::RGB8:
                return GL_RGB;
            case Format::RGBA8:
                return GL_RGBA;
            default:
            {
                return GL_RGBA;
            }
            }
        }

        GLenum FormatToGLFormat(Format format)
        {
            switch (format)
            {
            case Format::RGB8:
            case Format::RGBA8:
            default:
            {
                return GL_RGBA;
            }
            }
        }

        GLenum FormatToGLType(Format format)
        {
            switch (format)
            {
            case Format::RGB8:
                return GL_UNSIGNED_BYTE;
            case Format::RGBA8:
                return GL_UNSIGNED_BYTE;
            default:
            {
                return GL_UNSIGNED_BYTE;
            }
            }
        }

        GLenum MapGLType(Type type)
        {
            switch (type)
            {
            case Type::BOOL:
                return GL_BOOL;
            case Type::BOOL2:
                return GL_BOOL_VEC2;
            case Type::BOOL3:
                return GL_BOOL_VEC3;
            case Type::BOOL4:
                return GL_BOOL_VEC4;
            case Type::INT:
                return GL_INT;
            case Type::INT2:
                return GL_INT_VEC2;
            case Type::INT3:
                return GL_INT_VEC3;
            case Type::INT4:
                return GL_INT_VEC4;
            case Type::UINT:
                return GL_UNSIGNED_INT;
            case Type::FLOAT:
                return GL_FLOAT;
            case Type::FLOAT2:
                return GL_FLOAT_VEC2;
            case Type::FLOAT3:
                return GL_FLOAT_VEC3;
            case Type::FLOAT4:
                return GL_FLOAT_VEC4;
            case Type::MAT2:
                return GL_FLOAT_MAT2;
            case Type::MAT3:
                return GL_FLOAT_MAT3;
            case Type::MAT4:
                return GL_FLOAT_MAT4;
            case Type::SAMPLER2D:
                return GL_SAMPLER_2D;
            // case Type::SAMPLER3D:
            //     return GL_SAMPLER_3D_OES;
            case Type::SAMPLER_CUBE:
                return GL_SAMPLER_CUBE;
            default:
            {
                return GL_NONE;
            }
            }
        }

        Type MapType(GLenum glType)
        {
            switch (glType)
            {
            case GL_BOOL:
                return Type::BOOL;
            case GL_BOOL_VEC2:
                return Type::BOOL2;
            case GL_BOOL_VEC3:
                return Type::BOOL3;
            case GL_BOOL_VEC4:
                return Type::BOOL4;
            case GL_INT:
                return Type::INT;
            case GL_INT_VEC2:
                return Type::INT2;
            case GL_INT_VEC3:
                return Type::INT3;
            case GL_INT_VEC4:
                return Type::INT4;
            case GL_UNSIGNED_INT:
                return Type::UINT;
            case GL_FLOAT:
                return Type::FLOAT;
            case GL_FLOAT_VEC2:
                return Type::FLOAT2;
            case GL_FLOAT_VEC3:
                return Type::FLOAT3;
            case GL_FLOAT_VEC4:
                return Type::FLOAT4;
            case GL_FLOAT_MAT2:
                return Type::MAT2;
            case GL_FLOAT_MAT3:
                return Type::MAT3;
            case GL_FLOAT_MAT4:
                return Type::MAT4;
            case GL_SAMPLER_2D:
                return Type::SAMPLER2D;
            // case GL_SAMPLER_3D_OES:
            //     return Type::SAMPLER3D;
            case GL_SAMPLER_CUBE:
                return Type::SAMPLER_CUBE;
            default:
            {
                return Type::UNKNOWN;
            }
            }
        }

        void GLSLFuncCreateShader(GLSLDevice *device, GPUShader *gpuShader)
        {
            GLenum glShaderStage = 0;
            std::string shaderStageStr;
            GLint status;

            for (auto gpuStage : gpuShader->gpuStages)
            {
                switch (gpuStage.type)
                {
                case ShaderStageFlagBit::VERTEX:
                {
                    glShaderStage = GL_VERTEX_SHADER;
                    shaderStageStr = "Vertex Shader";
                    break;
                }
                case ShaderStageFlagBit::FRAGMENT:
                {
                    glShaderStage = GL_FRAGMENT_SHADER;
                    shaderStageStr = "Fragment Shader";
                    break;
                }
                case ShaderStageFlagBit::GEOMETRY:
                {
                    glShaderStage = GL_GEOMETRY_SHADER;
                    shaderStageStr = "Geometry Shader";
                    break;
                }
                default:
                {
                    return;
                }
                }
                gpuStage.glShader = glCreateShader(glShaderStage);
                const char *source = gpuStage.source.c_str();
                glShaderSource(gpuStage.glShader, 1, (const GLchar **)&source, nullptr);
                glCompileShader(gpuStage.glShader);
                glGetShaderiv(gpuStage.glShader, GL_COMPILE_STATUS, &status);
                if (status != GL_TRUE)
                {
                    GLsizei length;
                    glGetShaderiv(gpuStage.glShader, GL_SHADER_SOURCE_LENGTH, &length);
                    GLchar *src = (GLchar *)malloc(sizeof(GLchar) * length);

                    glGetShaderSource(gpuStage.glShader, length, nullptr, src);
                    free(src);

                    return;
                }
            }
            gpuShader->glProgram = glCreateProgram();

            for (size_t i = 0; i < gpuShader->gpuStages.size(); ++i)
            {
                GPUShaderStage &gpuStage = gpuShader->gpuStages[i];
                glAttachShader(gpuShader->glProgram, gpuStage.glShader);
            }

            glLinkProgram(gpuShader->glProgram);

            for (size_t i = 0; i < gpuShader->gpuStages.size(); ++i)
            {
                GPUShaderStage &gpuStage = gpuShader->gpuStages[i];
                if (gpuStage.glShader)
                {
                    glDetachShader(gpuShader->glProgram, gpuStage.glShader);
                    glDeleteShader(gpuStage.glShader);
                    gpuStage.glShader = 0;
                }
            }

            glGetProgramiv(gpuShader->glProgram, GL_LINK_STATUS, &status);
            if (status != GL_TRUE)
            {
                GLsizei length;
                glGetShaderiv(gpuShader->glProgram, GL_SHADER_SOURCE_LENGTH, &length);
                GLchar *src = (GLchar *)malloc(sizeof(GLchar) * length);

                glGetShaderSource(gpuShader->glProgram, length, nullptr, src);
                free(src);

                return;
            }

            GLint attrMaxLength = 0;
            GLint attrCount = 0;
            glGetProgramiv(gpuShader->glProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attrMaxLength);
            glGetProgramiv(gpuShader->glProgram, GL_ACTIVE_ATTRIBUTES, &attrCount);

            GLchar glName[256];
            GLsizei glLength;
            GLsizei glSize;
            GLenum glType;

            gpuShader->glInputs.resize(attrCount);
            for (GLint i = 0; i < attrCount; ++i)
            {
                GPUInput &gpuInput = gpuShader->glInputs[i];

                memset(glName, 0, sizeof(glName));
                glGetActiveAttrib(gpuShader->glProgram, i, attrMaxLength, &glLength, &glSize, &glType, glName);

                gpuInput.glLoc = glGetAttribLocation(gpuShader->glProgram, glName);
                gpuInput.binding = gpuInput.glLoc;
                gpuInput.name = glName;
                gpuInput.type = MapType(glType);
                gpuInput.stride = GLTypeSize(glType);
                gpuInput.count = glSize;
                gpuInput.size = gpuInput.stride * gpuInput.count;
                gpuInput.glType = glType;
            }
        }

        void GLSLFuncDestroyShader(GLSLDevice *device, GPUShader *gpuShader)
        {
            if (gpuShader->glProgram)
            {

                glDeleteProgram(gpuShader->glProgram);
                gpuShader->glProgram = 0;
            }
        }

        void GLSLFuncCreateTexture(GLSLDevice *device, GPUTexture *gpuTexture)
        {
            gpuTexture->glInternelFmt = MapGLInternalFormat(gpuTexture->textureInfo.formate);
            gpuTexture->glFormat = FormatToGLFormat(gpuTexture->textureInfo.formate);
            gpuTexture->glType = FormatToGLType(gpuTexture->textureInfo.formate);

            switch (gpuTexture->textureInfo.type)
            {
            case TextureType::TEX2D:
            {
                gpuTexture->glTarget = GL_TEXTURE_2D;
                glGenTextures(1, &gpuTexture->glTexture);
                glBindTexture(GL_TEXTURE_2D, gpuTexture->glTexture);
                uint w = gpuTexture->textureInfo.width;
                uint h = gpuTexture->textureInfo.height;
                glTexImage2D(GL_TEXTURE_2D, 0, gpuTexture->glInternelFmt, w, h, 0, gpuTexture->glFormat, gpuTexture->glType, nullptr);
                break;
            }

            default:
                break;
            }
        }

        void GLSLFuncDestroyTexture(GLSLDevice *device, GPUTexture *gpuTexture)
        {
            if (gpuTexture->glTexture)
            {
                glDeleteTextures(1, &gpuTexture->glTexture);
                gpuTexture->glTexture = 0;
            }
        }

        void GLSLFuncCreateFrameBuffer(GLSLDevice *device, GPUFrameBuffer *gpuFrameBuffer)
        {
            int colorCount = gpuFrameBuffer->gpuColorTextures.size();
            glGenFramebuffers(1, &gpuFrameBuffer->glFramebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, gpuFrameBuffer->glFramebuffer);
            GLenum attachments[4] = {0};
            uint attachmentCount = 0;
            // for (size_t i = 0; i < colorCount; i++)
            {
                int i = 0;
                GPUTexture *gpuColorTexture = gpuFrameBuffer->gpuColorTextures[i];
                if (gpuColorTexture)
                {
                    GLint mipmapLevel = 0;
                    glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)(GL_COLOR_ATTACHMENT0 + i), gpuColorTexture->glTarget, gpuColorTexture->glTexture, mipmapLevel);

                    attachments[attachmentCount++] = (GLenum)(GL_COLOR_ATTACHMENT0 + i);
                }
            }
            if (gpuFrameBuffer->gpuDepthStencilTexture)
            {
                GPUTexture *gpuDepthStencilTexture = gpuFrameBuffer->gpuDepthStencilTexture;
                const GLenum glAttachment = GL_DEPTH_ATTACHMENT;
                glFramebufferTexture2D(GL_FRAMEBUFFER, glAttachment, gpuDepthStencilTexture->glTarget, gpuDepthStencilTexture->glTexture, 0);
            }
            glDrawBuffers(attachmentCount, attachments);
        }

        void GLSLFuncDestroyFrameBuffer(GLSLDevice *device, GPUFrameBuffer *gpuFrameBuffer)
        {
            if (gpuFrameBuffer->glFramebuffer)
            {
                glDeleteFramebuffers(1, &gpuFrameBuffer->glFramebuffer);
                gpuFrameBuffer->glFramebuffer = 0;
            }
        }

        void GLSLFuncCopyBuffersToTexture(GLSLDevice *device, const uint8_t *buffers, GPUTexture *gpuTexture)
        {
            switch (gpuTexture->glTarget)
            {
            case GL_TEXTURE_2D:
            {
                uint w = gpuTexture->textureInfo.width;
                uint h = gpuTexture->textureInfo.height;
                glTexSubImage2D(GL_TEXTURE_2D, 1, 0, 0, w, h, gpuTexture->glFormat, gpuTexture->glType, (GLvoid *)buffers);
            }
            default:
                break;
            }
        }

        void GLSLFuncUpdateBuffer(GLSLDevice *device, GPUBuffer *gpuBuffer, const void *buffer)
        {
            switch (gpuBuffer->usage)
            {
            case BufferUsage::INDEX:
            {
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, gpuBuffer->size, buffer);
                break;
            }
            case BufferUsage::VERTEX:
            {
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, gpuBuffer->size, buffer);
                break;
            }
            case BufferUsage::UNIFORM:
            {
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, gpuBuffer->size, buffer);
                break;
            }
            default:
                break;
            }
        }

        void GLSLFuncCreateBuffer(GLSLDevice *device, GPUBuffer *gpuBuffer)
        {
            GLuint memoryUsage = GL_DYNAMIC_DRAW;
            switch (gpuBuffer->usage)
            {
            case BufferUsage::UNIFORM:
            {
                glGenBuffers(1, &gpuBuffer->glBuffer);
                if (gpuBuffer->size)
                {
                    glBindBuffer(GL_UNIFORM_BUFFER, gpuBuffer->glBuffer);
                    glBufferData(GL_UNIFORM_BUFFER, gpuBuffer->size, nullptr, memoryUsage);
                    glBindBuffer(GL_UNIFORM_BUFFER, 0);
                }
                break;
            }
            case BufferUsage::INDEX:
            {
                glGenBuffers(1, &gpuBuffer->glBuffer);
                if (gpuBuffer->size)
                {
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpuBuffer->glBuffer);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, gpuBuffer->size, nullptr, memoryUsage);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                }
                break;
            }
            case BufferUsage::VERTEX:
            {
                glGenBuffers(1, &gpuBuffer->glBuffer);
                if (gpuBuffer->size)
                {
                    glBindBuffer(GL_ARRAY_BUFFER, gpuBuffer->glBuffer);
                    glBufferData(GL_ARRAY_BUFFER, gpuBuffer->size, nullptr, memoryUsage);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                }
                break;
            }
            default:
                break;
            }
        }

        void GLSLFuncDestroyBuffer(GLSLDevice *device, GPUBuffer *gpuBuffer)
        {
            glDeleteBuffers(1, &gpuBuffer->glBuffer);
            gpuBuffer->glBuffer = 0;
        }

        void GLSLFuncCreateInputAssembler(GLSLDevice *device, GPUInputAssembler *gpuInputAssembler)
        {
        }

        void GLSLFuncDestroyInputAssembler(GLSLDevice *device, GPUInputAssembler *gpuInputAssembler)
        {
            glDeleteVertexArrays(1, &gpuInputAssembler->glVAO);
        }

        void GLSLFuncBindVAO(GLSLDevice *device, GPUInputAssembler *gpuInputAssembler, GPUShader *shader)
        {
            glGenVertexArrays(1, &gpuInputAssembler->glVAO);
            for (size_t i = 0; i < shader->glInputs.size(); i++)
            {
                auto input = shader->glInputs[i];
                for (size_t iaIndex = 0; iaIndex < gpuInputAssembler->attributes.size(); iaIndex++)
                {
					VertexAttribute iaInput = gpuInputAssembler->attributes[iaIndex];
                    if (input.name == iaInput.name)
                    {
                        glBindBuffer(GL_ARRAY_BUFFER, gpuInputAssembler->gpuIndexBuffer->glBuffer);

                        GLint glLoc = input.glLoc;
                        // GL_CHECK(glEnableVertexAttribArray(glLoc));
                        // GL_CHECK(glVertexAttribPointer(glLoc, input.count, gpuAttribute.glType, gpuAttribute.isNormalized, gpuAttribute.stride, BUFFER_OFFSET(attribOffset)));
                    }
                }
            }
        }

    }
}