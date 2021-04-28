#include "GERInputAssembler.h"
#include "GERDevice.h"
namespace GameEngine
{
    namespace ger
    {
        InputAssembler::InputAssembler(Device *device) : p_Device(device) {}
        InputAssembler::~InputAssembler() {}
    }
}