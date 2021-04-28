#pragma once

#include "PipelineDefines.h"

namespace GameEngine
{
    namespace ger
    {
        class Device;
        class RenderPipeline
        {
        public:
            RenderPipeline(/* args */);
            ~RenderPipeline();

            virtual void Initialize();
            virtual void Activate();
            virtual void Destroy();
            virtual void Render();

        private:
            RenderFlowList v_RenderFlowList;
        };

    }
}