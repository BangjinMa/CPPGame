#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Config.h"
#include "Render/Frame.h"

namespace GameEngine
{
    class MeshData;

    class GraphicsFunc
    {
    public:
        static void BindTexture(SharedTexture texture);
        static void BindCubeTexture(SharedCube cube);
        static void DrawCubeTexture(SharedCube cube, int shaderID);
        static void PrepareMesh(ModelRenderConfig);
        // static void PrepareMaterial(SharedMaterial, Frame& frame);

#pragma region 设置Uniform
        static void SetTexture(SharedShaderProgramBase shader, std::string name, int id);
        static void SetTextureArray(SharedShaderProgramBase shader, std::string name, int id);
        static void SetUBOData(SharedShaderProgramBase shader, Frame& frame);
        static void SetLightInfo(const LightInfo& lightInfo, Frame& frame);
        static void SetViewInfos(const ViewInfos& infos, Frame& frame);
        static void SetModelInfos(const ModelInfos& infos, Frame& frame);
        static void SetShadowInfos(const ShadowInfos& infos, Frame& frame);
#pragma endregion

#pragma region 阴影
        static void BeginShadow(int layerIndex, unsigned int& shadow, unsigned int& shadowFBO);
        static void EndShadow(Frame& frame);
        static int GetShadowArray(unsigned int& shadow);
        static void DeleteShadowTexture(Frame& frame);
        static void GetTextureArray(unsigned int &id, int count);
#pragma endregion

        static int GetFrameBufferObject(Frame& frame);
        static void DeleteFrameBufferObject(Frame& frame);
    };

}  // namespace GameEngine