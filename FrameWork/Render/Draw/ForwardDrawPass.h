#pragma once

#include "../IDrawPass.h"
#include "../Sub/CubPass.h"
#include "../Sub/ForwardPass.h"
#include "../Sub/ImGuiPass.h"
#include "../Sub/ShadowPass.h"
#include "../Sub/CSMTest.h"
namespace GameEngine
{
    class ForwardDrawPass : public IDrawPass
    {
        void Initialize() override
        {
            // m_SubPasses.push_back(std::make_shared<ShadowPass>());
            m_SubPasses.push_back(std::make_shared<ForwardPass>());
            m_SubPasses.push_back(std::make_shared<CubPass>());
            // m_SubPasses.push_back(std::make_shared<ImGuiPass>());
            for(auto pass:m_SubPasses)
            {
                pass->Initialize();
            }
        }

        void Draw(SharedCamera camera) override
        {
            IDrawPass::Draw(camera);
        }
    };
}  // namespace GameEngine
