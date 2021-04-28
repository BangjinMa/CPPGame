#include "GraphicsManager.h"

#include <algorithm>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "AssetLoader.h"
#include "Camera.h"
#include "GameObject.h"
#include "GraphicsFunc.h"
#include "IntersectionTests.h"
#include "Light.h"
#include "Render/Draw/ForwardDrawPass.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "easylogging++.h"

namespace GameEngine
{
    extern SceneManager *g_pSceneManager;
    extern AssetLoader *g_pAssetLoader;

    int GraphicsManager::Initialize()
    {
        m_IDrawPass.push_back(std::make_shared<ForwardDrawPass>());
        for (auto pass : m_IDrawPass)
        {
            pass->Initialize();
        }
        return 0;
    }

    void GraphicsManager::Finalize() {}

    void GraphicsManager::Clear() {}

    void GraphicsManager::Draw(float deltaTime)
    {
        auto scene = g_pSceneManager->GetScene();
        CalculateLights();
        GraphicsFunc::SetLightInfo(m_LightInfos, m_Frame);
        for (auto pass : m_IDrawPass)
        {
            pass->BeginDraw();
        }
        for (auto camera : scene->m_Cameras)
        {
            auto cameraTs = camera->GetParent()->GetComponent<Transform>();
            cameraTs->SetPosition(cameraTs->GetPosition());
            Frustum frustum = camera->CalculateFrustum(camera->GetNear(), camera->GetFar());
            ViewInfos viewInfos;
            memcpy(viewInfos.u_camera_pos, glm::value_ptr(cameraTs->GetPosition()), sizeof(float) * 3);
            memcpy(viewInfos.u_projection_matrix, glm::value_ptr(camera->GetProjectionMatrix()), sizeof(float) * 16);
            memcpy(viewInfos.u_view_matrix, glm::value_ptr(cameraTs->GetViewMatrix()), sizeof(float) * 16);
            GraphicsFunc::SetViewInfos(viewInfos, m_Frame);

            std::vector<SharedGameObject> receivers;
            for (auto child : scene->GetChildren())
            {
                child.second->CalculateAABB();
                if (IntersectionTest(child.second->GetAABB(), frustum))
                    receivers.push_back(child.second);
            }

            for (auto pass : m_IDrawPass)
            {
                pass->Draw(camera);
            }
        }
        for (auto pass : m_IDrawPass)
        {
            pass->EndDraw();
        }
    }

    void GraphicsManager::Tick(float deltaTime)
    {
    }

    void GraphicsManager::CalculateLights()
    {
        auto scene = g_pSceneManager->GetScene();
        auto lights = scene->GetLights();
        m_LightInfos.numsLight = lights.size();
        int index = -1;
        for (auto iter = lights.begin(); iter != lights.end(); iter++)
        {
            index++;
            auto light = *iter;
            m_LightInfos.lights[index].type = light->GetLightType();

            auto transfrom = light->GetParent()->GetComponent<Transform>();
            auto pos = transfrom->GetPosition();
            auto dir = -transfrom->GetForward();
            
            memcpy(m_LightInfos.lights[index].color, glm::value_ptr(light->GetColor()), sizeof(float) * 4);
            memcpy(m_LightInfos.lights[index].position, glm::value_ptr(pos), sizeof(float) * 3);
            memcpy(m_LightInfos.lights[index].direction, glm::value_ptr(dir), sizeof(float) * 3);

            auto directionalLight = std::dynamic_pointer_cast<DirectionalLight>(light);
            memcpy(m_LightInfos.lights[index].ambient, glm::value_ptr(directionalLight->GetAmbient()), sizeof(float) * 3);
            memcpy(m_LightInfos.lights[index].diffuse, glm::value_ptr(directionalLight->GetDiffuse()), sizeof(float) * 3);
            memcpy(m_LightInfos.lights[index].specular, glm::value_ptr(directionalLight->GetSpecular()), sizeof(float) * 3);
            if (m_LightInfos.lights[index].type == LightType::Type_DirectionalLight)
                continue;

            auto pointLight = std::dynamic_pointer_cast<PointLight>(light);
            m_LightInfos.lights[index].constant = pointLight->GetConstant();
            m_LightInfos.lights[index].linear = pointLight->GetLinear();
            m_LightInfos.lights[index].quadratic = pointLight->GetQuadratic();
            if (m_LightInfos.lights[index].type == LightType::Type_PointLight)
                continue;

            auto spotLight = std::dynamic_pointer_cast<SpotLight>(light);
            m_LightInfos.lights[index].cutOff = glm::cos(glm::radians(spotLight->GetCutOff()));
            m_LightInfos.lights[index].outerCutOff = glm::cos(glm::radians(spotLight->GetOuterCutOff()));
            if (m_LightInfos.lights[index].type == LightType::Type_SpotLight)
                continue;
        }
    }

    LightInfo GraphicsManager::GetLightInfo()
    {
        return m_LightInfos;
    }

}  // namespace GameEngine