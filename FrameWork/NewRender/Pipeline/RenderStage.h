#pragma once

namespace GameEngine
{
    namespace ger
    {
        class RenderStage
        {
        public:
            RenderStage(/* args */);
            ~RenderStage();

            virtual void Initialize();
            virtual void Activate();
            virtual void Destroy();
            virtual void Render();
        };
    }
}
