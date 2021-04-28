#pragma once

#include <list>
#include <map>
#include <memory>

#include "Config.h"
#include "IRuntimeModule.h"
#include "Mesh.h"
#include "MyMath.h"
#include "Render/IDrawPass.h"
#include "Renderer.h"
#include "Frame.h"

namespace GameEngine
{
    class Scene;

    class GraphicsManager : public IRuntimeModule
    {
    public:
        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick(float deltaTime);
        virtual void Clear();
        virtual void Draw(float deltaTime);

        virtual void CalculateLights();

        LightInfo GetLightInfo();

        Frame& GetFrame(){return m_Frame;}
    protected:
        std::list<std::shared_ptr<IDrawPass>> m_IDrawPass;

        LightInfo m_LightInfos;
        Frame m_Frame;
    };

    extern GraphicsManager* g_pGraphicsManager;
}  // namespace GameEngine
