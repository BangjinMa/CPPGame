#include "GERFrameBuffer.h"

#include "GERDevice.h"

namespace GameEngine
{
    namespace ger
    {
        FrameBuffer::FrameBuffer(Device *d) : _device(d) {}

        FrameBuffer::~FrameBuffer() {}
    }
}
