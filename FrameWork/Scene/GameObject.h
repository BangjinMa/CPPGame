#pragma once

#include <list>
#include <map>

#include "ClassIDs.h"
#include "Config.h"
#include "IBehaviour.h"
#include "Mesh.h"
#include "Object.h"
#include "Transform.h"
#include "BoundingBox.h"

namespace GameEngine
{

    class GameObject : public Object, public IBehaviour
    {
        friend class Component;

    public:
        virtual void Start() override;
        virtual void OnEnable() override;
        virtual void Update() override;
        virtual void Destory() override;

        static SharedGameObject CreateGameObject();
        template <class T>
        SharePtr<T> GetComponent();
        template <class T>
        SharePtr<T> AddComponent(SharePtr<T> component);
        template <class T>
        void RemoveComponent(SharePtr<T> component);
        template <class T>
        SharePtr<T> AddComponent(T *component);

        void AddChild(SharedGameObject child);
        void DeleteChild(SharedGameObject child);

        SharedGameObject GetChildByName(std::string name);
        SharedGameObject GetChildByID(int id);

        SharedGameObject GetParent();
        void SetParent(SharedGameObject parent);

        virtual void OnSerialize(cJSON *root) override;
        virtual void OnDeserialize(cJSON *root) override;

        SharedComponent ParserComp(cJSON *root);

        void SetName(std::string name);
        std::string GetName();

        void CalculateAABB();
        BoundingBox GetAABB(){return m_AABB;}

        GameObject();
        virtual ~GameObject();

        std::map<int, SharedGameObject> GetChildren()
        {
            return m_children;
        }

    private:
        std::vector<SharePtr<Component>> m_compenents;
        SharedGameObject m_Parent;
        std::map<int, SharedGameObject> m_children;

    public:
        BoundingBox m_AABB;
        std::string m_Name = "";
        bool m_isVisual = true;
        std::weak_ptr<GameObject> m_GameObject;
    };

    template <class T>
    inline SharePtr<T> GameObject::GetComponent()
    {
        for (unsigned int i = 0; i < m_compenents.size(); ++i)
        {
            auto &com = m_compenents[i];
            auto t = std::dynamic_pointer_cast<T>(com);
            if (t)
            {
                return t;
            }
        }
        return SharePtr<T>();
    }

    template <class T>
    inline void GameObject::RemoveComponent(SharePtr<T> component)
    {
        for (unsigned int i = 0; i < m_compenents.size(); ++i)
        {
            auto &com = m_compenents[i];
            if (component->getClassID() == com->getClassID())
            {
                m_compenents.erase(m_compenents.begin() + i);
            }
        }
    }
    template <class T>
    inline SharePtr<T> GameObject::AddComponent(SharePtr<T> component)
    {
        if (component)
        {
            component->SetParent(m_GameObject.lock());
            RemoveComponent<T>(component);
            m_compenents.push_back(component);
            return component;
        }
        return SharePtr<T>();
    }

    template <class T>
    inline SharePtr<T> GameObject::AddComponent(T *component)
    {
        SharePtr<T> t = SharePtr<T>(component);
        auto com = AddComponent<T>(t);
        return com;
    }

}  // namespace GameEngine