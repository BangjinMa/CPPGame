#include "GameObject.h"

#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Camera.h"
#include "Component.h"
#include "Light.h"
#include "Transform.h"

namespace GameEngine
{
    SharedGameObject

    GameObject::CreateGameObject()
    {
        auto obj = std::make_shared<GameObject>();
        obj->m_GameObject = obj;

        obj->AddComponent<Transform>(std::make_shared<Transform>());

        return obj;
    }

    void GameObject::AddChild(SharedGameObject child)
    {
        auto begin = m_children.find(child->GetID());
        if (begin != m_children.end())
        {
            return;
        }
        child->SetParent(m_GameObject.lock());
        m_children.insert(std::pair<int, SharedGameObject>(child->GetID(), child));
    }

    SharedGameObject GameObject::GetChildByName(std::string name)
    {
        for (auto child = m_children.begin(); child != m_children.end(); child++)
        {
            if (child->second->GetName() == name)
            {
                return child->second;
            }
            else
            {
                auto res = child->second->GetChildByName(name);
                if (res)
                    return res;
            }
        }
        return nullptr;
    }

    SharedGameObject GameObject::GetChildByID(int id)
    {
        for (auto child = m_children.begin(); child != m_children.end(); child++)
        {
            if (child->second->GetID() == id)
            {
                return child->second;
            }
            else
            {
                auto res = child->second->GetChildByID(id);
                if (res)
                    return res;
            }
        }

        return nullptr;
    }

    void GameObject::DeleteChild(SharedGameObject child)
    {
        auto begin = m_children.find(child->GetID());
        if (begin != m_children.end())
        {
            m_children.erase(child->GetID());
        }
    }

    void GameObject::SetParent(SharedGameObject parent)
    {
        m_Parent = parent;
    }

    SharedGameObject GameObject::GetParent()
    {
        return m_Parent;
    }

    GameObject::GameObject()
    {
    }

    GameObject::~GameObject()
    {
        m_compenents.clear();
        m_children.clear();
    }

    void GameObject::Start()
    {
        for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
        {
            (*i)->Start();
        }
        for (auto i = m_children.begin(); i != m_children.end(); i++)
        {
            i->second->Start();
        }
    }
    void GameObject::OnEnable()
    {
    }

    void GameObject::Update()
    {
        for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
        {
            (*i)->Update();
        }
        for (auto i = m_children.begin(); i != m_children.end(); i++)
        {
            i->second->Update();
        }
    }

    void GameObject::Destory()
    {
        for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
        {
            (*i)->Destory();
        }
        for (auto i = m_children.begin(); i != m_children.end(); i++)
        {
            i->second->Destory();
        }
    }

    void GameObject::OnSerialize(cJSON* root)
    {
        Object::OnSerialize(root);
        SerializableHelper::Seserialize(root, "name", GetName());
        auto gameobjects = cJSON_AddArrayToObject(root, "Children");
        for (auto child : GetChildren())
        {
            auto item = cJSON_CreateObject();
            child.second->OnSerialize(item);
            cJSON_AddItemToArray(gameobjects, item);
        }
        auto comps = cJSON_AddArrayToObject(root, "Components");
        for (auto comp : m_compenents)
        {
            auto item = cJSON_CreateObject();
            SerializableHelper::Seserialize(item, "type", comp->getClassID());
            comp->OnSerialize(item);
            cJSON_AddItemToArray(comps, item);
        }
    }
    SharedComponent GameObject::ParserComp(cJSON* root)
    {
        SharedComponent object = nullptr;
        auto type = cJSON_GetObjectItem(root, "type")->valueint;
        switch (type)
        {
        case ClassID(Transform):
        {
            SharePtr<Transform> trans = GetComponent<Transform>();

            SharePtr<Transform> temp = std::make_shared<Transform>();
            temp->OnDeserialize(root);
            temp->SetParentPosition(trans->GetPosition());
            object = temp;
            break;
        }
        case ClassID(Camera):
            object = std::make_shared<Camera>();
            object->OnDeserialize(root);
            break;
		case ClassID(Renderer):
			object = std::make_shared<Renderer>();
			object->OnDeserialize(root);
			break;
        case ClassID(PointLight):
            object = std::make_shared<PointLight>();
            object->OnDeserialize(root);
            break;
        case ClassID(AreaLight):
            object = std::make_shared<AreaLight>();
            object->OnDeserialize(root);
            break;
        case ClassID(SpotLight):
            object = std::make_shared<SpotLight>();
            object->OnDeserialize(root);
            break;
        case ClassID(DirectionalLight):
            object = std::make_shared<DirectionalLight>();
            object->OnDeserialize(root);
            break;
        default:
            break;
        }
        return object;
    }

    void GameObject::OnDeserialize(cJSON* root)
    {
        auto paramsNode = cJSON_GetObjectItem(root, "Components");
        SetName(SerializableHelper::DeserializeString(root, "name"));
        for (auto index = 0; index < cJSON_GetArraySize(paramsNode); ++index)
        {
            auto compParam = cJSON_GetArrayItem(paramsNode, index);
            auto comp = ParserComp(compParam);
            if (comp)
                AddComponent(comp);
        }

        paramsNode = cJSON_GetObjectItem(root, "Children");
        for (auto index = 0; index < cJSON_GetArraySize(paramsNode); ++index)
        {
            auto childParam = cJSON_GetArrayItem(paramsNode, index);
            auto childNode = GameObject::CreateGameObject();
            childNode->OnDeserialize(childParam);
            AddChild(childNode);
        }
        Object::OnDeserialize(root);
    }

    void GameObject::SetName(std::string name)
    {
        m_Name = name;
    }

    std::string GameObject::GetName()
    {
        return m_Name;
    }

    void GameObject::CalculateAABB()
    {
        auto mesh = GetComponent<Renderer>();

        if (mesh)
        {
            auto trans = GetComponent<Transform>();
            // transform OOBB points to world space
            auto model = trans->GetMatrix();
            VecterFloat3 vTransformed[8];
            for (int i = 0; i < 8; i++)
            {
                vTransformed[i] = model * VecterFloat4(mesh->GetMesh()->m_OOBB.m_pPoints[i], 1);
            }
            // set new AABB
            m_AABB.Set(vTransformed, 8, sizeof(VecterFloat3));
        }
    }

}  // namespace GameEngine