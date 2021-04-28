#pragma once

#include "PipelineDefines.h"

namespace GameEngine
{
    namespace ger
    {
        class RenderFlow
        {
        public:
            RenderFlow(/* args */);
            ~RenderFlow();

            virtual void Initialize();
            virtual void Activate();
            virtual void Destroy();
            virtual void Render();

        private:
            RenderStageList v_RenderStageList;
        };

    }
}