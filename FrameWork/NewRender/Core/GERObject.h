#pragma once

#include <string>
#include <vector>

#include "../Types.h"

namespace GameEngine
{
    namespace ger
    {
        typedef unsigned int uint;
        typedef unsigned short ushort;
        typedef unsigned long ulong;

        enum class BufferUsage : uint
        {
            NONE = 0,
            TRANSFER_SRC = 0x1,
            TRANSFER_DST = 0x2,
            INDEX = 0x4,
            VERTEX = 0x8,
            UNIFORM = 0x10,
            STORAGE = 0x20,
            INDIRECT = 0x40,
        };

        struct BufferInfo
        {
            BufferUsage usage;
            uint size;
        };

        enum class TextureType
        {
            TEX1D,
            TEX2D,
            TEX3D,
            CUBE,
            TEX1D_ARRAY,
            TEX2D_ARRAY,
        };

        enum class Format
        {

            UNKNOWN,

            RGB8,

            RGBA8,
            // Total count
            COUNT,
        };

        struct TextureInfo
        {
            TextureType type = TextureType::TEX1D;
            Format formate = Format::UNKNOWN;
            uint width;
            uint height;
        };

        class Texture;
        typedef std::vector<Texture *> TextureList;
        struct FrameBufferInfo
        {
            TextureList colorTextures;
            Texture *depthStencilTexture = nullptr;
        };

        struct DeviceInfo
        {
        };

#pragma region Shader
        enum class Type
        {
            UNKNOWN,
            BOOL,
            BOOL2,
            BOOL3,
            BOOL4,
            INT,
            INT2,
            INT3,
            INT4,
            UINT,
            UINT2,
            UINT3,
            UINT4,
            FLOAT,
            FLOAT2,
            FLOAT3,
            FLOAT4,
            MAT2,
            MAT2X3,
            MAT2X4,
            MAT3X2,
            MAT3,
            MAT3X4,
            MAT4X2,
            MAT4X3,
            MAT4,
            SAMPLER1D,
            SAMPLER1D_ARRAY,
            SAMPLER2D,
            SAMPLER2D_ARRAY,
            SAMPLER3D,
            SAMPLER_CUBE,
            COUNT,
        };

        ///////////////////////////////////////////////
        // // Shader 类型
        ///////////////////////////////////////////////
        enum class ShaderStageFlagBit : int
        {
            NONE = 0x0,
            VERTEX = 0x1, //顶点
            CONTROL = 0x2,
            EVALUATION = 0x4,
            GEOMETRY = 0x8,  //几何
            FRAGMENT = 0x10, //片元
            COMPUTE = 0x20,
            ALL = 0x3f,
        };
        ///////////////////////////////////////////////
        // // Shader 资源
        ///////////////////////////////////////////////
        struct ShaderStage
        {
            ShaderStageFlagBit type;
            std::string source;
        };
        typedef std::vector<ShaderStage> ShaderStageList;

        struct Attribute
        {
        };
        typedef std::vector<Attribute> AttributeList;

        struct UniformSampler
        {
            uint set = 0;
            uint binding = 0;
            std::string name;
            Type type = Type::UNKNOWN;
            uint count = 0;
        };
        typedef std::vector<UniformSampler> UniformSamplerList;

        ///////////////////////////////////////////////
        // // Shader中的单条Uniform参数
        ///////////////////////////////////////////////
        struct Uniform
        {
            std::string name;
            Type type = Type::UNKNOWN;
            uint count = 0;
        };
        typedef std::vector<Uniform> UniformList;

        ///////////////////////////////////////////////
        // // Shader中 块
        ///////////////////////////////////////////////
        struct UniformBlock
        {
            uint set = 0;
            uint binding = 0;
            std::string name;
            UniformList members;
            uint count = 0u;
        };

        typedef std::vector<UniformBlock> UniformBlockList;

        ///////////////////////////////////////////////
        // // Shader 属性
        ///////////////////////////////////////////////
        struct ShaderInfo
        {
            ShaderStageList stages;
            AttributeList attributes;
            UniformBlockList blocks;
            UniformSamplerList samplers;
        };
#pragma endregion

        struct VertexAttribute
        {
			std::string name;
            Type type;
            uint size;
            uint location;
            uint attrSizeBytes;
        };

        class GERBuffer;

        typedef std::vector<VertexAttribute> VertexAttributeList;
        typedef std::vector<GERBuffer *> GERBufferList;

        struct InputAssemblerInfo
        {
            VertexAttributeList attributes;
            GERBuffer *vertexBuffers;
            GERBuffer *indexBuffer = nullptr;
        };

    }
}