﻿#pragma once

#include "../IDrawPass.h"
#include "../Sub/ForwardPass.h"
#include "../Sub/ImGuiPass.h"

namespace GameEngine
{
    class ForwardDrawPass : public IDrawPass
    {
        void Initialize() override
        {
            m_SubPasses.push_back(std::make_shared<ForwardPass>());
            m_SubPasses.push_back(std::make_shared<ImGuiPass>());
            for (auto pass : m_SubPasses)
            {
                pass->Initialize();
            }
        }

        void Draw() override
        {
            for (auto pass : m_SubPasses)
            {
                pass->Draw();
            }
        }
    };
}  // namespace GameEngine