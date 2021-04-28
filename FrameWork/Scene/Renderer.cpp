#include "Renderer.h"

#include "AssetManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

#include "../NewRender/Core/GERBuffer.h"
#include "../NewRender/Core/GERDevice.h"
#include "../NewRender/Core/GERInputAssembler.h"
#include "../NewRender/Core/GERObject.h"

namespace GameEngine
{
    extern SceneManager *g_pSceneManager;
    extern AssetManager *g_pAssetManager;

    void Renderer::Prepare()
    {
    }

    Renderer::Renderer()
    {
        m_ClassID = ClassID(Renderer);
    }

    Renderer::~Renderer()
    {

    }

    SharedMesh Renderer::GetMesh()
    {
        return m_Mesh;
    }

    std::vector<std::string> Renderer::GetMaterialPaths()
    {
        return m_MaterialPaths;
    }

    void Renderer::OnSerialize(cJSON *root)
    {
        SerializableHelper::Seserialize(root, "m_Materials", m_MaterialPaths);
        SerializableHelper::Seserialize(root, "m_Mesh", m_MeshPath);
        Object::OnSerialize(root);
    }
    void Renderer::OnDeserialize(cJSON *root)
    {
        m_MaterialPaths = SerializableHelper::DeserializeVectorString(root, "m_Materials");
        m_MeshPath = SerializableHelper::DeserializeString(root, "m_Mesh");
        m_Mesh = (g_pAssetManager->LoadMesh(m_MeshPath));
        ger::Device *device = ger::Device::getInstance();
        for (size_t iMesh = 0; iMesh < m_Mesh->m_MeshDatas.size(); iMesh++)
        {
            ger::BufferInfo info;
            info.usage = ger::BufferUsage::INDEX;
            info.size = m_Mesh->m_MeshDatas[iMesh].indices.size() * sizeof(float);
            ger::GERBuffer *bufferIndex = device->CreateBuffer(info);
            device->p_GERCommandBuffer->UpdateBuffer(bufferIndex, &m_Mesh->m_MeshDatas[iMesh].indices);

            info.usage = ger::BufferUsage::VERTEX;
            info.size = m_Mesh->m_MeshDatas[iMesh].vertex.size() * sizeof(float);
            ger::GERBuffer *bufferVertex = device->CreateBuffer(info);
            device->p_GERCommandBuffer->UpdateBuffer(bufferVertex, &m_Mesh->m_MeshDatas[iMesh].vertex);

            ger::InputAssemblerInfo inputInfo;
            inputInfo.indexBuffer = bufferIndex;
            inputInfo.vertexBuffers = bufferVertex;

            ger::VertexAttributeList attrs;
            for (auto attr : m_Mesh->m_MeshDatas[iMesh].attribs)
            {
                ger::VertexAttribute vAttr;
                vAttr.attrSizeBytes = attr.attribSizeBytes;
                vAttr.type = ger::Type::FLOAT4;
                vAttr.location = attr.vertexAttrib;
                vAttr.size = attr.size;
                attrs.push_back(vAttr);
            }
            inputInfo.attributes = attrs;
            ger::InputAssembler *input = device->CreateInputAssembler(inputInfo);
            inputs.push_back(input);
        }

        Object::OnDeserialize(root);
    }

} // namespace GameEngine
