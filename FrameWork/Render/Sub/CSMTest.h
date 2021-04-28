#pragma once

#include "GraphicsManager.h"
#include "ISubPass.h"
#include "Renderer.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    class CSMTest : public ISubPass
    {
    public:
        void Initialize()
        {
            m_ShaderID2 = g_pShaderManager->AddShaderByPath("Shaders/write_depth.vert", "Shaders/write_depth.frag");
        }

        void BeginDraw()
        {
        }
        void Draw(SharedCamera camera)
        {
            auto shaderShadowMap = g_pShaderManager->GetShaderProgram(m_ShaderID2);
            shaderShadowMap->Use();

            ShadowInfos shadowInfos;

            int splitNum = camera->GetSplitNum();
            float *splitPostions = new float[splitNum + 1];
            camera->CalculateSplitPositions(splitPostions, camera->GetSplitNum());
            SharePtr<Scene> scene = g_pSceneManager->GetScene();
            std::vector<SharePtr<Light>> lights = scene->GetLights();
            if (lights.size() <= 0)
                return;
            SharePtr<Light> light = lights[0];

            Frame &frame = g_pGraphicsManager->GetFrame();
            frame.sumShadowCount = 4;
            GraphicsFunc::GetTextureArray(frame.sumShadowSTA, frame.sumShadowCount);

            int offset = 0;
            for (size_t num = 0; num < 4; num++)
            {
                Frustum frustum = camera->CalculateFrustum(splitPostions[num], splitPostions[num + 1]);
                glm::mat4 mCropMatrix = light->CalculateCropMatrix(frustum);
                memcpy(&shadowInfos.aFragPosLightSpace[offset], glm::value_ptr(mCropMatrix), sizeof(float) * 16);
                offset += 16;
                GraphicsFunc::BeginShadow(num, frame.sumShadowSTA, frame.shadowFBO);
                shaderShadowMap->setMat4("projectionMatrix", mCropMatrix);

                for (auto child : scene->GetChildren())
                {
                    auto meshRender = child.second->GetComponent<Renderer>();
                    auto modelMat = child.second->GetComponent<Transform>()->GetMatrix();
                    ModelInfos infos;
                    memcpy(infos.modelMat4, glm::value_ptr(modelMat), sizeof(float) * 16);

                    GraphicsFunc::SetModelInfos(infos, frame);
                    GraphicsFunc::SetUBOData(shaderShadowMap, frame);

                    if (meshRender && meshRender->GetMesh())
                    {
                        auto mesh = meshRender->GetMesh();
                        for (size_t mi = 0; mi < mesh->m_MeshDatas.size(); mi++)
                        {
                            ModelRenderConfig config;
                            config.index = mi;
                            config.mesh = mesh;
                            GraphicsFunc::PrepareMesh(config);
                        }
                    }
                }

                GraphicsFunc::EndShadow(frame);
            }

            for (auto child : scene->GetChildren())
            {
                auto meshRender = child.second->GetComponent<Renderer>();
                if (meshRender && meshRender->GetMesh())
                {
                    auto mesh = meshRender->GetMesh();
                    auto modelMat = child.second->GetComponent<Transform>()->GetMatrix();
                    auto materials = meshRender->GetMaterialPaths();
                    int materialID = -1;
                    for (size_t mi = 0; mi < mesh->m_MeshDatas.size(); mi++)
                    {
                        // if (mi < materials.size())
                        //     materialID = mi;
                        // if (materialID >= 0)
                        // {
                        //     ModelInfos infos;
                        //     GraphicsFunc::PrepareMaterial(materials[materialID], frame);
                        //     auto shader = g_pShaderManager->GetShaderProgram(materials[materialID]->shaderID);
                        //     memcpy(infos.modelMat4, glm::value_ptr(modelMat), sizeof(float) * 16);
                        //     GraphicsFunc::SetModelInfos(infos, frame);
                        //     for (size_t i = 0; i < 4; i++)
                        //     {
                        //         shadowInfos.afarBounds[i] = splitPostions[i + 1];
                        //     }

                        //     GraphicsFunc::SetShadowInfos(shadowInfos, frame);
                        //     GraphicsFunc::SetUBOData(shader, frame);

                        //     GraphicsFunc::SetTextureArray(shader, "shadowMap", frame.sumShadowSTA);
                        // }
                        ModelRenderConfig config;
                        config.index = mi;
                        config.mesh = mesh;
                        GraphicsFunc::PrepareMesh(config);
                    }
                }
            }
            delete splitPostions;
        }

        void EndDraw()
        {
            Frame &frame = g_pGraphicsManager->GetFrame();
            GraphicsFunc::DeleteShadowTexture(frame);
        }

    private:
        int m_ShaderID2;
    };
}
