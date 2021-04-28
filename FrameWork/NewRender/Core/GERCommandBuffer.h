#pragma once

namespace GameEngine
{
    namespace ger
    {
        class Device;
        class GERBuffer;
		class Shader;
        class InputAssembler;
        class GERCommandBuffer
        {
        public:
            GERCommandBuffer(Device *device);
            ~GERCommandBuffer();

            virtual void Initialize() = 0;
            virtual void Destroy() = 0;

            virtual void BindVAO(Shader* shader, InputAssembler *ia) = 0;
            virtual void UpdateBuffer(GERBuffer *buffer, const void *data) = 0;

        protected:
            Device *p_Device;
        };

    }
}