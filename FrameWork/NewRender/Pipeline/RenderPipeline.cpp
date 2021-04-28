#include "RenderPipeline.h"

#include "../Core/GERDevice.h"
#include "RenderFlow.h"

namespace GameEngine
{
    namespace ger
    {
        void RenderPipeline::Initialize()
        {
        }

        void RenderPipeline::Activate()
        {
            for (const auto flow : v_RenderFlowList)
                flow->Activate();
        }

        void RenderPipeline::Render()
        {
        }

        void RenderPipeline::Destroy()
        {
        }

    }
}