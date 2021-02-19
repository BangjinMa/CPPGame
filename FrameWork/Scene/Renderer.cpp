﻿#include "Renderer.h"

#include "AssetManager.h"
#include "GameObject.h"
#include "Material.h"
#include "Scene.h"
#include "SceneManager.h"

namespace GameEngine
{
    extern SceneManager* g_pSceneManager;
    extern AssetManager* g_pAssetManager;

    void Renderer::Prepare()
    {
        // for (int i = 0; i < m_Materials.size(); ++i)
        // {
        //     auto &material = m_Materials[i];
        //     if (material)
        //     {
        //         material->Prepare();
        //     }
        // }
    }

    Renderer::Renderer()
    {
        m_ClassID = ClassID(Renderer);
    }

    SharedMesh Renderer::getMesh()
    {
        return SharedMesh();
    }

    std::vector<SharedMaterial> Renderer::getMaterials()
    {
        return m_Materials;
    }

    void Renderer::AddMaterial(SharedMaterial material)
    {
        m_Materials.push_back(material);
    }

    void Renderer::Render(ViewInfos viewInfos)
    {
    }

    void Renderer::Start()
    {
        if (m_Started)
            return;
        auto renderer = GetParent()->getComponent<Renderer>();
        if (!renderer)
            return;
        auto scene = g_pSceneManager->GetScene();
        scene->AddRenderer(std::dynamic_pointer_cast<Renderer>(renderer));
        Component::Start();
    }

    void Renderer::OnSerialize(cJSON* root)
    {
        SerializableHelper::Seserialize(root, "m_Materials", m_MaterialPaths);
        Object::OnSerialize(root);
    }
    void Renderer::OnDeserialize(cJSON* root)
    {
        m_MaterialPaths = SerializableHelper::DeserializeVectorString(root, "m_Materials");
        for (auto material : m_MaterialPaths)
        {
            AddMaterial(g_pAssetManager->LoadMaterial(material));
        }

        Object::OnDeserialize(root);
    }

}  // namespace GameEngine
