#include "GraphicsFunc.h"

#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include "AssetManager.h"
#include "BaseApplication.h"
#include "Camera.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "easylogging++.h"
#include "glm/glm.hpp"
#include "../NewRender/Core/GERDevice.h"
namespace GameEngine
{
    extern AssetManager *g_pAssetManager;
    extern ShaderManager *g_pShaderManager;
    extern BaseApplication *g_pApp;
    int textureIndex = 0;
    void GraphicsFunc::SetTexture(SharedShaderProgramBase shader, std::string name, int id)
    {
        shader->Use();
        shader->setInt(name, textureIndex);
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        glBindTexture(GL_TEXTURE_2D, id);
        textureIndex++;
    }
    void GraphicsFunc::SetTextureArray(SharedShaderProgramBase shader, std::string name, int id)
    {
        shader->Use();
        shader->setInt(name, textureIndex);
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        glBindTexture(GL_TEXTURE_2D_ARRAY, id);
        textureIndex++;
    }

    // void GraphicsFunc::PrepareMaterial(SharedMaterial material, Frame &frame)
    // {
    //     if (material->shaderID <= 0)
    //         material->shaderID = g_pShaderManager->AddShaderByPath(
    //             material->GetShaderPath(ShaderType::Vertex),
    //             material->GetShaderPath(ShaderType::Fragment));
    //     textureIndex = 0;
    //     auto shader = g_pShaderManager->GetShaderProgram(material->shaderID);
    //     shader->Use();
    //     SetTexture(shader, "shadowMap", frame.shadowMap);
    //     for (size_t i = 0; i < material->m_MaterialDatas.size(); i++)
    //     {
    //         switch (material->m_MaterialDatas[i].m_Type)
    //         {
    //         case MaterialType::T_Mat4:
    //         {
    //             auto property = reinterpret_cast<float *>(material->m_MaterialDatas[i].m_Buffer->GetData());
    //             shader->setMat4(material->m_MaterialDatas[i].m_Name, &property[0]);
    //             break;
    //         }
    //         case MaterialType::T_Texture:
    //         {
    //             std::string property = reinterpret_cast<char *>(material->m_MaterialDatas[i].m_Buffer->GetData());
    //             int location = glGetUniformLocation(shader->m_ProgramID, material->m_MaterialDatas[i].m_Name.c_str());
    //             if (location != -1)
    //             {
    //                 SharedTexture image = g_pAssetManager->LoadTexture(property);
    //                 if (!image)
    //                     image = g_pAssetManager->getWhiteTexture();
    //                 if (image->id <= 0)
    //                 {
    //                     BindTexture(image);
    //                 }
    //                 SetTexture(shader, material->m_MaterialDatas[i].m_Name, image->id);
    //             }
    //             break;
    //         }
    //         default:
    //             break;
    //         }
    //     }
    // }

    void GraphicsFunc::BindTexture(SharedTexture texture)
    {
        GLenum format;
        if (texture->formate == 1)
            format = GL_RED;
        else if (texture->formate == 3)
            format = GL_RGB;
        else if (texture->formate == 4)
            format = GL_RGBA;

        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, texture->Width, texture->Height, 0, format, GL_UNSIGNED_BYTE, texture->data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        texture->id = textureID;
    }

    void GraphicsFunc::BindCubeTexture(SharedCube cube)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        for (unsigned int i = 0; i < 6; i++)
        {
            auto cubeValue = cube->GetValueByDir(i);
            SharedTexture image = g_pAssetManager->LoadTexture(cubeValue.path);
            if (!image)
                image = g_pAssetManager->getWhiteTexture();
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, image->Width, image->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        cube->SetTextureID(textureID);
    }

    void GraphicsFunc::DrawCubeTexture(SharedCube cube, int shaderID)
    {
        if (!cube)
            return;
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        auto shader = g_pShaderManager->GetShaderProgram(shaderID);
        glDepthFunc(GL_LEQUAL);
        shader->Use();

        auto scene = g_pSceneManager->GetScene();
        SharePtr<Camera> camera = *(scene->m_Cameras.begin());
        auto cameraTs = camera->GetParent()->GetComponent<Transform>();

        auto view = glm::mat4(glm::mat3(cameraTs->GetMatrix()));
        shader->setMat4("u_view_matrix", view);

        shader->setMat4("u_projection_matrix", camera->GetProjectionMatrix());

        shader->setInt("skybox", 0);
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_CUBE_MAP, cube->GetTextureID());
        ModelRenderConfig config;
        config.index = 0;
        config.mesh = cube->GetMesh();
        PrepareMesh(config);
        glDepthFunc(GL_LESS);

        glDisable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
    }

    void GraphicsFunc::PrepareMesh(ModelRenderConfig config)
    {

        auto mesh = config.mesh;
        auto index = config.index;
        if (!mesh)
            return;
        ger::Device *device = ger::Device::getInstance();
        //device->p_GERCommandBuffer->
    }

#pragma region 设置Uniform
    void GraphicsFunc::SetLightInfo(const LightInfo &lightInfo, Frame &frame)
    {
        if (frame.m_uboLightInfo < 0)
        {
            glGenBuffers(1, &(GLuint)frame.m_uboLightInfo);
        }

        glBindBuffer(GL_UNIFORM_BUFFER, frame.m_uboLightInfo);

        glBufferData(GL_UNIFORM_BUFFER, kSizeLightInfo, &lightInfo,
                     GL_DYNAMIC_DRAW);

        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void GraphicsFunc::SetViewInfos(const ViewInfos &infos, Frame &frame)
    {
        if (frame.m_uboCameraInfo < 0)
        {
            glGenBuffers(1, &(GLuint)frame.m_uboCameraInfo);
        }

        glBindBuffer(GL_UNIFORM_BUFFER, frame.m_uboCameraInfo);

        glBufferData(GL_UNIFORM_BUFFER, sizeof(ViewInfos), &infos,
                     GL_DYNAMIC_DRAW);

        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void GraphicsFunc::SetModelInfos(const ModelInfos &infos, Frame &frame)
    {
        if (frame.m_uboModelInfo < 0)
        {
            glGenBuffers(1, &(GLuint)frame.m_uboModelInfo);
        }

        glBindBuffer(GL_UNIFORM_BUFFER, frame.m_uboModelInfo);

        glBufferData(GL_UNIFORM_BUFFER, sizeof(ModelInfos), &infos,
                     GL_DYNAMIC_DRAW);

        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void GraphicsFunc::SetShadowInfos(const ShadowInfos &infos, Frame &frame)
    {
        if (frame.m_uboShadowInfos < 0)
        {
            glGenBuffers(1, &(GLuint)frame.m_uboShadowInfos);
        }

        glBindBuffer(GL_UNIFORM_BUFFER, frame.m_uboShadowInfos);

        glBufferData(GL_UNIFORM_BUFFER, sizeof(ShadowInfos), &infos,
                     GL_DYNAMIC_DRAW);

        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void GraphicsFunc::SetUBOData(SharedShaderProgramBase shader, Frame &frame)
    {
        shader->Use();

        int blockIndex = glGetUniformBlockIndex(shader->m_ProgramID, "LightInfo");
        if (blockIndex != GL_INVALID_INDEX)
        {
            int32_t blockSize;

            glGetActiveUniformBlockiv(shader->m_ProgramID, blockIndex,
                                      GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
            int size = sizeof(LightInfo);
            assert(blockSize >= size);

            glUniformBlockBinding(shader->m_ProgramID, blockIndex, 0);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, frame.m_uboLightInfo);
        }

        blockIndex = glGetUniformBlockIndex(shader->m_ProgramID, "ViewInfos");
        if (blockIndex != GL_INVALID_INDEX)
        {
            int32_t blockSize;

            glGetActiveUniformBlockiv(shader->m_ProgramID, blockIndex,
                                      GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
            int size = sizeof(ViewInfos);
            assert(blockSize >= size);

            glUniformBlockBinding(shader->m_ProgramID, blockIndex, 1);
            glBindBufferBase(GL_UNIFORM_BUFFER, 1, frame.m_uboCameraInfo);
        }

        blockIndex = glGetUniformBlockIndex(shader->m_ProgramID, "ModelInfos");
        if (blockIndex != GL_INVALID_INDEX)
        {
            int32_t blockSize;

            glGetActiveUniformBlockiv(shader->m_ProgramID, blockIndex,
                                      GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
            int size = sizeof(ModelInfos);
            assert(blockSize >= size);

            glUniformBlockBinding(shader->m_ProgramID, blockIndex, 2);
            glBindBufferBase(GL_UNIFORM_BUFFER, 2, frame.m_uboModelInfo);
        }

        blockIndex = glGetUniformBlockIndex(shader->m_ProgramID, "ShadowInfos");
        if (blockIndex != GL_INVALID_INDEX)
        {
            int32_t blockSize;

            glGetActiveUniformBlockiv(shader->m_ProgramID, blockIndex,
                                      GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
            int size = sizeof(ShadowInfos);
            assert(blockSize >= size);

            glUniformBlockBinding(shader->m_ProgramID, blockIndex, 3);
            glBindBufferBase(GL_UNIFORM_BUFFER, 3, frame.m_uboShadowInfos);
        }
    }

#pragma endregion

#pragma region 阴影
    void GraphicsFunc::BeginShadow(int layerIndex, unsigned int &shadow, unsigned int &shadowFBO)
    {
        const int32_t kShadowMapWidth = 1024;
        const int32_t kShadowMapHeight = 1024;

        if (shadowFBO <= 0)
            glGenFramebuffers(1, &shadowFBO);

        glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, (GLuint)shadow, 0, layerIndex);

        auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
            assert(0);

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glDepthMask(GL_TRUE);
        glClear(GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, kShadowMapWidth, kShadowMapHeight);
    }
    void GraphicsFunc::EndShadow(Frame &frame)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        auto config = g_pApp->GetGfxConfiguration();
        glViewport(0, 0, config.screenWidth, config.screenHeight);
    }
    void GraphicsFunc::GetTextureArray(unsigned int &id, int count)
    {
        // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
        const int32_t kShadowMapWidth = 1024;
        const int32_t kShadowMapHeight = 1024;

        const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, id);
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_DEPTH_COMPONENT24, kShadowMapWidth, kShadowMapHeight, count);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT24, SHADOW_WIDTH, SHADOW_HEIGHT, count, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    }

    int GraphicsFunc::GetShadowArray(unsigned int &shadow)
    {
        // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
        const int32_t kShadowMapWidth = 1024;
        const int32_t kShadowMapHeight = 1024;

        const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

        glGenTextures(1, &shadow);
        glBindTexture(GL_TEXTURE_2D, shadow);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                     SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // register the shadow map
        return static_cast<intptr_t>(shadow);
    }
    void GraphicsFunc::DeleteShadowTexture(Frame &frame)
    {
        if (frame.shadowMap > 0)
        {
            glDeleteTextures(1, &frame.shadowMap);
            frame.shadowMap = 0;
        }

        if (frame.sumShadowSTA > 0)
        {
            glDeleteTextures(frame.sumShadowCount, &frame.sumShadowSTA);
            frame.sumShadowCount = 0;
        }
    }

#pragma endregion

    int GraphicsFunc::GetFrameBufferObject(Frame &frame)
    {
        if (frame.shadowFBO <= 0)
        {
            glGenFramebuffers(1, &frame.shadowFBO);
            glBindFramebuffer(GL_FRAMEBUFFER, frame.shadowFBO);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        return frame.shadowFBO;
    }

    void GraphicsFunc::DeleteFrameBufferObject(Frame &frame)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &frame.shadowFBO);
        frame.shadowFBO = 0;
        auto config = g_pApp->GetGfxConfiguration();
        glViewport(0, 0, config.screenWidth, config.screenHeight);
    }

} // namespace GameEngine