#pragma once

#include "../Core/GERCommandBuffer.h"

namespace GameEngine
{
    namespace ger
    {
        class GLSLCommandBuffer : public GERCommandBuffer
        {
        public:
            GLSLCommandBuffer(Device *device);
            ~GLSLCommandBuffer();

            virtual void Initialize() override;
            virtual void Destroy() override;

			virtual void BindVAO(Shader* shader, InputAssembler *ia) override;
            virtual void UpdateBuffer(GERBuffer *buffer, const void *data) override;
        };

    }
}
