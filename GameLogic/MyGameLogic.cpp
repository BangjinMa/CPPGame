#include "MyGameLogic.h"

#include <glm/gtx/string_cast.hpp>

#include "AssetLoader.h"
#include "BaseApplication.h"
#include "Camera.h"
#include "Event/EventDispatcherManager.h"
#include "Event/KeyEventDispatcher.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "easylogging++.h"
#include "NewRender/Core/GERDevice.h"

namespace EventSystem
{
    extern EventDispatcherManager *g_pEventDispatcherManager;
}

namespace GameEngine
{
    extern BaseApplication *g_pApp;
    extern SceneManager *g_pSceneManager;
    extern AssetLoader *g_pAssetLoader;
}  // namespace GameEngine

namespace GameEngine
{
    VecterFloat3 rotation(0);
    int MyGameLogic::Initialize()
    {
		ger::Device *device = ger::Device::getInstance();
		device->Initialize();

        std::string sceneStr = g_pAssetLoader->SyncOpenAndReadTextFileToString("Scene/new.scene");
        auto json = cJSON_Parse(sceneStr.c_str());
        m_Scene = std::make_shared<Scene>();
        m_Scene->OnDeserialize(json);
        g_pSceneManager->SetNextScene(m_Scene);
        EventCallBack callback = [this](const void *event) {
            const EventSystem::KeyEventData *pEvent = reinterpret_cast<const EventSystem::KeyEventData *>(event);
            if (pEvent->key == 256 && pEvent->action == 1)
                g_pApp->SetQuit(true);
            else if (pEvent->key == 87 && pEvent->action == 2)
            {
                auto trans = this->m_Scene->GetChildByName("cameraObject")->GetComponent<Transform>();
                auto pos = trans->GetPosition();
                pos.z += 0.02f;
                trans->SetPosition(pos);
            }
            else if (pEvent->key == 83 && pEvent->action == 2)
            {
                auto trans = this->m_Scene->GetChildByName("cameraObject")->GetComponent<Transform>();
                auto pos = trans->GetPosition();
                pos.z -= 0.02f;
                trans->SetPosition(pos);
            }
            else if (pEvent->key == 65 && pEvent->action == 2)
            {
                auto trans = this->m_Scene->GetChildByName("cameraObject")->GetComponent<Transform>();
                auto pos = trans->GetPosition();
                pos.x -= 0.02f;
                trans->SetPosition(pos);
            }
            else if (pEvent->key == 68 && pEvent->action == 2)
            {
                auto trans = this->m_Scene->GetChildByName("cameraObject")->GetComponent<Transform>();
                auto pos = trans->GetPosition();
                pos.x += 0.02f;
                trans->SetPosition(pos);
            }
        };
        EventSystem::g_pEventDispatcherManager->AddEventListener<EventSystem::KeyEventData>(callback);

        auto trans = m_Scene->GetChildByName("cameraObject")->GetComponent<Transform>();
        auto m = glm::lookAt(trans->GetPosition(), glm::vec3(0,0,0), glm::vec3(0,1,0));
        glm::vec3 rotation = RotationMatrixToEulerAngles(m);
        trans->SetRotation(rotation);
        return 0;
    }
    void MyGameLogic::Finalize() {}
    void MyGameLogic::Tick(float deltaTime)
    {

    }

}  // namespace GameEngine
