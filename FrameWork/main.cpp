﻿#include "AssetLoader.h"
#include "AssetManager.h"
#include "BaseApplication.h"
#include "Event/EventDispatcherManager.h"
#include "Event/KeyEventDispatcher.h"
#include "GameLogic.h"
#include "InputManager.h"
#include "MemoryManager.h"
#include "Render/GraphicsManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "Utils/Clock.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
using namespace GameEngine;

namespace GameEngine
{
    extern BaseApplication *g_pApp;
    extern MemoryManager *g_pMemoryManager;
    extern InputManager *g_pInputManager;
    extern AssetLoader *g_pAssetLoader;
    extern GraphicsManager *g_pGraphicsManager;
    extern AssetManager *g_pAssetManager;
    extern ShaderManager *g_pShaderManager;
    extern GameLogic *g_pGameLogic;
    extern SceneManager *g_pSceneManager;
    extern Clock *g_pClock;
}  // namespace GameEngine

namespace EventSystem
{
    extern EventDispatcherManager *g_pEventDispatcherManager;
}

using namespace EventSystem;
int main(int argc, char *argv[])
{
    el::Loggers::getLogger("logger")->info("GameEngine Begin...");

    for (int i = 0; i < argc; i++)
        el::Loggers::getLogger("logger")->info(argv[i]);

    int ret;
    std::vector<IRuntimeModule *> run_time_modules;
    run_time_modules.push_back(g_pApp);
    run_time_modules.push_back(g_pMemoryManager);
    run_time_modules.push_back(g_pEventDispatcherManager);
    run_time_modules.push_back(g_pInputManager);
    run_time_modules.push_back(g_pAssetLoader);
    run_time_modules.push_back(g_pAssetManager);
    run_time_modules.push_back(g_pGraphicsManager);
    run_time_modules.push_back(g_pShaderManager);
    run_time_modules.push_back(g_pSceneManager);
    run_time_modules.push_back(g_pGameLogic);

    g_pClock->Initialize();
    for (auto &module : run_time_modules)
    {
        if ((ret = module->Initialize()) != 0)
        {
            el::Loggers::getLogger("logger")->error(
                "nitialize failed, will exit now.");
            return ret;
        }
    }
    int i = 1;
    while (!g_pApp->IsQuit())
    {
        g_pClock->Tick(1);
        float deltaTime = g_pClock->GetDeltaTime();
        for (auto &module : run_time_modules)
        {
            module->Tick(deltaTime);
        }
    }
    auto monitor = cJSON_CreateObject();
    g_pSceneManager->GetScene()->OnSerialize(monitor);
    auto str = cJSON_Print(monitor);
    el::Loggers::getLogger("logger")->info(str);
    g_pAssetLoader->WriteFile(str, "file_1_1_1.txt");
    for (auto &module : run_time_modules)
    {
        module->Finalize();
    }
    g_pClock->Finalize();
    for (std::vector<IRuntimeModule *>::const_iterator itr =
             run_time_modules.begin();
         itr != run_time_modules.end(); ++itr)
    {
        delete *itr;
    }
    run_time_modules.clear();

    el::Loggers::getLogger("logger")->info("GameEngine End...");
    return 0;
}
