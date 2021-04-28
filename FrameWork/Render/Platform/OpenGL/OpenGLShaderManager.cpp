#include "OpenGLShaderManager.h"

#include "AssetLoader.h"
#include "Shader.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;

    int OpenGLShaderManager::AddShaderByPath(std::string vspath, std::string fspath)
    {
        std::string vertStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(vspath.c_str());
        std::string fragStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(fspath.c_str());
        return AddShaderByString(vertStr, fragStr);
    }

    int OpenGLShaderManager::AddShaderByString(std::string vspath, std::string fspath)
    {
        SharedShaderProgramBase shader = std::make_shared<ShaderProgram>();
        bool flag = true;
        flag = shader->AddShaderFromSourceCode(ShaderType::Vertex, vspath.c_str());
        flag = shader->AddShaderFromSourceCode(ShaderType::Fragment, fspath.c_str());
        flag = shader->Link();
        return AddShader(shader);
    }
} // namespace GameEngine
