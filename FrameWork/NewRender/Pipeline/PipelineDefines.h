#pragma once

#include <vector>

namespace GameEngine
{
    namespace ger
    {
        class RenderStage;
        class RenderFlow;

        typedef std::vector<RenderStage *> RenderStageList;
        typedef std::vector<RenderFlow *> RenderFlowList;
    }
}