#include "../Core/GERBuffer.h"

namespace GameEngine
{
    namespace ger
    {
        struct GPUBuffer;
        class GLSLBuffer : public GERBuffer
        {
        public:
            GLSLBuffer(Device *d);
            ~GLSLBuffer();

            virtual bool Initialize(const BufferInfo &info) override;
            virtual void Destroy() override;

            GPUBuffer* GetGPUBuffer();

        private:
            GPUBuffer *p_GPUBuffer;
            BufferInfo gerBuffer;
        };

    }
}
