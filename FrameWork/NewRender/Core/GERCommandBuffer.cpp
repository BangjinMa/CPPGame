#include "GERCommandBuffer.h"

#include "GERBuffer.h"
#include "GERDevice.h"

namespace GameEngine
{
    namespace ger
    {
        GERCommandBuffer::GERCommandBuffer(Device *device) : p_Device(device) {}
        GERCommandBuffer::~GERCommandBuffer() {}
    }
}